/*
	Written By Oscar Bergström
	https://github.com/OSCARJFB

	MIT License
	Copyright(c) 2024 Oscar Bergström
*/

#include "cvector.h"

static vector_ptr vec_resize(vector_ptr vec_ptr, bool shrink)
{
	const cVector* vec = (uint8_t*)vec_ptr - offsetof(cVector, v_array);
	const int64_t newSize = shrink ? vec->capacity / 2 : vec->capacity * 2;

	cVector* new_vec = realloc(vec, vec->sizeInBytes * newSize + sizeof(cVector));
	if (!new_vec)
		return vec_ptr;

	new_vec->capacity = newSize;
	return &new_vec->v_array;
}

inline int64_t vec_size(vector_ptr vec_ptr)
{
	cVector* vec = (uint8_t*)vec_ptr - offsetof(cVector, v_array);
	return vec->size;
}

inline int64_t vec_capacity(vector_ptr vec_ptr)
{
	cVector* vec = (uint8_t*)vec_ptr - offsetof(cVector, v_array);
	return vec->capacity;
}


vector_ptr vec_insertAtEnd(vector_ptr vec_ptr, void* item)
{
	if (!vec_ptr)
		return vec_ptr;

	const int32_t byteOffset = offsetof(cVector, v_array);
	cVector* vec = (uint8_t*)vec_ptr - byteOffset;
	if (vec->size == vec->capacity) {
		vec_ptr = vec_resize(vec_ptr, false);
		vec = (uint8_t*)vec_ptr - byteOffset;
	}

	if(vec->size == 0)
		memcpy(vec_ptr, item, vec->sizeInBytes);
	else
		memcpy((uint8_t*)vec_ptr + vec->sizeInBytes * vec->size, item, vec->sizeInBytes);
	++vec->size;
	return vec_ptr;
}

vector_ptr vec_insert(vector_ptr vec_ptr, int64_t index, void* item)
{
	const int32_t byteOffset = offsetof(cVector, v_array);
	cVector* vec = (uint8_t*)vec_ptr - byteOffset;
	if (vec->size == vec->capacity) {
		vec_ptr = vec_resize(vec_ptr, false);
		vec = (uint8_t*)vec_ptr - byteOffset;
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

vector_ptr vec_eraseAtEnd(vector_ptr vec_ptr)
{
	cVector* vec = (uint8_t*)vec_ptr - offsetof(cVector, v_array);
	if (--vec->size < vec->capacity / 2)
		vec_ptr = vec_resize(vec_ptr, true);

	return vec_ptr;
}

vector_ptr vec_erase(vector_ptr vec_ptr, int64_t index)
{
	const int32_t byteOffset = offsetof(cVector, v_array);
	cVector* vec = (uint8_t*)vec_ptr - byteOffset;
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

vector_ptr vec_create(int32_t sizeInBytes)
{
	cVector *vec = malloc(sizeInBytes * 10 + sizeof(cVector));
	if (!vec)
		return NULL;
	vec->sizeInBytes = sizeInBytes;
	vec->capacity = 10;
	vec->size = 0;
	return &vec->v_array;
}

void vec_delete(vector_ptr *vec_ptr)
{
	const cVector* vec = (int8_t*)*vec_ptr - offsetof(cVector, v_array);
	for (int64_t i = 0; i < vec->capacity; ++i) {
		(uint8_t*)*vec_ptr = i ? (uint8_t*)*vec_ptr + i * vec->sizeInBytes : (uint8_t*)*vec_ptr;
		vec_ptr = NULL;
	}
	vec_ptr = NULL;
	free(vec);
	vec = NULL;
}

static void test(int* vec_num)
{
	int push = 94;
	vec_num = vec_insert(vec_num, 0, &push);

	vec_delete(&vec_num);
	vec_num[10] = 1994;
	printf("%d\n", vec_num[1]);
}

int main(void)
{
	int* vec_num = vec_create(sizeof(int));
	for (int i = 0; i < 100; ++i)
	vec_num = vec_insertAtEnd(vec_num, &i);

	test(vec_num);
	return 0;
}