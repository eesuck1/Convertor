#include <stdio.h>

#include "parser.h"
#include "utilities.h"


int main(void)
{
	string file_path = to_string("C:\\Git\\Convertor\\Convertor\\Assets\\Tests\\first_test.tirac");
	vector lines = get_lines(file_path);
	
	print_vector_default(lines);

	return 0;
}