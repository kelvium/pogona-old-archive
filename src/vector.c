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

VectorError vectorInitImpl(BaseVector* vector, usize typeSize)
{
	vector->capacity = VECTOR_START_CAPACITY;
	vector->size = 0;
	vector->typeSize = typeSize;
	vector->data = calloc(VECTOR_START_CAPACITY, typeSize);
	return VECTOR_OK;
}

VectorError vectorPushImpl(BaseVector* vector, void* data)
{
	VectorError error = VECTOR_OK;

	if (vector->size >= vector->capacity) {
		error = VECTOR_RESIZE(vector, vector->capacity + VECTOR_RESIZE_BY);
		if (error != VECTOR_OK)
			return error;
	}

	memcpy(vector->data + (vector->size * vector->typeSize), data, vector->typeSize);
	++vector->size;
	return error;
}

VectorError vectorPopImpl(BaseVector* vector)
{
	// TODO: implement shrinking after a lot of pops so we don't lose precious
	// memory

	VectorError error = VECTOR_OK;

	if (vector->size < 1) {
		error = VECTOR_TOO_SMALL;
		return error;
	}

	memset(vector->data + (vector->size * vector->typeSize), 0, vector->typeSize);
	--vector->size;
	return error;
}

VectorError vectorResizeImpl(BaseVector* vector, usize newSize)
{
	void* reallocated = realloc(vector->data, newSize * vector->typeSize);
	if (!reallocated)
		return VECTOR_REALLOC_FAILED;

	if (newSize < vector->size)
		vector->size = newSize;
	vector->capacity = newSize;
	vector->data = reallocated;
	return VECTOR_OK;
}

VectorError vectorShrinkToFitImpl(BaseVector* vector)
{
	usize requiredCapacity = vector->size * vector->typeSize;
	if (requiredCapacity == vector->capacity)
		return VECTOR_OK;

	void* reallocated = realloc(vector->data, requiredCapacity);
	if (!reallocated)
		return VECTOR_REALLOC_FAILED;

	vector->capacity = requiredCapacity;
	if (requiredCapacity == 0) /* avoid division by zero */
		vector->size = requiredCapacity / vector->typeSize;
	else
		vector->size = 0;
	vector->data = reallocated;
	return VECTOR_OK;
}

VectorError vectorFreeImpl(BaseVector* vector)
{
	free(vector->data);
	return VECTOR_OK;
}
