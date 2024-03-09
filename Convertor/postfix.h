#ifndef POSTFIX_H
#define POSTFIX_H

#include <limits.h>
#include <ctype.h>

#include "strings.h"
#include "utilities.h"

typedef enum {
    plus = 1,
    minus = 1,
    multiplication = 2,
    division = 2,
    left_parenthesis = 0,
    right_parenthesis = 0,
} precedence;

precedence get_precedence(string unit)
{
    char symbol = unit.symbols[0];

    switch (symbol)
    {
        case '+':
            return plus;
        case '-':
            return minus;
        case '*':
            return multiplication;
        case '/':
            return division;
        case '(':
            return left_parenthesis;
        case ')':
            return right_parenthesis;
        default:
            printf("%s is not an operator!\n", unit.symbols);

            exit(-1);
    }
}

strings to_postfix(strings expression)
{
    strings output = create_strings(MAX_LINE_LENGTH);
    strings operators_stack = create_strings(MAX_LINE_LENGTH);

    string opened = to_string("(");
    string closed = to_string(")");

    while (expression.count > 0)
    {
        string unit = strings_pop(&expression);

        if (is_number(unit))
        {
            strings_append(&output, unit);
        }
        else if (is_operator(unit))
        {
            while (operators_stack.count > 0 && get_precedence(strings_top(operators_stack)) >= get_precedence(unit))
            {
                strings_append(&output, strings_pop(&operators_stack));
            }

            strings_append(&operators_stack, unit);
        }
        else if (string_equal(unit, opened))
        {
            strings_append(&operators_stack, unit);
        }
        else if (string_equal(unit, closed))
        {
            while (operators_stack.count > 0 && !string_equal(strings_top(operators_stack), opened))
            {
                strings_append(&output, strings_pop(&operators_stack));
            }

            if (string_equal(strings_top(operators_stack), opened))
            {
                strings_pop(&operators_stack);
            }
        }
    }

    while (operators_stack.count > 0)
    {
        strings_append(&output, strings_pop(&operators_stack));
    }

    return output;
}

double calculate_binary(string first, string second, string operator)
{
    char symbol = operator.symbols[0];

    switch (symbol)
    {
        case '+':
            return string_to_double(first) + string_to_double(second);
        case '-':
            return string_to_double(first) - string_to_double(second);
        case '*':
            return string_to_double(first) * string_to_double(second);
        case '/':
            return string_to_double(first) / string_to_double(second);
        default:
            printf("%s is not an operator!\n", operator.symbols);

            exit(-1);
    }
}

double calculate_postfix(strings expression)
{

}

#endif // POSTFIX_H