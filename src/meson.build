src_pogona = [
	'pogona.c',
	'vector.c',
	'logger.c',
	'math/linear.c',
]

pch_pogona = [
	'../pch/pch.h',
]

inc_pogona = [
	include_directories('../pch'),
	include_directories('../include'),
]

deps_pogona = []

cc = meson.get_compiler('c')
if host_machine.system() != 'windows'
	deps_pogona += cc.find_library('m')
endif

custom_targets_pogona = []

subdir('window')
subdir('renderer')

# HACK: we shouldn't do this, but it fixes CI (and any other GCC build)..
if cc.get_id() == 'gcc'
	pch_pogona = []
endif

lib_pogona = static_library(
	'pogona',
	src_pogona,
	custom_targets_pogona,
	dependencies : deps_pogona,
	c_pch : pch_pogona,
	include_directories : inc_pogona,
	install : true,
)

configure_file(output : 'config.h', configuration : config_data)
