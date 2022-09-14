/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <pogona/vector.h>
#include <stdlib.h>
#include <time.h>

#define CHECK(x)                \
	do {                          \
		i32 error = (x);    \
		assert(error == VECTOR_OK); \
	} while (0)

int main(void)
{
	srand(time(NULL));

	I32Vector vector;
	CHECK(VECTOR_INIT(&vector));

	// First pass: push a random amount of elements to the vector
	usize elementsCount = rand() % 1024;
	for (usize i = 0; i < elementsCount; i++) {
		i32 element = rand();
		CHECK(VECTOR_PUSH(&vector, &element));
	}

	// Second pass: pop a random amount of elements from the vector (less than `elementsCount`)
	usize elementsRemoved = 0;
	for (usize i = 0; i < rand() % elementsCount; i++) {
		CHECK(VECTOR_POP(&vector));
		++elementsRemoved;
	}

	// Third pass: resize the vector to a random size
	usize newSize = rand() % 128;
	CHECK(VECTOR_RESIZE(&vector, newSize));

	CHECK(VECTOR_FREE(&vector));
	return 0;
}
