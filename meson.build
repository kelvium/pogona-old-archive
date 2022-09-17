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
	'src/window/window.c',
	'src/window/wayland_window_api.c',
	'src/renderer/renderer.c',
	'src/renderer/vulkan_renderer_api.c',
	'src/renderer/vulkan/vulkan_core.c',
	'src/renderer/vulkan/vulkan_surface.c',
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

dep_wayland_client = dependency('wayland-client', required: get_option('wayland_support'))
if dep_wayland_client.found()
	deps_pogona += dep_wayland_client
	config_data.set('POGONA_WAYLAND_SUPPORT', true)

	wayland = import('unstable-wayland')
	protocol_xdg_shell = wayland.find_protocol('xdg-shell')
	xdg_shell = wayland.scan_xml(protocol_xdg_shell)

	custom_targets_pogona += xdg_shell
endif

if get_option('vulkan_support').enabled()
	subproject_volk = cmake.subproject('volk')
	dep_volk = subproject_volk.dependency('volk')
	if dep_volk.found()
		deps_pogona += dep_volk
		config_data.set('POGONA_VULKAN_SUPPORT', true)
	endif
endif

lib_pogona = static_library(
	'pogona',
	src_pogona,
	custom_targets_pogona,
	dependencies: deps_pogona,
	c_pch: pch_pogona,
	include_directories: inc_pogona,
)

exe_example = executable(
	'example',
	['example/main.c'],
	link_with: lib_pogona,
	dependencies: dep_volk,
	include_directories: [include_directories('include')],
)

configure_file(output: 'config.h', configuration: config_data)

subdir('tests')
