#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef void* cVector_ptr;
typedef void* cVector_Array_ptr;
typedef void* cVector_Item_ptr;

typedef struct cVector
{
	int32_t sizeInBytes;
	int64_t size, end;
	cVector_Array_ptr v_array;
} cVector;

// Add an item at the end of the vector.
// parameters:
// - cVector_ptr vec_ptr: A pointer to a vector object.
// - void* item: The address of the variable being pushed.
cVector_ptr cVectorPushBack(cVector_ptr vec_ptr, void* item);

// Add an item at a specific index. This will rearrange the order of the vector.
// parameters:
// - cVector_ptr vec_ptr: A pointer to a vector object
// - int64_t index: The index of the item being pushed.
// - void* item: The address of the variable being pushed.
cVector_ptr cVectorPushAt(cVector_ptr vec_ptr, int64_t index, void* item);

// Remove an item at the end of the vector.
// parameter: 
// - cVector_ptr vec_ptr: A pointer to a vector object.
cVector_ptr cVectorRemoveBack(cVector_ptr vec_ptr);

// Remove an item at a specific index.
// parameters: 
// - cVector_ptr vec_ptr: A pointer to a vector object.
// - int64_t index: The index of the item being removed.
cVector_ptr cVectorRemoveAt(cVector_ptr vec_ptr, int64_t index);

// Fetches the current size of the vector.
// parameter: 
// - cVector_ptr vec_ptr: A pointer to a vector object.
inline size_t cVectorSize(cVector_ptr vec_ptr);

// Create and allocate a new vector object.
// parameters: 
// - int64_t size: Initial size of the vector.
// - int32_t sizeInBytes: use the sizeof(<your data type>) operator.
cVector_ptr cVectorCreate(int64_t size, int32_t sizeInBytes);

// Free the memory of a vector.
// Don't use c free() or c++ delete on a vector pointer.
// Instead use cVectorDelete. It will make sure the metadata is properly deallocated.
// parameter: 
// - cVector_ptr vec_ptr: A pointer to a vector object.
void cVectorDelete(cVector_ptr vec_ptr);

#endif