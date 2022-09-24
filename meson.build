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

subdir('src')

if get_option('example')
	subdir('example')
endif

if get_option('tests')
	subdir('tests')
endif
