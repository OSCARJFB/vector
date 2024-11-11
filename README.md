# cvector

Is a lighweight library bringing C a general solution for construction of dynamic arrays.
The library can allocate arrays of any datatype, native or user invented data structer.
However this libarary is probably no where near as efficient as the std::vector of c++,
but is easy to use and should be able to perform its basic purpose.

## Creation a vector:
This example show how a vector is created.
When creating a vector the caller must make sure to specify the size in 
bytes of the datatype/structure aimed to be stored in the container.

```
int* vec_num = vec_create(sizeof(int));
```

## Push back
This example show how to push an item to the end of the vector.

```
vec_num = vec_pushBack(vec_num, &i);
```

## Push at index
This example show how to push an item to a specific index (index 5 in the example).

```
vec_num = vec_push(vec_num, 5, &i);
```

## 2d array like structure
In this example it's shown how you may use the API to create a 2d like array.
```
int** vec_num2d = vec_create(sizeof(int));
for (size_t i = 0; i < vec_size(vec_num2d); ++i)
	vec_num2d[i] = vec_create(sizeof(int));
```