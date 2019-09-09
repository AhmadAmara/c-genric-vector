#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	E_OK,
	E_NULL_PTR,
	E_UNDERFLOW,
	E_ALLOCATION_ERROR,
	E_BAD_INDEX
} ErrorCode;

typedef void * T;


struct Vector{
	T m_arr;
	size_t size;
	size_t capacity;
	size_t data_size;
};

typedef struct Vector Vector;

typedef void (*actionFunc)(size_t idx, T v);


Vector* vectorCreate(size_t size, size_t data_size);
void vectorDestroy(Vector **vector);

/* duplicate the vector */
ErrorCode dupVector(Vector* vector);

/* Adds an item at the end. Grows if needed (by * 2) */
ErrorCode vectorPush(Vector *vector, T value);

/* Adds an item at a certain position and shifts. Grows if needed (by * 2) */
ErrorCode vectorInsert(Vector *vector, T value, size_t index);

/* Clears the item at the end. Grows if needed (by * 2) */
ErrorCode vectorPop(Vector *vector, T res);

/* Clears an item at a certain position and shifts. */
ErrorCode vectorRemove(Vector *vector, size_t index, T res);

ErrorCode vectorGetElement(const Vector *vector, size_t index, T res);
ErrorCode vectorSetElement(Vector *vector, size_t index, T value);

size_t vectorGetSize(const Vector *vector){return vector->size;}
size_t vectorGetCapacity(const Vector *vector){return vector->capacity;}

/* Counts how many instances of a given value there are. */
size_t vectorCount(const Vector *vector, T value);

size_t vectorForEach(Vector* vector, actionFunc); 



#ifdef _DEBUG
void vectorPrint(Vector *vector, actionFunc func);
void printInt(size_t idx, void *v);

#endif /* _DEBUG */

#endif /* __VECTOR_H__ */

