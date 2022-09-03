#include <assert.h>
#include <pogona/vector.h>
#include <stdio.h>

#define CHECK(x)                \
	do {                          \
		VectorError error = (x);    \
		assert(error == VECTOR_OK); \
	} while (0)

int main(void)
{
	U64Vector vector;
	CHECK(VECTOR_INIT(&vector));

	for (usize i = 0; i < 16; ++i) {
		assert(vector.size == i);

		// does not matter at all
		u64 value = 0xffff00ff;
		CHECK(VECTOR_PUSH(&vector, &value));

		// compare values
		u64 valueGot = vector.data[i];
		assert(value == valueGot);
	}

	CHECK(VECTOR_RESIZE(&vector, 12));

	for (usize i = 0; i < 12; i++) {
		CHECK(VECTOR_POP(&vector));
	}

	// check that it cannot pop again!
	VectorError error = VECTOR_POP(&vector);
	assert(error == VECTOR_TOO_SMALL);

	assert(vector.size == 0);
	CHECK(VECTOR_FREE(&vector));
	return 0;
}
