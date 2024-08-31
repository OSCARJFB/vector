/*
	Written By Oscar Bergström
	https://github.com/OSCARJFB

	MIT License
	Copyright(c) 2024 Oscar Bergström
*/

#include "cvector.h"

static cVector_ptr cVectorResize(cVector_ptr vec_ptr, bool shrink)
{
	const cVector* vec = (uint8_t*)vec_ptr - offsetof(cVector, v_array);
	const int64_t newSize = shrink ? vec->capacity / 2 : vec->capacity * 2;

	cVector* new_vec = realloc(vec, vec->sizeInBytes * newSize + sizeof(cVector));
	if (!new_vec)
		return vec_ptr;

	new_vec->capacity = newSize;
	return &new_vec->v_array;
}

inline int64_t cVectorSize(cVector_ptr vec_ptr)
{
	cVector* vec = (uint8_t*)vec_ptr - offsetof(cVector, v_array);
	return vec->size;
}

cVector_ptr cVectorPushBack(cVector_ptr vec_ptr, void* item)
{
	if (!vec_ptr)
		return vec_ptr;

	const int32_t byteOffset = offsetof(cVector, v_array);
	cVector* vec = (uint8_t*)vec_ptr - byteOffset;
	if (vec->size == vec->capacity) {
		vec_ptr = cVectorResize(vec_ptr, false);
		vec = (uint8_t*)vec_ptr - byteOffset;
	}

	if(vec->size == 0)
		memcpy(vec_ptr, item, vec->sizeInBytes);
	else
		memcpy((uint8_t*)vec_ptr + vec->sizeInBytes * vec->size, item, vec->sizeInBytes);
	++vec->size;
	return vec_ptr;
}

cVector_ptr cVectorPushAt(cVector_ptr vec_ptr, int64_t index, void* item)
{
	const int32_t byteOffset = offsetof(cVector, v_array);
	cVector* vec = (uint8_t*)vec_ptr - byteOffset;
	if (vec->size == vec->capacity) {
		vec_ptr = cVectorResize(vec_ptr, false);
		vec = (uint8_t*)vec_ptr - byteOffset;
	}

	uint8_t* arrayTemp = malloc(vec->capacity * vec->sizeInBytes);
	if (!arrayTemp)
		return vec_ptr;
	memcpy(arrayTemp, vec_ptr, vec->capacity * vec->sizeInBytes);
	memcpy((uint8_t*)vec_ptr + vec->sizeInBytes * index, item, vec->sizeInBytes);
	uint8_t* dest = (uint8_t*)vec_ptr + vec->sizeInBytes * (index + 1);
	uint8_t* src = (uint8_t*)arrayTemp + vec->sizeInBytes * index;
	memcpy(dest, src, (vec->capacity - index) * vec->sizeInBytes);
	free(arrayTemp);
	arrayTemp = NULL;
	++vec->size;
	return vec_ptr;
}

cVector_ptr cVectorRemoveBack(cVector_ptr vec_ptr)
{
	cVector* vec = (uint8_t*)vec_ptr - offsetof(cVector, v_array);
	if (--vec->size == vec->capacity && vec->capacity != 10)
		vec_ptr = cVectorResize(vec_ptr, true);
	return vec_ptr;
}

cVector_ptr cVectorRemoveAt(cVector_ptr vec_ptr, int64_t index)
{

}

cVector_ptr cVectorCreate(int32_t sizeInBytes)
{
	cVector *vec = malloc(sizeInBytes * 10 + sizeof(cVector));
	if (!vec)
		return NULL;
	vec->sizeInBytes = sizeInBytes;
	vec->capacity = 10;
	vec->size = 0;
	return &vec->v_array;
}

void cVectorDelete(cVector_ptr vec_ptr)
{
	cVector* vec = (int8_t*)vec_ptr - offsetof(cVector, v_array);
	free(vec);
	vec = NULL;
}

int32_t main(void)
{
	return 0;
}