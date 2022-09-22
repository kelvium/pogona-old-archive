/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <pch.h>
#include <pogona/vector.h>

#define VECTOR_START_CAPACITY 8
#define VECTOR_RESIZE_BY 8

typedef struct BaseVector {
	void* data;
	usize capacity;
	usize size;
	usize typeSize;
} BaseVector;

i32 vectorInitImpl(BaseVector* vector, usize typeSize)
{
	vector->capacity = VECTOR_START_CAPACITY;
	vector->size = 0;
	vector->typeSize = typeSize;
	vector->data = calloc(VECTOR_START_CAPACITY, typeSize);
	return 0;
}

i32 vectorPushImpl(BaseVector* vector, void* data)
{
	i32 error = 0;

	if (vector->size >= vector->capacity) {
		error = VECTOR_RESIZE(vector, vector->capacity + VECTOR_RESIZE_BY);
		if (error < 0)
			return error;
	}

	memcpy(vector->data + (vector->size * vector->typeSize), data, vector->typeSize);
	++vector->size;
	return error;
}

i32 vectorPopImpl(BaseVector* vector)
{
	// TODO: implement shrinking after a lot of pops so we don't lose precious
	// memory

	i32 error = 0;

	if (vector->size < 1) {
		error = -1;
		return error;
	}

	memset(vector->data + (vector->size * vector->typeSize), 0, vector->typeSize);
	--vector->size;
	return error;
}

i32 vectorResizeImpl(BaseVector* vector, usize newSize)
{
	void* reallocated = realloc(vector->data, newSize * vector->typeSize);
	if (!reallocated)
		return -1;

	if (newSize < vector->size)
		vector->size = newSize;
	vector->capacity = newSize;
	vector->data = reallocated;
	return 0;
}

i32 vectorShrinkToFitImpl(BaseVector* vector)
{
	usize requiredCapacity = vector->size * vector->typeSize;
	if (requiredCapacity == vector->capacity)
		return 0;

	void* reallocated = realloc(vector->data, requiredCapacity);
	if (!reallocated)
		return -1;

	vector->capacity = requiredCapacity;
	if (requiredCapacity == 0) /* avoid division by zero */
		vector->size = requiredCapacity / vector->typeSize;
	else
		vector->size = 0;
	vector->data = reallocated;
	return 0;
}

i32 vectorFreeImpl(BaseVector* vector)
{
	free(vector->data);
	return 0;
}
