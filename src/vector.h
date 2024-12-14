/*
	Written By Oscar Bergström
	https://github.com/OSCARJFB

	MIT License
	Copyright(c) 2024 Oscar Bergström
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

typedef void vector;
typedef void vector_Array;

typedef struct cVector
{
	int32_t sizeInBytes;
	size_t capacity, size;
	vector_Array* v_array;
} cVector;

#ifdef _DEBUG

size_t vec_size(vector* vec_ptr);
size_t vec_capacity(vector* vec_ptr);

#endif // _DEBUG

vector* vec_pushBack(vector* vec_ptr, void* item);
vector* vec_push(vector* vec_ptr, int64_t index, void* item);
vector* vec_eraseBack(vector* vec_ptr);
vector* vec_erase(vector* vec_ptr, int64_t index);
vector* vec_create(int32_t sizeInBytes);
void vec_delete(vector** vec_ptr);

#ifndef _DEBUG

#define vec_size(x) ((cVector*)((uint8_t*)x - offsetof(cVector, v_array)))->size;
#define vec_size(x) ((cVector*)((uint8_t*)x - offsetof(cVector, v_array)))->capacity;

#endif // _DEBUG

#endif