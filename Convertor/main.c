#include <stdio.h>

#include "parser.h"
#include "utilities.h"


int main(void)
{
	//string file_path = to_string("C:\\Git\\Convertor\\Convertor\\Assets\\Tests\\first_test.tirac");
	//strings lines = get_lines(file_path);
	//
	//print_strings_default(lines);

	string test = to_string("VOloDicHka PuPiK");
	string_lower(&test);
	print_string(test);

	return 0;
}