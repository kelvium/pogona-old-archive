/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <pogona/types.h>

#define DEFINE_TYPE(name, fname, type)                             \
	typedef struct name##2##type                                     \
	{                                                                \
		type x;                                                        \
		type y;                                                        \
	}                                                                \
	name##2##type;                                                   \
                                                                   \
	typedef struct name##3##type                                     \
	{                                                                \
		type x;                                                        \
		type y;                                                        \
		type z;                                                        \
	}                                                                \
	name##3##type;                                                   \
                                                                   \
	typedef struct name##4##type                                     \
	{                                                                \
		type x;                                                        \
		type y;                                                        \
		type z;                                                        \
		type w;                                                        \
	}                                                                \
	name##4##type;                                                   \
                                                                   \
	name##2##type fname##2##type##Sum(name##2##type, name##2##type); \
	name##2##type fname##2##type##Sub(name##2##type, name##2##type); \
	name##2##type fname##2##type##Mul(name##2##type, name##2##type); \
	name##2##type fname##2##type##Div(name##2##type, name##2##type); \
	bool fname##2##type##Equ(name##2##type, name##2##type);          \
	name##2##type fname##2##type##S(type x);                         \
                                                                   \
	name##3##type fname##3##type##Sum(name##3##type, name##3##type); \
	name##3##type fname##3##type##Sub(name##3##type, name##3##type); \
	name##3##type fname##3##type##Mul(name##3##type, name##3##type); \
	name##3##type fname##3##type##Div(name##3##type, name##3##type); \
	bool fname##3##type##Equ(name##3##type, name##3##type);          \
	name##3##type fname##3##type##S(type x);                         \
                                                                   \
	name##4##type fname##4##type##Sum(name##4##type, name##4##type); \
	name##4##type fname##4##type##Sub(name##4##type, name##4##type); \
	name##4##type fname##4##type##Mul(name##4##type, name##4##type); \
	name##4##type fname##4##type##Div(name##4##type, name##4##type); \
	bool fname##4##type##Equ(name##4##type, name##4##type);          \
	name##4##type fname##4##type##S(type x)

DEFINE_TYPE(Vec, vec, u8);
DEFINE_TYPE(Vec, vec, u16);
DEFINE_TYPE(Vec, vec, u32);
DEFINE_TYPE(Vec, vec, u64);

DEFINE_TYPE(Vec, vec, i8);
DEFINE_TYPE(Vec, vec, i16);
DEFINE_TYPE(Vec, vec, i32);
DEFINE_TYPE(Vec, vec, i64);

DEFINE_TYPE(Vec, vec, f32);
DEFINE_TYPE(Vec, vec, f64);

DEFINE_TYPE(Vec, vec, bool);

#undef DEFINE_TYPE
