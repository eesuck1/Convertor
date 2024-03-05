#ifndef UTILITIES_H
#define UTILITIES_H

#define MAX_LINE_LENGTH 512
#define MAX_LINES_NUMBER 2048

#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

#include "structures.h"
#include "strings.h"
#include "str.h"

static const string punctuation = { "!#$%&'()*+,-/:;<=>?@[\\]^`{|}~", 30 };
static const string whitespace = { " \t\n\r\v\f", 7 };
static const string latin_lower_alphabet = { "abcdefghijklmnopqrstuvwxyz", 27 };
static const string latin_upper_alphabet = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 27 };
static const string cyrillic_lower_alphabet = { "ÀÁÂÃ¥ÄÅªÆÇÈ²¯ÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÜŞß", 34 };
static const string cyrillic_upper_alphabet = { "àáâã´äåºæçè³¿éêëìíîïğñòóôõö÷øùüşÿ", 34 };


strings string_split(string line, string separator)
{
	strings result = create_strings(MAX_LINE_LENGTH);

	size_t start_index = 0;
	size_t end_index = line.length - 1;

	if (!string_in(line, separator))
	{
		strings_append(&result, line);

		return result;
	}

	size_t counter = string_count(line, separator);

	for (size_t index = 0; index < line.length; index++)
	{
		slice index_slice = { index, separator.length + index, 1 };

		if (counter == 0)
		{
			slice sub_string_slice = { start_index, line.length, 1 };

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

slice get_default_slice(strings strings)
{
	slice slice = { 0, strings.count, 1 };

	return slice;
}

void print_strings_default(strings strings)
{
	print_strings(strings, get_default_slice(strings));
}

void clear_strings(strings* strings)
{
	for (size_t index = 0; index < strings->count; index++)
	{
		strings->values[index] = empty_string(0);
	}

	strings->count = 0;
}

void strings_pop(strings* strings)
{
	strings->values[strings->count--] = empty_string(0);
}

#endif // UTILITIES_H