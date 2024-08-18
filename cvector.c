#include "cvector.h"

static cVector_ptr cVectorIncrease(cVector_ptr vec_ptr)
{
	const int32_t byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	const cVector* vec = (int8_t*)vec_ptr - byteOffset;
	const int64_t newSize = vec->size * 2;
	
	cVector* new_vec = realloc(vec, vec->sizeInBytes * newSize + sizeof(cVector));
	if (!new_vec)
		return vec_ptr;
	
	new_vec->size = newSize;
	return &new_vec->v_array;
}

static cVector_ptr cVectorDecrease(cVector_ptr vec_ptr)
{

}

cVector_ptr cVectorPushBack(cVector_ptr vec_ptr, void* item)
{
	if (!vec_ptr)
		return vec_ptr;

	const int32_t byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	cVector* vec = (int8_t*)vec_ptr - byteOffset;
	if (vec->end == vec->size) {
		vec_ptr = cVectorIncrease(vec_ptr);
		vec = (int8_t*)vec_ptr - byteOffset;
	}

	if(vec->end == 0)
		memcpy(vec_ptr, item, vec->sizeInBytes);
	else
		memcpy((int8_t*)vec_ptr + vec->sizeInBytes * vec->end, item, vec->sizeInBytes);
	++vec->end;
	return vec_ptr;
}

cVector_ptr cVectorPushAt(cVector_ptr vec_ptr, int64_t index, void* item)
{

}

cVector_ptr cVectorRemoveBack(cVector_ptr vec_ptr)
{

}

cVector_ptr cVectorRemoveAt(cVector_ptr vec_ptr, int64_t index)
{

}

inline size_t cVectorSize(cVector_ptr vec_ptr)
{
	const int32_t byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	cVector* vec = (int8_t*)vec_ptr - byteOffset;
	return vec->end;
}

cVector_ptr cVectorCreate(int64_t size, int32_t sizeInBytes)
{
	size = size <= 0 ? 10 : size;
	cVector *vec = malloc((sizeInBytes * size + sizeof(cVector)));
	if (!vec)
		return NULL;
	vec->sizeInBytes = sizeInBytes;
	vec->size = size;
	vec->end = 0;
	return &vec->v_array;
}

void cVectorDelete(cVector_ptr vec_ptr)
{
	const int byteOffset = sizeof(cVector) - sizeof(cVector_ptr);
	cVector* vec = (int8_t*)vec_ptr - byteOffset;
	free(vec);
	vec = NULL;
}

int main(void)
{
	return 0;
}