#ifndef UTILITIES_H
#define UTILITIES_H

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 512
#endif // MAX_LINE_LENGTH

#ifndef MAX_LINES_NUMBER
#define MAX_LINES_NUMBER 2048
#endif // MAX_LINES_NUMBER

#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <assert.h>
#include <stdlib.h>

#include "structures.h"
#include "strings.h"
#include "str.h"


strings string_split(string line, string separator)
{
	strings result = create_strings(MAX_LINE_LENGTH);

	size_t start_index = 0;
	size_t end_index = line.length - 1;

	if (!string_in(separator, line))
	{
		strings_append(&result, line);

		return result;
	}

	size_t counter = string_count(separator, line);

	for (size_t index = 0; index < line.length; index++)
	{
		slice index_slice = { index, separator.length + index, 1 };

		if (counter == 0)
		{
			slice sub_string_slice = { start_index, line.length - 1, 1 };

			strings_append(&result, string_slice(line, sub_string_slice));

			break;
		}

		if (string_equal(string_slice(line, index_slice), separator))
		{
			counter--;
			end_index = index;

			slice sub_string_slice = { start_index, end_index, 1 };

			strings_append(&result, string_slice(line, sub_string_slice));

			start_index = end_index + separator.length;
		}
	}

	return result;
}

slice default_slice(strings strings)
{
	slice slice = { 0, strings.count, 1 };

	return slice;
}

void print_strings_default(strings strings)
{
	print_strings(strings, default_slice(strings));
}

void clear_strings(strings* strings)
{
	for (size_t index = 0; index < strings->count; index++)
	{
		strings->values[index] = empty_string(0);
	}

	strings->count = 0;
}

string strings_pop(strings* strings)
{
    string value = strings->values[strings->count - 1];
	strings->values[strings->count--] = empty_string(0);

    return value;
}

string strings_pop_at(strings* strings, size_t value_index)
{
    string value = strings_at(*strings, value_index);

    for (size_t index = value_index; index < strings->count - 1; index++)
    {
        strings->values[index] = strings->values[index + 1];
    }

    strings_pop(strings);

    return value;
}

strings strings_reverse(strings original)
{
    strings reversed = create_strings(original.count + 1);
    size_t expression_count = original.count;

    for (size_t index = 1; index <= expression_count; index++)
    {
        strings_append(&reversed, strings_at(original, expression_count - index));
    }

    return reversed;
}

bool is_number(string line)
{
    bool dot = false;

    for (size_t index = 0; index < line.length; index++)
    {
        char symbol = line.symbols[index];

        if (symbol == '.')
        {
            if (dot)
            {
                return false;
            }

            dot = true;
        }

        if (!isdigit(symbol) && !dot)
        {
            return false;
        }
    }

    return true;
}

bool is_operator(string line)
{
    return string_in(line, operators);
}

double string_to_double(string value)
{
    char* end_pointer = NULL;
    double result = strtod(value.symbols, end_pointer);

    if (end_pointer != NULL)
    {
        printf("Error while converting %s to double at symbol %c", value.symbols, *end_pointer);

        exit(-1);
    }

    return result;
}

#endif // UTILITIES_H