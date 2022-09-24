glslang_validator = find_program('glslangValidator')
custom_targets_example = []
shaders = [
	'shader.vert.glsl',
	'shader.frag.glsl',
]
foreach shader  : shaders
	custom_targets_example += custom_target(
		'shader @0@'.format(shader),
		command : [glslang_validator, '-V', '@INPUT@', '-o', '@OUTPUT@'],
		input : shader,
		output : '@BASENAME@.spv',
		install : true,
		install_dir : 'lib/pogona',
	)
endforeach

exe_example = executable(
	'example',
	['main.c'],
	custom_targets_example,
	link_with : lib_pogona,
	dependencies : dep_volk,
	include_directories : [include_directories('../include')],
	install : true,
	install_dir : 'lib/pogona',
)
