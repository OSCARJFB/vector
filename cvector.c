#include "cvector.h"

/*
typedef struct Test
{
	int x, y, z;
} Test;
*/

static cVector_ptr cVectorResize(cVector_ptr vec_ptr)
{
	const int byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	const cVector* vec = (char*)vec_ptr - byteOffset;
	const size_t newSize = vec->size * 2;
	
	cVector* new_vec = realloc(vec, vec->sizeInBytes * newSize + sizeof(cVector));
	if (!new_vec)
		return vec_ptr;
	
	new_vec->size = newSize;
	return &new_vec->v_array;
}

inline cVector_ptr cVectorPushBack(cVector_ptr vec_ptr, void* item)
{
	if (!vec_ptr)
		return vec_ptr;

	const int byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	cVector* vec = (char*)vec_ptr - byteOffset;
	if (vec->end == vec->size) {
		vec_ptr = cVectorResize(vec_ptr);
		vec = (char*)vec_ptr - byteOffset;
	}

	if(vec->end == 0)
		memcpy(vec_ptr, item, vec->sizeInBytes);
	else
		memcpy((char*)vec_ptr + vec->sizeInBytes * vec->end, item, vec->sizeInBytes);
	++vec->end;
	return vec_ptr;
}

inline size_t cVectorSize(cVector_ptr vec_ptr)
{
	const int byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	cVector* vec = (char*)vec_ptr - byteOffset;
	return vec->end;
}

cVector_ptr cVectorCreate(size_t size, int sizeInBytes)
{
	size = size <= 0 ? 10 : size;
	cVector *vec = malloc((sizeInBytes * size + sizeof(cVector)));
	if (!vec)
		return NULL;
	vec->sizeInBytes = sizeInBytes;
	vec->size = size;
	vec->end = 0;
	return &vec->v_array;
}

void cVectorDelete(cVector_ptr vec_ptr)
{
	const int byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	cVector* vec = (char*)vec_ptr - byteOffset;
	free(vec);
	vec = NULL;
}

int main(void)
{
	Test *test = cVectorCreate(10, sizeof(Test));
	for (int i = 0; i < 13; ++i) {
		Test testVal = { 1 + i, 2 + i, 3 + i };
		test = cVectorPushBack(test, &testVal);
	}

	size_t size = cVectorSize(test);

	for (int i = 0; i < size; ++i) 
		printf("%d %d %d\n", test[i].x, test[i].y, test[i].z);

	cVectorDelete(test);
	return 0;
}