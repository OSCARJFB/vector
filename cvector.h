#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef void* cVector_ptr;
typedef void* cArray_ptr;

typedef struct cVector
{
	int sizeInBytes;
	size_t size, end;
	cArray_ptr v_array;
} cVector;

// Add an item at the end of the vector.
// cVector_ptr vec_ptr: A pointer to a vector object.
// void* item: The address of the variable being pushed.
inline cVector_ptr cVectorPushBack(cVector_ptr vec_ptr, void* item);

// Fetches the current size of the vector.
// cVector_ptr vec_ptr: A pointer to a vector object.
inline size_t cVectorSize(cVector_ptr vec_ptr);

// Create and allocate a new vector object.
// size_t size: Initial size of the vector.
// int sizeInBytes: use the sizeof(<your data type>) operator.
cVector_ptr cVectorCreate(size_t size, int sizeInBytes);

// Free the memory of a vector.
// Don't use c free() or c++ delete on a vector pointer.
// Instead use cVectorDelete. It will make sure the metadata is properly deallocated.
// cVector_ptr vec_ptr: A pointer to a vector object.
void cVectorDelete(cVector_ptr vec_ptr);

#endif