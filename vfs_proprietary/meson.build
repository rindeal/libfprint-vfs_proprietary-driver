if drivers.contains('vfs_proprietary')

	libvfsFprintWrapper_name = 'vfsFprintWrapper'
	libvfsFprintWrapper_dir = get_variable('libvfsFprintWrapper_dir', '')
	if libvfsFprintWrapper_dir == ''
		libvfsFprintWrapper_dir = join_paths('/opt/validity-sensor/usr', get_option('libdir'))
	endif
	libvfsFprintWrapper = cc.find_library(libvfsFprintWrapper_name, dirs: [ libvfsFprintWrapper_dir ])

	vfs_proprietary_capture_helper_dir = join_paths(get_option('prefix'), get_option('libexecdir'), meson.project_name())
	vfs_proprietary_capture_helper_name = 'vfs_proprietary-capture-helper'
	vfs_proprietary_capture_helper_path = join_paths(vfs_proprietary_capture_helper_dir, vfs_proprietary_capture_helper_name)
	vfs_proprietary_capture_helper = executable( vfs_proprietary_capture_helper_name,
		join_paths('capture-helper', 'main.c'),
		dependencies: [ libvfsFprintWrapper ],
		install: true,
		install_dir: vfs_proprietary_capture_helper_dir,
		install_rpath: libvfsFprintWrapper_dir,
		link_args: [ '-Wl,--allow-shlib-undefined' ],
	)

	drivers_sources += [ files('vfs_proprietary.c', 'capture_helper.c') ]
	drivers_cflags += [ '-Wno-unused-parameter', '-DVFS_PROPRIETARY_CAPTURE_HELPER_PATH="@0@"'.format(vfs_proprietary_capture_helper_path) ]
	drivers_cflags += [ '-Wall', '-Wextra' ]

else

	subdir_done()

endif
