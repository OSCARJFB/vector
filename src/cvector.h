#ifndef CVECTOR_H
#define CVECTOR_H

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
	int64_t capacity, size;
	vector_Array* v_array;
} cVector;

int64_t vec_size(vector* vec_ptr);
int64_t vec_capacity(vector* vec_ptr);
vector* vec_pushBack(vector* vec_ptr, void* item);
vector* vec_push(vector* vec_ptr, int64_t index, void* item);
vector* vec_eraseBack(vector* vec_ptr);
vector* vec_erase(vector* vec_ptr, int64_t index);
vector* vec_create(int32_t sizeInBytes);
void vec_delete(vector** vec_ptr);

#endif