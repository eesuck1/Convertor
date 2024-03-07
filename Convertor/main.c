#include <stdio.h>

#include "parser.h"
#include "utilities.h"


int main(void)
{
	string file_path = to_string("C:\\Git\\Convertor\\Convertor\\Assets\\Tests\\first_test.tirac");
	strings lines = get_lines(file_path);

	graph parsed = get_graph(lines);

	for (size_t index = 0; index < lines.count; index++)
	{
		print_strings(parsed.values[index], default_slice(parsed.values[index]));
	}

	return 0;
}