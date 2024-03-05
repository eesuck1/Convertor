#ifndef VECTOR_H
#define VECTOR_H

#include <windows.h>
#include <stdbool.h>

#include "structures.h"

string_vector create_vector(size_t capacity)
{
	string_vector vector =
	{
		(string*)VirtualAlloc(NULL, capacity * sizeof(string), MEM_COMMIT, PAGE_READWRITE),
		capacity,
		0
	};

	return vector;
}

bool vector_is_empty(string_vector* vector)
{
	return vector->count == 0;
}

void full_vector(string_vector* vector, string value)
{
	for (size_t index = 0; index < vector->capacity; index++)
	{
		vector->values[index] = value;
	}

	vector->count = vector->capacity;
}

string vector_get_by_index(string_vector vector, size_t index)
{
	if (index > vector.count || index < 0)
	{
		printf("Index is out of bounds\n");

		exit(-1);
	}

	return vector.values[index];
}

void vector_set_by_index(string_vector* vector, size_t index, string value)
{
	if (index > vector->count || index < 0)
	{
		printf("Index is out of bounds\n");

		exit(-1);
	}
	vector->values[index] = value;
}

void vector_append(string_vector* vector, string value)
{
	if (vector->count == vector->capacity)
	{
		printf("Vector is Full");

		return;
	}

	vector->values[vector->count++] = value;
}

void vector_free(string_vector* vector)
{
	vector->count = 0;
	VirtualFree(vector->values, 0, MEM_RELEASE);
}

#endif // !VECTOR_H
