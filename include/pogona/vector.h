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
	VECTOR_OK,
	VECTOR_TOO_SMALL,
	VECTOR_REALLOC_FAILED,
} VectorError;

VectorError vectorInitImpl(BaseVector* vector, usize typeSize);
VectorError vectorPushImpl(BaseVector* vector, void* data);
VectorError vectorPopImpl(BaseVector* vector);
VectorError vectorResizeImpl(BaseVector* vector, usize newSize);
VectorError vectorFreeImpl(BaseVector* vector);

#define VECTOR_INIT(vector) \
	(vectorInitImpl((BaseVector*) vector, sizeof(**vector.data)))
#define VECTOR_PUSH(vector, ...) \
	(vectorPushImpl((BaseVector*) vector, __VA_ARGS__))
#define VECTOR_POP(vector) (vectorPopImpl((BaseVector*) vector))
#define VECTOR_RESIZE(vector, newSize) \
	(vectorResizeImpl((BaseVector*) vector, newSize))
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
