/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <pogona/types.h>

#define VECTOR(T)   \
	struct {          \
		T* data;        \
		usize capacity; \
		usize size;     \
		usize typeSize; \
	}

typedef struct BaseVector BaseVector;

typedef enum {
	VECTOR_OK = 0,
	VECTOR_TOO_SMALL = -1,
	VECTOR_REALLOC_FAILED = -2,
} VectorError;

i32 vectorInitImpl(BaseVector* vector, usize typeSize);
i32 vectorPushImpl(BaseVector* vector, void* data);
i32 vectorPopImpl(BaseVector* vector);
i32 vectorResizeImpl(BaseVector* vector, usize newSize);
i32 vectorShrinkToFitImpl(BaseVector* vector);
i32 vectorFreeImpl(BaseVector* vector);

#define VECTOR_INIT(vector) (vectorInitImpl((BaseVector*) vector, sizeof(**vector.data)))
#define VECTOR_PUSH(vector, ...) (vectorPushImpl((BaseVector*) vector, __VA_ARGS__))
#define VECTOR_POP(vector) (vectorPopImpl((BaseVector*) vector))
#define VECTOR_RESIZE(vector, newSize) (vectorResizeImpl((BaseVector*) vector, newSize))
#define VECTOR_SHRINK_TO_FIT(vector) (vectorShrinkToFitImpl((BaseVector*) vector))
#define VECTOR_FREE(vector) (vectorFreeImpl((BaseVector*) vector))

typedef VECTOR(u8) U8Vector;
typedef VECTOR(u16) U16Vector;
typedef VECTOR(u32) U32Vector;
typedef VECTOR(u64) U64Vector;

typedef VECTOR(i8) I8Vector;
typedef VECTOR(i16) I16Vector;
typedef VECTOR(i32) I32Vector;
typedef VECTOR(i64) I64Vector;

typedef VECTOR(f32) F32Vector;
typedef VECTOR(f64) F64Vector;

typedef VECTOR(usize) USizeVector;
typedef VECTOR(isize) ISizeVector;

typedef VECTOR(void*) VoidVector;
