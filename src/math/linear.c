/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include <pch.h>
#include <pogona/math/linear.h>

#define IMPL_TYPE(type)                                                                                             \
	Vec2##type vec2##type##Sum(Vec2##type x, Vec2##type y)                                                            \
	{                                                                                                                 \
		return (Vec2##type) {                                                                                           \
			.x = x.x + y.x,                                                                                               \
			.y = x.y + y.y,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	Vec2##type vec2##type##Sub(Vec2##type x, Vec2##type y)                                                            \
	{                                                                                                                 \
		return (Vec2##type) {                                                                                           \
			.x = x.x - y.x,                                                                                               \
			.y = x.y - y.y,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	Vec2##type vec2##type##Mul(Vec2##type x, Vec2##type y)                                                            \
	{                                                                                                                 \
		return (Vec2##type) {                                                                                           \
			.x = x.x * y.x,                                                                                               \
			.y = x.y * y.y,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	Vec2##type vec2##type##Div(Vec2##type x, Vec2##type y)                                                            \
	{                                                                                                                 \
		return (Vec2##type) {                                                                                           \
			.x = x.x / y.x,                                                                                               \
			.y = x.y / y.y,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	bool vec2##type##Equ(Vec2##type x, Vec2##type y) { return x.x == y.x && x.y == y.y; }                             \
                                                                                                                    \
	Vec2##type vec2##type##S(type s)                                                                                  \
	{                                                                                                                 \
		return (Vec2##type) {                                                                                           \
			.x = s,                                                                                                       \
			.y = s,                                                                                                       \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	Vec3##type vec3##type##Sum(Vec3##type x, Vec3##type y)                                                            \
	{                                                                                                                 \
		return (Vec3##type) {                                                                                           \
			.x = x.x + y.x,                                                                                               \
			.y = x.y + y.y,                                                                                               \
			.z = x.z + y.z,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	Vec3##type vec3##type##Sub(Vec3##type x, Vec3##type y)                                                            \
	{                                                                                                                 \
		return (Vec3##type) {                                                                                           \
			.x = x.x - y.x,                                                                                               \
			.y = x.y - y.y,                                                                                               \
			.z = x.z - y.z,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	Vec3##type vec3##type##Mul(Vec3##type x, Vec3##type y)                                                            \
	{                                                                                                                 \
		return (Vec3##type) {                                                                                           \
			.x = x.x * y.x,                                                                                               \
			.y = x.y * y.y,                                                                                               \
			.z = x.z * y.z,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	bool vec3##type##Equ(Vec3##type x, Vec3##type y) { return x.x == y.x && x.y == y.y && x.z == y.z; }               \
                                                                                                                    \
	Vec3##type vec3##type##Div(Vec3##type x, Vec3##type y)                                                            \
	{                                                                                                                 \
		return (Vec3##type) {                                                                                           \
			.x = x.x / y.x,                                                                                               \
			.y = x.y / y.y,                                                                                               \
			.z = x.z / y.z,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	Vec3##type vec3##type##S(type s)                                                                                  \
	{                                                                                                                 \
		return (Vec3##type) {                                                                                           \
			.x = s,                                                                                                       \
			.y = s,                                                                                                       \
			.z = s,                                                                                                       \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	Vec4##type vec4##type##Sum(Vec4##type x, Vec4##type y)                                                            \
	{                                                                                                                 \
		return (Vec4##type) {                                                                                           \
			.x = x.x + y.x,                                                                                               \
			.y = x.y + y.y,                                                                                               \
			.z = x.z + y.z,                                                                                               \
			.w = x.w + y.w,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	Vec4##type vec4##type##Sub(Vec4##type x, Vec4##type y)                                                            \
	{                                                                                                                 \
		return (Vec4##type) {                                                                                           \
			.x = x.x - y.x,                                                                                               \
			.y = x.y - y.y,                                                                                               \
			.z = x.z - y.z,                                                                                               \
			.w = x.w - y.w,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	Vec4##type vec4##type##Mul(Vec4##type x, Vec4##type y)                                                            \
	{                                                                                                                 \
		return (Vec4##type) {                                                                                           \
			.x = x.x * y.x,                                                                                               \
			.y = x.y * y.y,                                                                                               \
			.z = x.z * y.z,                                                                                               \
			.w = x.w * y.w,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	Vec4##type vec4##type##Div(Vec4##type x, Vec4##type y)                                                            \
	{                                                                                                                 \
		return (Vec4##type) {                                                                                           \
			.x = x.x / y.x,                                                                                               \
			.y = x.y / y.y,                                                                                               \
			.z = x.z / y.z,                                                                                               \
			.w = x.w / y.w,                                                                                               \
		};                                                                                                              \
	}                                                                                                                 \
                                                                                                                    \
	bool vec4##type##Equ(Vec4##type x, Vec4##type y) { return x.x == y.x && x.y == y.y && x.z == y.z && x.w == y.w; } \
                                                                                                                    \
	Vec4##type vec4##type##S(type s)                                                                                  \
	{                                                                                                                 \
		return (Vec4##type) {                                                                                           \
			.x = s,                                                                                                       \
			.y = s,                                                                                                       \
			.z = s,                                                                                                       \
			.w = s,                                                                                                       \
		};                                                                                                              \
	}

IMPL_TYPE(u8);
IMPL_TYPE(u16);
IMPL_TYPE(u32);
IMPL_TYPE(u64);

IMPL_TYPE(i8);
IMPL_TYPE(i16);
IMPL_TYPE(i32);
IMPL_TYPE(i64);

IMPL_TYPE(f32);
IMPL_TYPE(f64);

IMPL_TYPE(bool);

#define IMPL_TYPE_SQRT(type, sqrt)          \
	Vec2##type vec2##type##Sqrt(Vec2##type x) \
	{                                         \
		return (Vec2##type) {                   \
			.x = sqrt(x.x),                       \
			.y = sqrt(x.y),                       \
		};                                      \
	}                                         \
                                            \
	Vec3##type vec3##type##Sqrt(Vec3##type x) \
	{                                         \
		return (Vec3##type) {                   \
			.x = sqrt(x.x),                       \
			.y = sqrt(x.y),                       \
			.z = sqrt(x.z),                       \
		};                                      \
	}                                         \
                                            \
	Vec4##type vec4##type##Sqrt(Vec4##type x) \
	{                                         \
		return (Vec4##type) {                   \
			.x = sqrt(x.x),                       \
			.y = sqrt(x.y),                       \
			.z = sqrt(x.z),                       \
			.w = sqrt(x.w),                       \
		};                                      \
	}

IMPL_TYPE_SQRT(f32, sqrtf);
IMPL_TYPE_SQRT(f64, sqrt);

#undef IMPL_TYPE_SQRT
#undef IMPL_TYPE
