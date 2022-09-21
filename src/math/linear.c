/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <pch.h>
#include <pogona/math/linear.h>

#define IMPL_TYPE(name, fname, type)                                                                            \
	name##2##type fname##2##type##Sum(name##2##type x, name##2##type y)                                           \
	{                                                                                                             \
		return (name##2##type) {                                                                                    \
			.x = x.x + y.x,                                                                                           \
			.y = x.y + y.y,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	name##2##type fname##2##type##Sub(name##2##type x, name##2##type y)                                           \
	{                                                                                                             \
		return (name##2##type) {                                                                                    \
			.x = x.x - y.x,                                                                                           \
			.y = x.y - y.y,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	name##2##type fname##2##type##Mul(name##2##type x, name##2##type y)                                           \
	{                                                                                                             \
		return (name##2##type) {                                                                                    \
			.x = x.x * y.x,                                                                                           \
			.y = x.y * y.y,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	name##2##type fname##2##type##Div(name##2##type x, name##2##type y)                                           \
	{                                                                                                             \
		return (name##2##type) {                                                                                    \
			.x = x.x / y.x,                                                                                           \
			.y = x.y / y.y,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	bool fname##2##type##Equ(name##2##type x, name##2##type y) { return x.x == y.x && x.y == y.y; }               \
                                                                                                                \
	name##2##type fname##2##type##S(type s)                                                                       \
	{                                                                                                             \
		return (name##2##type) {                                                                                    \
			.x = s,                                                                                                   \
			.y = s,                                                                                                   \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	name##3##type fname##3##type##Sum(name##3##type x, name##3##type y)                                           \
	{                                                                                                             \
		return (name##3##type) {                                                                                    \
			.x = x.x + y.x,                                                                                           \
			.y = x.y + y.y,                                                                                           \
			.z = x.z + y.z,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	name##3##type fname##3##type##Sub(name##3##type x, name##3##type y)                                           \
	{                                                                                                             \
		return (name##3##type) {                                                                                    \
			.x = x.x - y.x,                                                                                           \
			.y = x.y - y.y,                                                                                           \
			.z = x.z - y.z,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	name##3##type fname##3##type##Mul(name##3##type x, name##3##type y)                                           \
	{                                                                                                             \
		return (name##3##type) {                                                                                    \
			.x = x.x * y.x,                                                                                           \
			.y = x.y * y.y,                                                                                           \
			.z = x.z * y.z,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	bool fname##3##type##Equ(name##3##type x, name##3##type y) { return x.x == y.x && x.y == y.y && x.z == y.z; } \
                                                                                                                \
	name##3##type fname##3##type##Div(name##3##type x, name##3##type y)                                           \
	{                                                                                                             \
		return (name##3##type) {                                                                                    \
			.x = x.x / y.x,                                                                                           \
			.y = x.y / y.y,                                                                                           \
			.z = x.z / y.z,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	name##3##type fname##3##type##S(type s)                                                                       \
	{                                                                                                             \
		return (name##3##type) {                                                                                    \
			.x = s,                                                                                                   \
			.y = s,                                                                                                   \
			.z = s,                                                                                                   \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	name##4##type fname##4##type##Sum(name##4##type x, name##4##type y)                                           \
	{                                                                                                             \
		return (name##4##type) {                                                                                    \
			.x = x.x + y.x,                                                                                           \
			.y = x.y + y.y,                                                                                           \
			.z = x.z + y.z,                                                                                           \
			.w = x.w + y.w,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	name##4##type fname##4##type##Sub(name##4##type x, name##4##type y)                                           \
	{                                                                                                             \
		return (name##4##type) {                                                                                    \
			.x = x.x - y.x,                                                                                           \
			.y = x.y - y.y,                                                                                           \
			.z = x.z - y.z,                                                                                           \
			.w = x.w - y.w,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	name##4##type fname##4##type##Mul(name##4##type x, name##4##type y)                                           \
	{                                                                                                             \
		return (name##4##type) {                                                                                    \
			.x = x.x * y.x,                                                                                           \
			.y = x.y * y.y,                                                                                           \
			.z = x.z * y.z,                                                                                           \
			.w = x.w * y.w,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	name##4##type fname##4##type##Div(name##4##type x, name##4##type y)                                           \
	{                                                                                                             \
		return (name##4##type) {                                                                                    \
			.x = x.x / y.x,                                                                                           \
			.y = x.y / y.y,                                                                                           \
			.z = x.z / y.z,                                                                                           \
			.w = x.w / y.w,                                                                                           \
		};                                                                                                          \
	}                                                                                                             \
                                                                                                                \
	bool fname##4##type##Equ(name##4##type x, name##4##type y)                                                    \
	{                                                                                                             \
		return x.x == y.x && x.y == y.y && x.z == y.z && x.w == y.w;                                                \
	}                                                                                                             \
                                                                                                                \
	name##4##type fname##4##type##S(type s)                                                                       \
	{                                                                                                             \
		return (name##4##type) {                                                                                    \
			.x = s,                                                                                                   \
			.y = s,                                                                                                   \
			.z = s,                                                                                                   \
			.w = s,                                                                                                   \
		};                                                                                                          \
	}

IMPL_TYPE(Vec, vec, u8);
IMPL_TYPE(Vec, vec, u16);
IMPL_TYPE(Vec, vec, u32);
IMPL_TYPE(Vec, vec, u64);

IMPL_TYPE(Vec, vec, i8);
IMPL_TYPE(Vec, vec, i16);
IMPL_TYPE(Vec, vec, i32);
IMPL_TYPE(Vec, vec, i64);

IMPL_TYPE(Vec, vec, f32);
IMPL_TYPE(Vec, vec, f64);

IMPL_TYPE(Vec, vec, bool);

#undef IMPL_TYPE
