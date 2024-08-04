#include "cvector.h"

inline void cVectorPushBack(cVector_ptr vec_ptr, void* item)
{
	if (!vec_ptr)
		return;
	const int byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	cVector* vec = (char*)vec_ptr - byteOffset;
	if(vec->index == 0)
		memcpy(vec_ptr, item, vec->sizeInBytes);
	else 
		memcpy((char*)vec_ptr + vec->sizeInBytes * vec->index, item, vec->sizeInBytes);
	++vec->index;
}

inline size_t cVectorSize(cVector_ptr vec_ptr)
{
	const int byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	cVector* vec = (char*)vec_ptr - byteOffset;
	return vec->size;
}

void* cVectorCreate(size_t size, int sizeInBytes)
{
	size = size <= 0 ? 10 : size;
	cVector *vec = malloc((sizeInBytes * size + sizeof(cVector)));
	if (!vec)
		return NULL;
	vec->sizeInBytes = sizeInBytes;
	vec->size = size;
	vec->index = 0;
	return &vec->v_array;
}

int main(void)
{
	Test *test = cVectorCreate(10, sizeof(Test));
	Test b1 = {1, 2, 3, 4};
	cVectorPushBack(test, &b1);
	size_t size = cVectorSize(test);
	return 0;
}