project(
	'pogona',
	'c',
	version : '0.1.0-dev',
	license : 'BSD-2-Clause',
	default_options  : [
		'c_std=c11',
		'warning_level=2',
	],
)

cmake = import('cmake')

little_endian = host_machine.endian() == 'little'
big_endian = host_machine.endian() == 'big'

config_data = configuration_data()
if little_endian
	config_data.set('POGONA_LITTLE_ENDIAN', true)
elif big_endian
	config_data.set('POGONA_BIG_ENDIAN', true)
endif

src_pogona = [
	'src/pogona.c',
	'src/vector.c',
	'src/logger.c',
	'src/math/linear.c',
]

pch_pogona = [
	'pch/pch.h',
]

inc_pogona = [
	include_directories('pch'),
	include_directories('include'),
]

deps_pogona = []

cc = meson.get_compiler('c')
if host_machine.system() != 'windows'
	deps_pogona += cc.find_library('m')
endif

custom_targets_pogona = []

subdir('src/window')
subdir('src/renderer')

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

subdir('example')
subdir('tests')
