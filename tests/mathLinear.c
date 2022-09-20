#include <assert.h>
#include <pogona/math/linear.h>
#include <stdlib.h>
#include <time.h>

#define TEST(type)                                                                                                    \
	type value##type = (type) rand();                                                                                   \
	assert(vec2##type##Equ(                                                                                             \
			vec2##type##Sum(vec2##type##S(value##type), vec2##type##S(value##type)), vec2##type##S(value##type * 2)));      \
	assert(vec3##type##Equ(                                                                                             \
			vec3##type##Sum(vec3##type##S(value##type), vec3##type##S(value##type)), vec3##type##S(value##type * 2)));      \
	assert(vec4##type##Equ(                                                                                             \
			vec4##type##Sum(vec4##type##S(value##type), vec4##type##S(value##type)), vec4##type##S(value##type * 2)));      \
                                                                                                                      \
	assert(vec2##type##Equ(vec2##type##Sub(vec2##type##S(value##type), vec2##type##S(value##type)), vec2##type##S(0))); \
	assert(vec3##type##Equ(vec3##type##Sub(vec3##type##S(value##type), vec3##type##S(value##type)), vec3##type##S(0))); \
	assert(vec4##type##Equ(vec4##type##Sub(vec4##type##S(value##type), vec4##type##S(value##type)), vec4##type##S(0))); \
                                                                                                                      \
	assert(vec2##type##Equ(vec2##type##Mul(vec2##type##S(value##type), vec2##type##S(value##type)),                     \
			vec2##type##S(value##type* value##type)));                                                                      \
	assert(vec3##type##Equ(vec3##type##Mul(vec3##type##S(value##type), vec3##type##S(value##type)),                     \
			vec3##type##S(value##type* value##type)));                                                                      \
	assert(vec4##type##Equ(vec4##type##Mul(vec4##type##S(value##type), vec4##type##S(value##type)),                     \
			vec4##type##S(value##type* value##type)));

/* TODO: division tests */

int main(void)
{
	srand(time(NULL));
	TEST(u8);
	TEST(u16);
	TEST(u32);
	TEST(u64);
	return 0;
}
