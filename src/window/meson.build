src_pogona += [
	'window/window.c',
	'window/wayland_window_api.c',
]

dep_wayland_client = dependency('wayland-client', required : get_option('wayland_support'))
if dep_wayland_client.found()
	deps_pogona += dep_wayland_client
	config_data.set('POGONA_WAYLAND_SUPPORT', true)

	wayland = import('unstable-wayland')
	protocol_xdg_shell = wayland.find_protocol('xdg-shell')
	xdg_shell = wayland.scan_xml(protocol_xdg_shell)

	custom_targets_pogona += xdg_shell
endif
