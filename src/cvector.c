/*
	Written By Oscar Bergström
	https://github.com/OSCARJFB

	MIT License
	Copyright(c) 2024 Oscar Bergström
*/

#include "cvector.h"

static vector* vec_resize(vector* vec_ptr, bool shrink)
{
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	const int64_t newSize = shrink ? vec->capacity / 2 : vec->capacity * 2;

	cVector* new_vec = realloc(vec, vec->sizeInBytes * newSize + sizeof(cVector));
	if (!new_vec)
		return vec_ptr;

	new_vec->capacity = newSize;
	return &new_vec->v_array;
}

int64_t vec_size(vector* vec_ptr)
{
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	return vec->size;
}

int64_t vec_capacity(vector* vec_ptr)
{
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	return vec->capacity;
}


vector* vec_pushBack(vector* vec_ptr, void* item)
{
	if (!vec_ptr)
		return vec_ptr;

	const int32_t byteOffset = offsetof(cVector, v_array);
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - byteOffset);
	if (vec->size == vec->capacity) {
		vec_ptr = vec_resize(vec_ptr, false);
		vec = (cVector*)((uint8_t*)vec_ptr - byteOffset);
	}

	if (vec->size == 0)
		memcpy(vec_ptr, item, vec->sizeInBytes);
	else
		memcpy((uint8_t*)vec_ptr + vec->sizeInBytes * vec->size, item, vec->sizeInBytes);
	++vec->size;
	return vec_ptr;
}

vector* vec_push(vector* vec_ptr, int64_t index, void* item)
{
	const int32_t byteOffset = offsetof(cVector, v_array);
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - byteOffset);
	if (vec->size == vec->capacity) {
		vec_ptr = vec_resize(vec_ptr, false);
		vec = (cVector*)((uint8_t*)vec_ptr - byteOffset);
	}

	uint8_t* arrayTemp = malloc(vec->capacity * vec->sizeInBytes);
	if (!arrayTemp)
		return vec_ptr;

	memcpy(arrayTemp, vec_ptr, vec->capacity * vec->sizeInBytes);
	memcpy((uint8_t*)vec_ptr + vec->sizeInBytes * (index ? index : 0), item, vec->sizeInBytes);

	uint8_t* dest = index ? (uint8_t*)vec_ptr + vec->sizeInBytes * (index + 1) :
		(uint8_t*)vec_ptr + vec->sizeInBytes * 2;
	uint8_t* src = index ? (uint8_t*)arrayTemp + vec->sizeInBytes * index :
		(uint8_t*)arrayTemp + vec->sizeInBytes;

	memcpy(dest, src, (vec->capacity - index) * vec->sizeInBytes);

	free(arrayTemp);
	arrayTemp = NULL;
	++vec->size;
	return vec_ptr;
}

vector* vec_eraseBack(vector* vec_ptr)
{
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	if (--vec->size < vec->capacity / 2)
		vec_ptr = vec_resize(vec_ptr, true);

	return vec_ptr;
}

vector* vec_erase(vector* vec_ptr, int64_t index)
{
	const int32_t byteOffset = offsetof(cVector, v_array);
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - byteOffset);
	if (--vec->size < vec->capacity / 2)
		return vec_resize(vec_ptr, false);

	uint8_t* endItem = malloc(vec->sizeInBytes);
	if (!endItem)
		return NULL;

	int64_t i;
	for (i = index ? index : 0; i < vec->size; ++i) {
		if (i == vec->size)
			break;

		uint8_t* src = (uint8_t*)vec_ptr + (i + 1) * vec->sizeInBytes;
		uint8_t* dest = (uint8_t*)vec_ptr + i * vec->sizeInBytes;
		for (int32_t i = 0; i < vec->sizeInBytes; ++i)
			*dest++ = *src++;
	}

	return vec_ptr;
}

vector* vec_create(int32_t sizeInBytes)
{
	cVector* vec = malloc(sizeInBytes * 2 + sizeof(cVector));
	if (!vec)
		return NULL;
	vec->sizeInBytes = sizeInBytes;
	vec->capacity = 2;
	vec->size = 0;
	return &vec->v_array;
}

void vec_delete(vector** vec_ptr)
{
	cVector* vec = (cVector*)((int8_t*)*vec_ptr - offsetof(cVector, v_array));
	*vec_ptr = NULL;
	free(vec);
	vec = NULL;
}