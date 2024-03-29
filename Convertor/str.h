#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

#include "structures.h"
#include "constants.h"
#include "slice.h"


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

	for (size_t index = 0; index <= line.length - sub_string.length; index++)
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
	line->symbols[line->length++ - 1] = symbol;
}

void string_pop(string* line)
{
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

size_t string_count(string sub_string, string line)
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

void string_copy(string source, string destination)
{
	if (source.length != destination.length)
	{
		printf("String Lengths are not Consistent!\n");

		exit(-1);
	}

    memcpy(destination.symbols, source.symbols, source.length);
}

void string_upper(string* line)
{
	for (size_t index = 0; index < line->length; index++)
	{
		string sub_string = string_slice(*line, (slice) { index, index + 1, 1 });

		size_t latin_index = string_find(latin_lower_alphabet, sub_string);
		size_t cyrillic_index = string_find(cyrillic_lower_alphabet, sub_string);

		if (latin_index != ULLONG_MAX)
		{
			line->symbols[index] = latin_upper_alphabet.symbols[latin_index];
		}
		if (cyrillic_index != ULLONG_MAX)
		{
			line->symbols[index] = cyrillic_upper_alphabet.symbols[cyrillic_index];
		}
	}
}

void string_lower(string* line)
{
	for (size_t index = 0; index < line->length; index++)
	{
		string sub_string = string_slice(*line, (slice) { index, index + 1, 1 });

		size_t latin_index = string_find(latin_upper_alphabet, sub_string);
		size_t cyrillic_index = string_find(cyrillic_upper_alphabet, sub_string);

		if (latin_index != ULLONG_MAX)
		{
			line->symbols[index] = latin_lower_alphabet.symbols[latin_index];
		}
		if (cyrillic_index != ULLONG_MAX)
		{
			line->symbols[index] = cyrillic_lower_alphabet.symbols[cyrillic_index];
		}
	}
}

#endif // !STR_H
