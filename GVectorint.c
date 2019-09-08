#include "GVectorInt.h"


ErrorCode dupVector(Vector *vector)
{
	if(vector == NULL)
	{
		return E_NULL_PTR;
	}
	printf(" ***************Fat dupVector****************8\n");

	vector->m_arr = realloc(vector->m_arr, vector->capacity * 2 * vector->data_size);

	if(NULL != vector->m_arr)
	{
		vector->capacity *= 2;
		return E_OK;

	}
	else 
	{
		return E_ALLOCATION_ERROR;
	}

	return E_OK;
}


Vector* vectorCreate(size_t size, size_t data_size){
	Vector *v = malloc(sizeof(Vector));
	v->size = 0;
	v->capacity = size;
	v->m_arr = malloc(data_size * size);
	v->data_size = data_size;
	return v;
}

void vectorDestroy(Vector **vector){
	free((*vector)->m_arr);
	free(*vector);
	*vector = NULL;
}


ErrorCode vectorPush(Vector *vector, T value)
{
	ErrorCode err = E_OK;

	if(vector == NULL)
	{
		return E_NULL_PTR;
	}

	if(vector->size >= vector->capacity)
	{
		err = dupVector(vector);
		/*memcpy((((char*)vector->m_arr) + (vector->size * vector->data_size)), value, vector->data_size);
		(vector->size)++;
		return err;*/
	}

	memcpy((((char*)vector->m_arr) + (vector->size * vector->data_size)), value, vector->data_size);
	(vector->size)++;
	return err;
	
}


ErrorCode vectorInsert(Vector *vector, T value, size_t index)
{	
	ErrorCode err = E_OK;

	if(vector == NULL)
	{
		return E_NULL_PTR;
	}

	if(index >= vector->size)
	{
		return E_BAD_INDEX;
	}
	

	if(vector->size >= vector->capacity)
	{
		err = dupVector(vector);
	}

	(vector->size)++;

	memmove((char*)vector->m_arr + ((index + 1) * vector->data_size) , (char*)vector->m_arr + (index * vector->data_size)  , (vector->size - index) * vector->data_size );

	memcpy(((char*)vector->m_arr + (index * vector->data_size)), value, vector->data_size);

	return err;
}


ErrorCode vectorPop(Vector *vector, T res)
{
	if(vector == NULL)
	{
		return E_NULL_PTR;
	}

/*	*res = *(vector->m_arr + vector->size - 1);
*/	memcpy(res ,((char*)vector->m_arr) + ((vector->size - 1) * vector->data_size), vector->data_size);

	vector->size--;
	return E_OK;
}


ErrorCode vectorRemove(Vector *vector, size_t index, T res)
{
	if(vector == NULL)
	{
		return E_NULL_PTR;
	}

	if(index >= vector->size)
	{
		return E_BAD_INDEX;
	}

/*	*res = *(vector->m_arr + index);
*/	memcpy(res ,((char*)vector->m_arr) + (index * vector->data_size), vector->data_size);
	memmove((char*)vector->m_arr + (index * vector->data_size) , (char*)vector->m_arr + ((index + 1) * vector->data_size)  , (vector->size - index) * vector->data_size );
	(vector->size)--;
	return E_OK;

}


ErrorCode vectorGetElement(const Vector *vector, size_t index, T value)
{
	if(vector == NULL)
	{
		return E_NULL_PTR;
	}

	if(index >= vector->size)
	{
		return E_BAD_INDEX;
	}

/*	*res = *(vector->m_arr + index);
*/	memcpy(value ,((char*)vector->m_arr) + (index * vector->data_size), vector->data_size);

	return E_OK;

}

ErrorCode vectorSetElement(Vector *vector, size_t index, T value)
{
	if(vector == NULL)
	{
		return E_NULL_PTR;
	}

	if(index >= vector->size)
	{
		return E_BAD_INDEX;
	}

/*	*(vector->m_arr + index) = value;
*/	memcpy(((char*)vector->m_arr) + (index * vector->data_size), value ,vector->data_size);

	return E_OK;
}



size_t vectorCount(const Vector *vector, T value)
{
	size_t i, count;
	count = 0;
	for(i = 0; i < vector->size; i++)
	{
/*		if(*((char*)vector->m_arr + i * vector->data_size) == value) */
		if(memcmp(((char*)vector->m_arr + i * vector->data_size), value, vector->data_size) == 0)
		
		{
			count++;
		}
	}
	return count;
}


void vectorPrint(Vector *vector, printFunc func)
{
	size_t i;


	for(i = 0; i < vector->size; i++)
	{
		/*printf("%d\n", *(vector->m_arr + i));*/
		func(i, (char*)(vector->m_arr) + (i * vector->data_size));
	}
	 
}

void printInt(size_t idx, void *v)
{
	printf("vector[%lu] = %d\n",idx, *((int *)v));
}

void printfloat(size_t idx, void *v)
{
	printf("vector[%lu] = %f\n",idx, *((float *)v));
}

/*
int main()
{
	size_t i;
	float a ;
	int b;
	void *res = malloc(sizeof(int *));
	Vector *floatVector;
	Vector *intVector = vectorCreate(2, sizeof(int));
	for (i = 0; i < 5; ++i){
		vectorPush(intVector, &i); 
		
	}
	b = 100;
	vectorInsert(intVector, &b, 0);

	vectorPrint(intVector, printInt);
	
	printf("size of vector = %lu\n", vectorGetSize(intVector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(intVector));
	printf("after pop\n");
	vectorPop(intVector, res);
	vectorPrint(intVector, printInt);
	printf("poped val = %d\n", *(int *)res);

	printf("size of vector = %lu\n", vectorGetSize(intVector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(intVector));


	vectorRemove(intVector, 2, res);
	printf("after remove 2\n");
	vectorPrint(intVector, printInt);
	printf("size of vector = %lu\n", vectorGetSize(intVector));
		printf("vectorGetCapacity = %lu\n", vectorGetCapacity(intVector));

	vectorGetElement(intVector, 2, res);
	printf("vectorGetElement 2 = %d\n",*(int *)res );


	*(int* )res = 5;
	vectorSetElement(intVector, 3, res);
	printf("after set 3 to 5\n");
	vectorPrint(intVector, printInt);
	printf("size of vector = %lu\n", vectorGetSize(intVector));
		printf("vectorGetCapacity = %lu\n", vectorGetCapacity(intVector));

	*(int* )res = 100;
	vectorInsert(intVector, res, 1);
		vectorPrint(intVector, printInt);

		printf("size of vector = %lu\n", vectorGetSize(intVector));
			printf("vectorGetCapacity = %lu\n", vectorGetCapacity(intVector));


	vectorInsert(intVector, res, 1);
		vectorPrint(intVector, printInt);

	printf("size of vector = %lu\n", vectorGetSize(intVector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(intVector));

	vectorInsert(intVector, res, 1);
		vectorPrint(intVector, printInt);

	printf("size of vector = %lu\n", vectorGetSize(intVector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(intVector));


	vectorInsert(intVector, res, 1);
		vectorPrint(intVector, printInt);


	vectorInsert(intVector, res, 1);
		vectorPrint(intVector, printInt);

	printf("size of vector = %lu\n", vectorGetSize(intVector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(intVector));

	printf("size of vector = %lu\n", vectorGetSize(intVector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(intVector));

	printf("ammount of 100 values = %lu\n", vectorCount(intVector, res));
	*(int* )res = 1;
	printf("ammount of 1 values = %lu\n", vectorCount(intVector, res));
		*(int* )res = 5;

	printf("ammount of 5 values = %lu\n", vectorCount(intVector, res));

	vectorDestroy(&intVector);
	free(res);


	a = 0.0f;
	floatVector = vectorCreate(5, sizeof(float));
	
	for (i = 0; i < 5; ++i){
		vectorPush(floatVector, &a);
		a++; 
	}
	a = 100.0f;
	vectorInsert(floatVector, &a, 0);

	vectorPrint(floatVector, printfloat);
	printf("Hello \n");
	printf("size of vector = %lu\n", vectorGetSize(floatVector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(floatVector));

	vectorDestroy(&floatVector);

	return 0;
}*/

/*int main()
{

	Vector *vector = vectorCreate(1);
	int * a = malloc(sizeof(int));


	int i;

printf("size of vector = %lu\n", vectorGetSize(vector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(vector));
	for (i = 0; i < 5; ++i){
		vectorPush(vector, i); 
		
	}
	printf("size of vector = %lu\n", vectorGetSize(vector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(vector));

	
	vectorInsert(vector, 100, 0);

	vectorPrint(vector);

	printf("size of vector = %lu\n", vectorGetSize(vector));
		printf("vectorGetCapacity = %lu\n", vectorGetCapacity(vector));


	printf("after pop\n");
	vectorPop(vector, a);
	vectorPrint(vector);
	printf("size of vector = %lu\n", vectorGetSize(vector));
		printf("vectorGetCapacity = %lu\n", vectorGetCapacity(vector));



	printf("poped val = %d\n", *a);

	vectorRemove(vector, 2, a);
	printf("after remove 2\n");
	vectorPrint(vector);
	printf("size of vector = %lu\n", vectorGetSize(vector));
		printf("vectorGetCapacity = %lu\n", vectorGetCapacity(vector));





	vectorGetElement(vector, 2, a);
	printf("vectorGetElement 2 = %d\n",*a ); 

	vectorSetElement(vector, 3, 5);
	printf("after set 3 to 5\n");
	vectorPrint(vector);
	printf("size of vector = %lu\n", vectorGetSize(vector));
		printf("vectorGetCapacity = %lu\n", vectorGetCapacity(vector));



	vectorInsert(vector, 100, 1);
		vectorPrint(vector);

		printf("size of vector = %lu\n", vectorGetSize(vector));
			printf("vectorGetCapacity = %lu\n", vectorGetCapacity(vector));


	vectorInsert(vector, 100, 1);
	vectorPrint(vector);

	printf("size of vector = %lu\n", vectorGetSize(vector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(vector));

	vectorInsert(vector, 100, 1);
	vectorPrint(vector);

	printf("size of vector = %lu\n", vectorGetSize(vector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(vector));


	vectorInsert(vector, 100, 1);
	vectorPrint(vector);


	vectorInsert(vector, 100, 1);
	vectorPrint(vector);

	printf("size of vector = %lu\n", vectorGetSize(vector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(vector));

	printf("size of vector = %lu\n", vectorGetSize(vector));
	printf("vectorGetCapacity = %lu\n", vectorGetCapacity(vector));

	printf("ammount of 100 values = %lu\n", vectorCount(vector, 100));
	printf("ammount of 1 values = %lu\n", vectorCount(vector, 1));
	printf("ammount of 5 values = %lu\n", vectorCount(vector, 5));

	vectorDestroy(&vector);
	free(a);

	return 0;
}*/