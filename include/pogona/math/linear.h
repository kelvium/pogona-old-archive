/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <pogona/types.h>

#define DEFINE_TYPE(type)                             \
	typedef struct Vec2##type {                         \
		type x;                                           \
		type y;                                           \
	} Vec2##type;                                       \
                                                      \
	typedef struct Vec3##type {                         \
		type x;                                           \
		type y;                                           \
		type z;                                           \
	} Vec3##type;                                       \
                                                      \
	typedef struct Vec4##type {                         \
		type x;                                           \
		type y;                                           \
		type z;                                           \
		type w;                                           \
	} Vec4##type;                                       \
                                                      \
	Vec2##type vec2##type##Sum(Vec2##type, Vec2##type); \
	Vec2##type vec2##type##Sub(Vec2##type, Vec2##type); \
	Vec2##type vec2##type##Mul(Vec2##type, Vec2##type); \
	Vec2##type vec2##type##Div(Vec2##type, Vec2##type); \
	Vec2##type vec2##type##Pow(Vec2##type, Vec2##type); \
	Vec2##type vec2##type##Sqrt(Vec2##type);            \
	bool vec2##type##Equ(Vec2##type, Vec2##type);       \
	Vec2##type vec2##type##S(type x);                   \
                                                      \
	Vec3##type vec3##type##Sum(Vec3##type, Vec3##type); \
	Vec3##type vec3##type##Sub(Vec3##type, Vec3##type); \
	Vec3##type vec3##type##Mul(Vec3##type, Vec3##type); \
	Vec3##type vec3##type##Div(Vec3##type, Vec3##type); \
	Vec3##type vec3##type##Pow(Vec3##type, Vec3##type); \
	Vec3##type vec3##type##Sqrt(Vec3##type);            \
	bool vec3##type##Equ(Vec3##type, Vec3##type);       \
	Vec3##type vec3##type##S(type x);                   \
                                                      \
	Vec4##type vec4##type##Sum(Vec4##type, Vec4##type); \
	Vec4##type vec4##type##Sub(Vec4##type, Vec4##type); \
	Vec4##type vec4##type##Mul(Vec4##type, Vec4##type); \
	Vec4##type vec4##type##Div(Vec4##type, Vec4##type); \
	Vec4##type vec4##type##Pow(Vec4##type, Vec4##type); \
	Vec4##type vec4##type##Sqrt(Vec4##type);            \
	bool vec4##type##Equ(Vec4##type, Vec4##type);       \
	Vec4##type vec4##type##S(type x)

DEFINE_TYPE(u8);
DEFINE_TYPE(u16);
DEFINE_TYPE(u32);
DEFINE_TYPE(u64);

DEFINE_TYPE(i8);
DEFINE_TYPE(i16);
DEFINE_TYPE(i32);
DEFINE_TYPE(i64);

DEFINE_TYPE(f32);
DEFINE_TYPE(f64);

#undef DEFINE_TYPE
