#ifndef PARSER_H
#define PARSER_H

#include "utilities.h"
#include "vector.h"

vector get_lines(string file_path)
{
	FILE* file_pointer;
	fopen_s(&file_pointer, file_path.symbols, "r");

	if (file_pointer == NULL)
	{
		printf("File Reading is Failed %d\n", GetLastError());

		exit(-1);
	}

	vector result = create_vector(MAX_LINES_NUMBER);

	char* symbols = "";
	while (fgets(symbols, MAX_LINE_LENGTH, file_pointer))
	{
		string chars = to_string(symbols);
		string line = empty_string(chars.length);

		string_copy(&chars, &line);

		if (!string_in(line, whitespace))
		{
			vector_append(&result, line);
		}
	}

	return result;
}

void translate(vector lines) {}

#endif // PARSER_H