# libfprint-vfs_proprietary-driver

[![Build Status](https://travis-ci.com/rindeal/libfprint-vfs_proprietary-driver.svg?branch=master)](https://travis-ci.com/rindeal/libfprint-vfs_proprietary-driver)


## What

[libfprint](https://www.freedesktop.org/wiki/Software/fprint/libfprint/) driver for:

  - VFS451 (138a:0007)
  - VFS471 (138a:003c)
  - VFS491 (138a:003d)
  - VFS495 (138a:003f)
  - \+ some others, but I've disabled them since FOSS alternative exists

This driver is remotely based on an ancient patch created by the sensors' manufacturer (_Validity Sensors, Inc._) for an ancient version of libfprint.


## Why

The driver from that manufacturer's patch represented just a tiny middleware for a proprietary _libvfsFprintWrapper.so_ library,
which itself was used for communication with a proprietary daemon _vcsFPService_ which was finally communicating with the fingerprint reader via USB API exposed by the Linux kernel.
This approach proved to be very buggy and worked just for about 50% of time, the other half you ended up with a nasty lockup.
Not to mention the inherent risks of loading a closed-source proprietary library into the calling process' memory space.

So what I did in this project was to separate the proprietary binaries completely by creating a dedicated process
which loads the proprietary library and then just sends back the scanned image via a pipe.
This way both binary components (the lib and the daemon) can be sanitized, sandboxed, whatever, ....

I also brought this driver up the spec for the latest libfprint API which was introduced with v0.8.0.

I understand that this driver is still far from optimal, but there are still no open-source drivers available.
Although there are some reverse-engineering efforts underway for other sensors - [nmikhailov/Validity90](https://github.com/nmikhailov/Validity90), [hmaarrfk/Validity91](https://github.com/hmaarrfk/Validity91).


## How

If you use [Portage](https://wiki.gentoo.org/wiki/Portage) you can just install [`sys-auth/libfprint` package from my ebuild repo](https://github.com/rindeal/rindeal-ebuild-repo/tree/master/sys-auth/libfprint)
with `vfs_proprietary-driver` USE-flag enabled.

If not you have to do everything manually by yourself:

The final architecture should look like this:

```plain
                                      +----------+
                                      | some app |
                                      +----+-----+
                                           |
                             +-------------+--------------+
                             | libfprint                  |
                             |                            |
                             | +------------------------+ |
                             | | vfs_proprietary-driver +-----+
                             | +------------------------+ |   |
                             +----------------------------+   |
                                                              |
                                                          pipes IPC
                                                              |
                          +--------------------------------+  |
                 +--------+ vfs_proprietary_capture-helper +--+
                 |        +--------------------------------+
                 |
           dynamic linking
                 |
+---------------------------------------------------------------------------+
|                |                  proprietary layer                       |
|                |                                                          |
| +--------------+-----------------+                +---------------------+ |
| | libvfsFprintWrapper.so library | <------------> | vcsFPService daemon | |
| +--------------------------------+   custom IPC   +---------------------+ |
|                                                                           |
+-------------------------------------------+-------------------------------+
                                            |
                                      +-----+------+
                                      | libusb-0.1 |
                                      +-----+------+
                                            |
                                     +------+-------+
                                     | Linux kernel |
                                     +------+-------+
                                            |
                                       +----+----+
                                       | *magic* |
                                       +----+----+
                                            |
                                       +----+----+
                                       | USB hub |
                                       +----+----+
                                            |
                                  +---------+----------+
                                  | fingerprint reader |
                                  +--------------------+
```

**Notes:**

 - `vfs_proprietary_capture-helper` is built together with the driver and the driver will have it's installation path hardcoded into itself
 - `vfs_proprietary_capture-helper` will also have rpath set to the directory containing `libvfsFprintWrapper.so`, so that you can place the proprietary binaries into a separate dir in `/opt` without the necessity to register the path in `/etc/ld.so.conf`.
 - proprietary binaries can be downloaded from [here](https://ftp.hp.com/pub/softpaq/sp84501-85000/sp84530.tar)
 - up-to-date script to compile _libfprint_ with this driver enabled is [here](https://github.com/rindeal/libfprint-vfs_proprietary-driver/blob/master/.ci/script)
 

## Assumptions and options

The compilation assumes the shared binary library is installed in `/opt/validity-sensor/usr/lib64`.
If that's not the case on your installation you can change the path to the containing directory
by defining `libvfsFprintWrapper_dir` Meson variable prior to calling the `subdir` Meson command.

The driver will return an error if no fingerprint is scanned within a hardcoded time window.
This timeout can be set with `VFS_PROPRIETARY_CAPTURE_HELPER_TIMEOUT` preprocessor definition.

The filename of the utility used for handling the binary library can be set with `VFS_PROPRIETARY_CAPTURE_HELPER_PATH` cpp macro.
