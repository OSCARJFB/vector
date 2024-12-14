/*
	Written By Oscar Bergström
	https://github.com/OSCARJFB

	MIT License
	Copyright(c) 2024 Oscar Bergström
*/

#include "vector.h"

static vector* vec_resize(vector* vec_ptr, bool shrink)
{
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	const int64_t newSize = shrink ? vec->size : vec->capacity * 2;

	cVector* new_vec = realloc(vec, vec->sizeInBytes * newSize + sizeof(cVector));
	if (!new_vec)
		return vec_ptr;

	new_vec->capacity = newSize;
	return &new_vec->v_array;
}

#ifdef _DEBUG

size_t vec_size(vector* vec_ptr)
{
	assert(vec_ptr && "vec_size, vec_ptr was NULL");
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	return vec->size;
}

size_t vec_capacity(vector* vec_ptr)
{
	assert(vec_ptr && "vec_capacity, vec_ptr was NULL");
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	return vec->capacity;
}

#endif // _DEBUG

vector* vec_pushBack(vector* vec_ptr, void* item)
{
	assert(vec_ptr && "vec_pushBack, vec_ptr was NULL");
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	if (vec->size == vec->capacity) {
		vec_ptr = vec_resize(vec_ptr, false);
		vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
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
	assert(vec_ptr && "vec_push, vec_ptr was NULL");
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	if (vec->size == vec->capacity) {
		vec_ptr = vec_resize(vec_ptr, false);
		vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	}

	void* tmp1 = malloc(sizeof(vec->sizeInBytes));
	void* tmp2 = malloc(sizeof(vec->sizeInBytes));
	if (!tmp1) {
		if (tmp2) {
			free(tmp2);
			tmp2 = NULL;
		}
		return NULL;
	}
	else if (!tmp2) {
		if (tmp1) {
			free(tmp1);
			tmp1 = NULL;
		}
		return NULL;
	}

	++vec->size;
	for (int64_t i = index; i < vec->size; ++i) {
		if (i == index) {
			memcpy(tmp1, (uint8_t*)vec_ptr + (i + 1) * vec->sizeInBytes, vec->sizeInBytes);

			memcpy(
				(uint8_t*)vec_ptr + (i + 1) * vec->sizeInBytes,
				(uint8_t*)vec_ptr + i * vec->sizeInBytes,
				vec->sizeInBytes
			);
		}
		else
		{
			memcpy(tmp2, (uint8_t*)vec_ptr + (i + 1) * vec->sizeInBytes, vec->sizeInBytes);

			memcpy(
				(uint8_t*)vec_ptr + (i + 1) * vec->sizeInBytes,
				tmp1,
				vec->sizeInBytes
			);

			memcpy(tmp1, tmp2, vec->sizeInBytes);
		}
	}

	memcpy((uint8_t*)vec_ptr + index * vec->sizeInBytes, item, vec->sizeInBytes);
	free(tmp1);
	free(tmp2);
	tmp1 = tmp2 = NULL;
	return vec_ptr;
}

vector* vec_eraseBack(vector* vec_ptr)
{
	assert(vec_ptr && "vec_eraseBack, vec_ptr was NULL");
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	--vec->size;
	if (vec->size < vec->capacity / 4) {
		vec_ptr = vec_resize(vec_ptr, true);
	}
	return vec_ptr;
}

vector* vec_erase(vector* vec_ptr, int64_t index)
{
	assert(vec_ptr && "vec_erase, vec_ptr was NULL");
	cVector* vec = (cVector*)((uint8_t*)vec_ptr - offsetof(cVector, v_array));
	--vec->size;

	if (vec->size < vec->capacity / 4) {
		return vec_resize(vec_ptr, true);
	}

	int64_t i;
	for (i = index ? index : 0; i < vec->size; ++i) {
		if (i == vec->size)
			break;
		memcpy(
			(uint8_t*)vec_ptr + i * vec->sizeInBytes,
			(uint8_t*)vec_ptr + (i + 1) * vec->sizeInBytes,
			vec->sizeInBytes
		);
	}

	--vec->size;
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
	assert(*vec_ptr && "vec_delete, vec_ptr pointed value was NULL");
	cVector* vec = (cVector*)((int8_t*)*vec_ptr - offsetof(cVector, v_array));
	*vec_ptr = NULL;
	free(vec);
	vec = NULL;
}