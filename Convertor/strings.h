#ifndef STRINGS_H
#define STRINGS_H

#include <windows.h>
#include <stdbool.h>

#include "structures.h"
#include "slice.h"


strings create_strings(size_t capacity)
{
	strings strings =
	{
		(string*)VirtualAlloc(NULL, capacity * sizeof(string), MEM_COMMIT, PAGE_READWRITE),
		capacity,
		0
	};

	return strings;
}

bool strings_is_empty(strings* strings)
{
	return strings->count == 0;
}

void full_strings(strings* strings, string value)
{
	for (size_t index = 0; index < strings->capacity; index++)
	{
		strings->values[index] = value;
	}

	strings->count = strings->capacity;
}

string strings_at(strings strings, size_t index)
{
	if (index > strings.count)
	{
        printf("Index %zu is out of %zu Count bounds\n", index, strings.count);

		exit(-1);
	}

	return strings.values[index];
}

void strings_set(strings* strings, size_t index, string value)
{
	if (index > strings->count)
	{
		printf("Index %zu is out of %zu Count bounds\n", index, strings->count);

		exit(-1);
	}
	strings->values[index] = value;
}

void strings_append(strings* strings, string value)
{
	if (strings->count == strings->capacity)
	{
		printf("strings is Full");

		return;
	}

	strings->values[strings->count++] = value;
}

void strings_free(strings* strings)
{
	strings->count = 0;
	VirtualFree(strings->values, 0, MEM_RELEASE);
}

void print_strings(strings strings, slice slice)
{
	if (strings.count == 0)
	{
		printf("\nStrings is Empty\n");

		return;
	}

	if (slice.high > strings.count)
	{
		printf("\nSlice upper Bound bigger than number of strings elements\n");

		return;
	}

	printf("\nFirst %zu Strings Values\n\n", slice_length(slice));

	for (size_t index = slice.low; index < slice.high; index += slice.step)
	{
		printf("Strings[%zu] = %s\n", index, strings.values[index].symbols);
	}
}

string strings_top(strings strings)
{
    return strings.values[strings.count - 1];
}

#endif // !STRINGS_H
