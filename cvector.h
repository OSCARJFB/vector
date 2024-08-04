#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef void* cVector_ptr;
typedef void* cArray_ptr;

typedef struct cVector
{
	int sizeInBytes;
	size_t size, index;
	cArray_ptr v_array;
} cVector;

typedef struct
{
	int a, b, c, d;
} Test;

inline void cVectorPushBack(cVector_ptr vec, void* item);
inline size_t cVectorSize(cVector_ptr vec_ptr);
void* cVectorCreate(size_t size, int sizeInBytes);

#endif