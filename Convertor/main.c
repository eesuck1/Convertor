#include <stdio.h>

#include "parser.h"
#include "utilities.h"
#include "postfix.h"

int main(void)
{
//	string file_path = to_string("C:\\Git\\Convertor\\Convertor\\Assets\\Tests\\first_test.tirac");
//	strings lines = get_lines(file_path);
//
//	graph parsed = get_graph(lines);
//
//    string result = parse_expression(parsed.values[1]);
//    print_string(result);

    variable var = create_variable(to_string("int"), to_string("x"), to_string("123"));
    variables variables = create_variables(10);

    variables_insert(&variables, var);

    print_string(variables_get(variables, var).name);

    return 0;
}