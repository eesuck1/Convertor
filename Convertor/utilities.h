#ifndef UTILITIES_H
#define UTILITIES_H

#define MAX_LINE_LENGTH 512
#define MAX_LINES_NUMBER 2048

#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

#include "structures.h"
#include "vector.h"

static const string punctuation = { "!#$%&'()*+,-/:;<=>?@[\\]^`{|}~", 30 };
static const string whitespace = { " \t\n\r\v\f", 7 };

string to_string(const char* line)
{
	string string = { line, strlen(line) };

	return string;
}

string empty_string(size_t length)
{
	string line = {
		(char*)VirtualAlloc(NULL, length * sizeof(char), MEM_COMMIT, PAGE_READWRITE),
		length
	};

	return line;
}

string full_string(size_t length, const char symbol)
{
	string line = {
		(char*)malloc(length * sizeof(char)),
		length
	};

	for (size_t index = 0; index < length; index++)
	{
		line.symbols[index] = symbol;
	}

	return line;
}

void print_string(string line)
{
	printf("%s\n", line.symbols);
}

size_t slice_length(slice slice)
{
	double fractional = (double)(slice.high - slice.low) / slice.step;
	size_t plus_one = (fractional - (size_t)(fractional)) == 0 ? 0 : 1;

	return (size_t)fractional + plus_one;
}

string string_slice(string line, slice slice)
{
	string temp = empty_string(slice_length(slice));

	for (size_t index = 0; index < temp.length; index++)
	{
		temp.symbols[index] = line.symbols[slice.low + index * slice.step];
	}

	return temp;
}

bool string_equal(string first, string second)
{
	if (first.length != second.length)
	{
		return false;
	}

	for (size_t index = 0; index < first.length; index++)
	{
		if (first.symbols[index] != second.symbols[index])
		{
			return false;
		}
	}

	return true;
}

bool string_in(string sub_string, string line)
{
	if (sub_string.length > line.length)
	{
		return false;
	}

	for (size_t index = 0; index < line.length - sub_string.length; index++)
	{
		slice slice = { index, sub_string.length + index, 1 };

		if (string_equal(string_slice(line, slice), sub_string))
		{
			return true;
		}
	}

	return false;
}

void string_append(string* line, char symbol)
{
	assert(false && "Not Properly Implemented Right Now!");

	line->symbols[line->length++ - 1] = symbol;
}

void string_pop(string* line)
{
	// assert(false && "Not Properly Implemented Right Now!");

	line->symbols[line->length--] = 0;
}

size_t string_find(string line, string sub_string)
{
	for (size_t index = 0; index < line.length - sub_string.length; index++)
	{
		slice slice = { index, sub_string.length + index, 1 };

		if (string_equal(string_slice(line, slice), sub_string))
		{
			return index;
		}
	}

	return ULLONG_MAX;
}

void string_replace(string* line, string original, string new)
{
	size_t base = string_find(*line, original);

	if (base == ULLONG_MAX)
	{
		printf("String: %s does not contain %s\n", line->symbols, original.symbols);

		return;
	}

	if (original.length != new.length)
	{
		printf("New Substring length is not equal to Original Substring\n");

		exit(-1);
	}

	for (size_t index = 0; index < new.length; index++)
	{
		line->symbols[index + base] = new.symbols[index];
	}
}

size_t string_count(string line, string sub_string)
{
	size_t counter = 0;

	for (size_t index = 0; index < line.length; index++)
	{
		slice slice = { index, sub_string.length + index, 1 };

		if (string_equal(string_slice(line, slice), sub_string))
		{
			counter++;
		}
	}

	return counter;
}

strings string_split(string line, string separator)
{
	strings result = create_vector(MAX_LINE_LENGTH);
	
	size_t start_index = 0;
	size_t end_index = line.length - 1;

	if (!string_in(line, separator))
	{
		vector_append(&result, line);

		return result;
	}

	size_t counter = string_count(line, separator);

	for (size_t index = 0; index < line.length; index++)
	{
		slice index_slice = { index, separator.length + index, 1 };

		if (counter == 0)
		{
			slice sub_string_slice = { start_index, line.length, 1 };

			vector_append(&result, string_slice(line, sub_string_slice));

			break;
		}

		if (string_equal(string_slice(line, index_slice), separator))
		{
			counter--;
			end_index = index;

			slice sub_string_slice = { start_index, end_index, 1 };

			vector_append(&result, string_slice(line, sub_string_slice));

			start_index = end_index + separator.length;
		}
	}

	return result;
}

void print_vector(strings vector, slice slice)
{
	if (vector.count == 0)
	{
		printf("\nVector is Empty\n");

		return;
	}

	if (slice.high > vector.count)
	{
		printf("\nSlice upper Bound bigger than number of Vector elements\n");

		return;
	}

	printf("\nFirst %zu Vector Values\n\n", slice_length(slice));

	for (size_t index = slice.low; index < slice.high; index += slice.step)
	{
		printf("vector[%zu] = %s\n", index, vector.values[index].symbols);
	}
}

void clear_vector(strings* vector)
{
	for (size_t index = 0; index < vector->count; index++)
	{
		vector->values[index] = empty_string(0);
	}

	vector->count = 0;
}

void vector_pop(strings* vector)
{
	vector->values[vector->count--] = empty_string(0);
}

slice get_default_slice(strings vector)
{
	slice slice = { 0, vector.count, 1 };

	return slice;
}

void print_vector_default(strings vector)
{
	print_vector(vector, get_default_slice(vector));
}

void string_copy(string* source, string* destination)
{
	if (source->length != destination->length)
	{
		printf("String Lengths are not Consistent!\n");
		
		exit(-1);
	}

	for (size_t index = 0; index < source->length; index++)
	{
		destination->symbols[index] = source->symbols[index];
	}
}

#endif // UTILITIES_H