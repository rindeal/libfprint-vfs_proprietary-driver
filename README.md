# libfprint-vfs_proprietary-driver

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
which loads the proprieatry library and the just sends back the scanned image via a pipe.
This way both binary components (the lib and the daemon) can be sanitized, sandboxed, whatever, ....

I also brought this driver up the spec for the latest libfprint API which was introduced with v0.8.0.

I understand that this driver is still far from optimal, but there are still no open-source drivers available.
Although there are some reverse-engineering efforts underway for other sensors - [nmikhailov/Validity90](https://github.com/nmikhailov/Validity90), [hmaarrfk/Validity91](https://github.com/hmaarrfk/Validity91).


## How

If you use [Portage](https://wiki.gentoo.org/wiki/Portage) you can just install [`sys-auth/libfprint` package from my ebuild repo](https://github.com/rindeal/rindeal-ebuild-repo/tree/master/sys-auth/libfprint)
with `vfs_proprietary-driver` USE-flag enabled.

If not you have to do everything manually by yourself:

### 1. Install proprietary binaries

They can be downloaded from [here](https://ftp.hp.com/pub/softpaq/sp84501-85000/sp84530.tar).

### 2. Copy this repo to libfprint source tree and patch it's build system

```sh
$ cd LIBFPRINT_SOURCE_TREE
$ cp -a THIS_REPO/vfs_proprietary libfprint/drivers/vfs_proprietary
$ sed -e "/^all_drivers *=/a all_drivers += [ 'vfs_proprietary' ]" -i -- meson.build
$ sed -e "/^libfprint *=/i subdir('drivers/vfs_proprietary')" -i -- libfprint/meson.build
```

The compilation assumes the shared binary library is installed in `/opt/validity-sensor/usr/lib64`.
If that's not the case on your installation you can change the path to the containing directory
by defining `libvfsFprintWrapper_dir` Meson variable prior to calling the `subdir` Meson command.
