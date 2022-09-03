#include <assert.h>
#include <pogona/vector.h>
#include <stdlib.h>
#include <time.h>

#define CHECK(x)                \
	do {                          \
		VectorError error = (x);    \
		assert(error == VECTOR_OK); \
	} while (0)

i32 getRandom()
{
	i32 random = rand();
	if (random == 0) {
		return 1;
	}
	return random;
}

int main(void)
{
	srand(time(NULL));

	I32Vector vector;
	CHECK(VECTOR_INIT(&vector));

	// First pass: push a random amount of elements to the vector
	usize elementsCount = getRandom() % 1024;
	for (usize i = 0; i < elementsCount; i++) {
		i32 element = getRandom();
		CHECK(VECTOR_PUSH(&vector, &element));
	}

	// Second pass: pop a random amount of elements from the vector (less than `elementsCount`)
	usize elementsRemoved = 0;
	for (usize i = 0; i < getRandom() % elementsCount; i++) {
		CHECK(VECTOR_POP(&vector));
		++elementsRemoved;
	}

	// Third pass: resize the vector to a random size
	usize newSize = getRandom() % 128;
	CHECK(VECTOR_RESIZE(&vector, newSize));

	CHECK(VECTOR_FREE(&vector));
	return 0;
}
