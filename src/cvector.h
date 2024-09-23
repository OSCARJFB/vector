/*
	Written By Oscar Bergström
	https://github.com/OSCARJFB

	MIT License
	Copyright(c) 2024 Oscar Bergström

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
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

typedef void vector;
typedef void vector_Array;

/*
	Should not be manually accessed,
	this data structure stores the vector meta data.
*/
typedef struct
{
	int32_t sizeInBytes;
	int64_t capacity, size;
	vector_Array* v_array;
} cVector;

/*
	Fetches the current size of the vector.
	parameter: 
	- vector* vec_ptr: A pointer to a vector object.
*/
int64_t vec_size(vector* vec_ptr);

/*
	Fetches the current capacity of the vector.
	parameter:
	- vector* vec_ptr: A pointer to a vector object.
*/
int64_t vec_capacity(vector* vec_ptr);

/*
	Add an item at the end of the vector.
	parameters:
	- vector vec_ptr: A pointer to a vector object.
	- void* item: The address of the variable being pushed.
*/
vector* vec_pushBack(vector* vec_ptr, void* item);

/*
	Add an item at a specific index. This will rearrange the order of the vector.
	parameters:
	- vector vec_ptr: A pointer to a vector object
	- int64_t index: The index of the item being pushed.
	- void* item: The address of the variable being pushed.
*/
vector* vec_push(vector* vec_ptr, int64_t index, void* item);

/*
	Remove an item at the end of the vector.
	parameter: 
	- vector* vec_ptr: A pointer to a vector object.
*/
vector* vec_eraseBack(vector* vec_ptr);

/*
	Remove an item at a specific index.
	parameters: 
	- vector* vec_ptr: A pointer to a vector object.
	- int64_t index: The index of the item being removed.
*/
vector* vec_erase(vector* vec_ptr, int64_t index);

/*
	Create and allocate a new vector object.
	parameters:
	- int32_t sizeInBytes: use the sizeof(<your data type>) operator.
*/
vector* vec_create(int32_t sizeInBytes);

/*
	Free the memory of a vector.
	Don't use c std free() on a vector pointer.
	Instead use vec_delete. It will make sure the metadata is properly deallocated.
	parameter: 
	- vector* vec_ptr: A pointer to a vector object.
*/
void vec_delete(vector** vec_ptr);

#endif