src_pogona += [
	'src/renderer/renderer.c',
]

if get_option('vulkan_support').enabled()
	src_pogona += [
		'src/renderer/vulkan_renderer_api.c',
		'src/renderer/vulkan/vulkan_core.c',
		'src/renderer/vulkan/vulkan_surface.c',
		'src/renderer/vulkan/vulkan_swapchain.c',
		'src/renderer/vulkan/vulkan_synchronization.c',
		'src/renderer/vulkan/vulkan_render_pass.c',
		'src/renderer/vulkan/vulkan_shader.c',
		'src/renderer/vulkan/vulkan_pipeline.c',
	]

	options = cmake.subproject_options()
	# FIXME: this is not cross-platform because some platforms, for example Linux, may have multiple APIs available.
	# FIXME: commented again because it causes some problems :-p
	#if get_option('wayland_support').enabled()
		options.add_cmake_defines({'VOLK_STATIC_DEFINES' : 'VK_USE_PLATFORM_WAYLAND_KHR'})
	#endif

	subproject_volk = cmake.subproject('volk', options : options)
	dep_volk = subproject_volk.dependency('volk')
	if dep_volk.found()
		deps_pogona += dep_volk
		config_data.set('POGONA_VULKAN_SUPPORT', true)
	endif
endif
