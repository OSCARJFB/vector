#include "cvector.h"

static cVector_ptr cVectorResize(cVector_ptr vec_ptr)
{
	const int byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	const cVector* vec = (char*)vec_ptr - byteOffset;
	const size_t newSize = vec->size * 2;
	cVector *temp_vec = malloc(newSize);
	if (!temp_vec)
		return vec_ptr;

	memcpy(temp_vec, vec, sizeof(cVector) + vec->end * vec->sizeInBytes);
	temp_vec->size = newSize;
	cVectorDelete(vec_ptr);
	return &temp_vec->v_array;
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
	int *test = cVectorCreate(10, sizeof(int));
	for (int i = 0; i < 15; ++i)
		test = cVectorPushBack(test, &i);

	size_t size = cVectorSize(test);

	for (int i = 0; i < size; ++i)
		printf("%d ", test[i]);

	cVectorDelete(test);
	return 0;
}