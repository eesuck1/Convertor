#ifndef VARIABLE_H
#define VARIABLE_H

#include "structures.h"
#include "str.h"

variable create_variable(string type, string name, string value)
{
    variable variable = {type, name, value};

    return variable;
}

void print_variable(variable variable)
{
    printf("%s %s = %s", variable.type.symbols, variable.name.symbols, variable.value.symbols);
}

#endif // VARIABLE_H