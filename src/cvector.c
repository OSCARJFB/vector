/*
	Written By Oscar Bergström
	https://github.com/OSCARJFB

	MIT License
	Copyright(c) 2024 Oscar Bergström
*/

#include "cvector.h"

static cVector_ptr cVectorResize(cVector_ptr vec_ptr, bool shrink)
{
	const int32_t byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	const cVector* vec = (int8_t*)vec_ptr - byteOffset;
	const int64_t newSize = shrink ? vec->size / 2 : vec->size * 2;

	cVector* new_vec = realloc(vec, vec->sizeInBytes * newSize + sizeof(cVector));
	if (!new_vec)
		return vec_ptr;

	new_vec->size = newSize;
	return &new_vec->v_array;
}

inline int64_t cVectorSize(cVector_ptr vec_ptr)
{
	const int32_t byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	cVector* vec = (int8_t*)vec_ptr - byteOffset;
	return vec->end;
}

cVector_ptr cVectorPushBack(cVector_ptr vec_ptr, void* item)
{
	if (!vec_ptr)
		return vec_ptr;

	const int32_t byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	cVector* vec = (int8_t*)vec_ptr - byteOffset;
	if (vec->end == vec->size) {
		vec_ptr = cVectorResize(vec_ptr, false);
		vec = (int8_t*)vec_ptr - byteOffset;
	}

	if(vec->end == 0)
		memcpy(vec_ptr, item, vec->sizeInBytes);
	else
		memcpy((int8_t*)vec_ptr + vec->sizeInBytes * vec->end, item, vec->sizeInBytes);
	++vec->end;
	return vec_ptr;
}

cVector_ptr cVectorPushAt(cVector_ptr vec_ptr, int64_t index, void* item)
{

}

cVector_ptr cVectorRemoveBack(cVector_ptr vec_ptr)
{
	const int32_t byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	cVector* vec = (int8_t*)vec_ptr - byteOffset;
	if (--vec->end == vec->size / 2 && vec->size != 10)
		vec_ptr = cVectorResize(vec_ptr, true);
	return vec_ptr;
}

cVector_ptr cVectorRemoveAt(cVector_ptr vec_ptr, int64_t index)
{

}

cVector_ptr cVectorCreate(int64_t size, int32_t sizeInBytes)
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
	cVector* vec = (int8_t*)vec_ptr - byteOffset;
	free(vec);
	vec = NULL;
}

int32_t main(void)
{
	int* vec_number = cVectorCreate(10, sizeof(int));
	for (int i = 0; i < 100; ++i)
		vec_number = cVectorPushBack(vec_number, &i);
	
	for (int i = 0; i < cVectorSize(vec_number); ++i)
		printf("%d ", vec_number[i]);

	for (int i = 0; i < 100; ++i)
		cVectorRemoveBack(vec_number);

	int64_t a = cVectorSize(vec_number);
	cVectorDelete(vec_number);
	return 0;
}