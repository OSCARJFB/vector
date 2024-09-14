/*
	Written By Oscar Bergström
	https://github.com/OSCARJFB

	MIT License
	Copyright(c) 2024 Oscar Bergström
*/

#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Remove later
#include <stdio.h>

typedef void* vector_ptr;
typedef void* vector_Array_ptr;

typedef struct
{
	int32_t sizeInBytes;
	int64_t capacity, size;
	vector_Array_ptr v_array;
} cVector;

/*
	Fetches the current size of the vector.
	parameter: 
	- vector_ptr vec_ptr: A pointer to a vector object.
*/
inline size_t vec_size(vector_ptr vec_ptr);

/*
	Create and allocate a new vector object.
	parameters: 
	- int32_t sizeInBytes: use the sizeof(<your data type>) operator.
*/
vector_ptr vec_create(int32_t sizeInBytes);

/*
	Add an item at the end of the vector.
	parameters:
	- vector_ptr vec_ptr: A pointer to a vector object.
	- void* item: The address of the variable being pushed.
*/
vector_ptr vec_insertAtEnd(vector_ptr vec_ptr, void* item);

/*
	Add an item at a specific index. This will rearrange the order of the vector.
	parameters:
	- vector_ptr vec_ptr: A pointer to a vector object
	- int64_t index: The index of the item being pushed.
	- void* item: The address of the variable being pushed.
*/
vector_ptr vec_insert(vector_ptr vec_ptr, int64_t index, void* item);

/*
	Remove an item at the end of the vector.
	parameter: 
	- vector_ptr vec_ptr: A pointer to a vector object.
*/
vector_ptr vec_eraseAtEnd(vector_ptr vec_ptr);

/*
	Remove an item at a specific index.
	parameters: 
	- vector_ptr vec_ptr: A pointer to a vector object.
	- int64_t index: The index of the item being removed.
*/
vector_ptr vec_erase(vector_ptr vec_ptr, int64_t index);

/*
	Free the memory of a vector.
	Don't use c std free() on a vector pointer.
	Instead use vec_delete. It will make sure the metadata is properly deallocated.
	parameter: 
	- vector_ptr vec_ptr: A pointer to a vector object.
*/
void vec_delete(vector_ptr vec_ptr);

#endif