#include <stdio.h>

#include "parser.h"
#include "utilities.h"
#include "postfix.h"


int main(void)
{
	string file_path = to_string("C:\\Git\\Convertor\\Convertor\\Assets\\Tests\\first_test.tirac");
	strings lines = get_lines(file_path);

	graph parsed = get_graph(lines);

    strings expression = strings_reverse(parsed.values[1]);
    to_postfix(expression);

    return 0;
}