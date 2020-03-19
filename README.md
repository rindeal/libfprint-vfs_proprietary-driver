# libfprint-vfs_proprietary-driver

[![Build Status](https://travis-ci.com/rindeal/libfprint-vfs_proprietary-driver.svg?branch=master)](https://travis-ci.com/rindeal/libfprint-vfs_proprietary-driver)
![Stability - Beta](https://img.shields.io/badge/stability-beta-33bbff.svg)

[**See project status announcement**](https://github.com/rindeal/libfprint-vfs_proprietary-driver/issues/8)

## What

[libfprint](https://www.freedesktop.org/wiki/Software/fprint/libfprint/) driver for:

  - VFS451 (138a:0007)
  - VFS471 (138a:003c)
  - VFS491 (138a:003d)
  - VFS495 (138a:003f)
  - \+ some others, but I've disabled them since FOSS alternative exists

This driver is remotely based on an ancient patch created by the sensors' manufacturer (_Validity Sensors, Inc._) for an ancient version of libfprint. I wasn't able to find the original source, but you can find the patch floating in the internets.


## Why

The driver from that manufacturer's patch represented just a tiny middleware for a proprietary _libvfsFprintWrapper.so_ library,
which itself was used for communication with a proprietary daemon _vcsFPService_ which was finally communicating with the fingerprint reader via USB API exposed by the Linux kernel.
This approach proved to be very buggy and worked just about 50% of time, the other half you ended up with a nasty lockup.
Not to mention the inherent risks of loading a closed-source proprietary library into the calling process' memory space.

So what I did in this project was to separate the proprietary binaries completely by creating a dedicated process
which loads the proprietary library and then just sends back the scanned image via a pipe.
This way both binary components (the lib and the daemon) can be sanitized, sandboxed, whatever, ....

I also brought this driver up the spec for the latest libfprint API which was introduced with v0.8.0, but since changed again, so some rework will have to be done when v0.9.0 is released.

I understand that this driver is still far from optimal, but there is still no open-source driver available for these sensors.
Although there are some reverse-engineering efforts underway for other sensors - [nmikhailov/Validity90](https://github.com/nmikhailov/Validity90), [hmaarrfk/Validity91](https://github.com/hmaarrfk/Validity91).


## How

### Automatic setup

If you use [Portage](https://wiki.gentoo.org/wiki/Portage) you can just install [`sys-auth/libfprint` package from my ebuild repo](https://github.com/rindeal/rindeal-ebuild-repo/tree/master/sys-auth/libfprint)
with `vfs_proprietary-driver` USE-flag enabled.

#### For Arch Users
If you are on arch linux, you can install it from Arch User Repository(AUR) using package name [libfprint-vfs_proprietary-git](https://aur.archlinux.org/packages/libfprint-vfs_proprietary-git/)

### Manual setup
How to fit everything together is specific to every Linux distribution, so I cannot describe it step by step, but the final architecture should look like this:

```plain
                         +--------------------------------+
                         |  some app                      |
                         |                                |
                         | +----------------------------+ |
                         | | libfprint                  | |
                         | |                            | |
                         | | +------------------------+ | |
                         | | | vfs_proprietary-driver | | |
                         | | |                        | | |
                         | | +-------+----------------+ | |
                         | |         |                  | |
                         | +----------------------------+ |
                         |           |                    |
                         +--------------------------------+
                                     |
                                 pipes IPC
                                     |
  +----------------------------------+---+
  | vfs_proprietary-capture-helper       |
  |                                      |
  |                                      |
+-+ - - - - - - - - - - - - - - - - - -  +--------------------------------------+
| |                                      |                    proprietary layer |
| |                                      |                                      |
| | +--------------------------------+   |              +---------------------+ |
| | | libvfsFprintWrapper.so library | <--------------> | vcsFPService daemon | |
| | |                                |   | custom IPC   |                     | |
| | +-----------------+--------------+   |              +---------+-----------+ |
| |                   |                  |                        |             |
| +--------------------------------------+                        |             |
|                     |                                           |             |
| - - - - - - - - - - | - - - - - - - - - - - - - - - - - - - - - | - - - - - - |
|                     |                                           |             |
|                     |           +------------+                  |             |
|                     +-----------+ libusb-0.1 +------------------+             |
|                                 |            |                                |
|                                 +------+-----+                                |
|                                        |                                      |
+-------------------------------------------------------------------------------+
                                         |
                                 +-------+------+
                                 | Linux kernel |
                                 |              |
                                 +-------+------+
                                         |
                            +------------------------+
                            | hardware   |           |
                            |            |           |
                            |      +-----+---+       |
                            |      | USB hub |       |
                            |      |         |       |
                            |      +----+----+       |
                            |           |            |
                            | +---------+----------+ |
                            | | fingerprint reader | |
                            | |                    | |
                            | +--------------------+ |
                            |                        |
                            +------------------------+

```

up-to-date script to compile _libfprint_ with this driver enabled is [here](https://github.com/rindeal/libfprint-vfs_proprietary-driver/blob/master/.ci/script)


**Notes:**

### Proprietary binaries

They can be downloaded from [here](https://ftp.hp.com/pub/softpaq/sp84501-85000/sp84530.tar).
The laptop I developed this driver on is from Hewlett-Packard, so I'm using a driver package from this vendor, but it's possible that you can find these binaries elsewhere, too.
From all the files in this archive, we're going to use only two of them: `vcsFPService` and `libvfsFprintWrapper.so`.

- `vcsFPService` is a daemon which has to be running for this driver to work at all
- `libvfsFprintWrapper.so` is a shared library used to handle communication with `vcsFPService` daemon and is the only proprietary component this driver uses directly


### `vfs_proprietary_capture-helper`

This small utility is built together with the driver, is installed into `libexec` dir by default and the driver will have it's installation path hardcoded into itself.
It links dynamically to the proprietary shared library `libvfsFprintWrapper.so`.
This utility has rpath hardcoded to the directory containing `libvfsFprintWrapper.so`, so you can place the proprietary library even under non-standard directory (eg. `/opt`).
To customize the path to this dir see [Assumptions and options](#assumptions-and-options) section.


## Assumptions and options

The build system assumes the shared binary library is installed in `/opt/validity-sensor/usr/lib64`.
If that's not the case on your installation you can change the path by defining `libvfsFprintWrapper_dir` Meson variable prior to calling the `subdir(VFS_PROPRIETARY_DIR)` Meson command.

In order to prevent lockups, the driver will return an error if no fingerprint is scanned within a hardcoded time window.
This timeout can be set with `VFS_PROPRIETARY_CAPTURE_HELPER_TIMEOUT` preprocessor definition. How you pass it to the preporcessor is at your discretion.

The filename of and/or the path to the utility used for handling the binary library can be set with `VFS_PROPRIETARY_CAPTURE_HELPER_PATH` cpp macro.
