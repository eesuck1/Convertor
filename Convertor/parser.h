#ifndef PARSER_H
#define PARSER_H

#include "utilities.h"
#include "strings.h"
#include "graph.h"

strings get_lines(string file_path)
{
	FILE* file_pointer;
	fopen_s(&file_pointer, file_path.symbols, "r");

	if (file_pointer == NULL)
	{
		printf("File Reading is Failed %lu\n", GetLastError());

		exit(-1);
	}

	strings result = create_strings(MAX_LINES_NUMBER);

	char symbols[MAX_LINE_LENGTH];

	while (fgets(symbols, MAX_LINE_LENGTH, file_pointer))
	{
		string chars = to_string(symbols);
		string line = empty_string(chars.length);

		string_copy(&chars, &line);

		if (!string_in(line, whitespace))
		{
			strings_append(&result, line);
		}
	}

	return result;
}

strings skip_comments(strings line)
{
	strings result = create_strings(MAX_LINE_LENGTH);

	bool commenting = false;

	for (size_t index = 0; index < line.count; index++)
	{
		string symbol = strings_at(line, index);

		if (string_equal(symbol, comment_string))
		{
			commenting = !commenting;

			continue;
		}

		if (!commenting)
		{
			strings_append(&result, symbol);
		}
	}

	return result;
}

graph get_graph(strings lines) 
{
	string separator = to_string(" ");
	graph result = create_graph(lines.count);

	for (size_t index = 0; index < lines.count; index++)
	{
		strings line = string_split(strings_at(lines, index), separator);
		strings without_comments = skip_comments(line);

		// print_strings(without_comments, default_slice(without_comments));

		if (without_comments.count > 0)
		{
			graph_append(&result, without_comments);
		}
	}

	return result;
}

#endif // PARSER_H