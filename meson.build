project(
	'pogona',
	'c',
	version: '0.1.0-dev',
	license: 'BSD-3-Clause',
	default_options: [
		'c_std=c11',
		'warning_level=2',
	],
)

src_pogona = [
	'src/pogona.c',
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

lib_pogona = library(
	'pogona',
	src_pogona,
	dependencies: deps_pogona,
	c_pch: pch_pogona,
	include_directories: inc_pogona,
)

exe_example = executable(
	'example',
	['example/main.c'],
	link_with: lib_pogona,
	include_directories: [include_directories('include')],
)
