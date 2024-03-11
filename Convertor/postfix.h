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

    strings copy = create_strings(expression.capacity);
    strings_copy(expression, &copy);

    while (copy.count > 0)
    {
        string unit = strings_pop(&copy);

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

string calculate_binary(string first, string second, string binary)
{
    char symbol = binary.symbols[0];
    double first_number = string_to_double(first);
    double second_number = string_to_double(second);

    switch (symbol)
    {
        case '+':
            return double_to_string(first_number + second_number);
        case '-':
            return double_to_string(first_number - second_number);
        case '*':
            return double_to_string(first_number * second_number);
        case '/':
            return double_to_string(first_number / second_number);
        default:
            printf("%s is not an operator!\n", binary.symbols);

            exit(-1);
    }
}

double calculate_postfix(strings expression)
{
    size_t pointer = 0;

    strings copy = create_strings(expression.capacity);
    strings_copy(expression, &copy);

    while (copy.count > 1)
    {
        string token = strings_at(copy, pointer);

        if (is_number(token))
        {
            pointer++;
        }
        else if (is_operator(token))
        {
            string first = strings_pop_at(&copy, pointer - 2);
            string second = strings_pop_at(&copy, pointer - 2);

            string binary = strings_at(copy, pointer - 2);

            string result = calculate_binary(first, second, binary);
            strings_set(&copy, pointer - 2, result);

            pointer -= 1;
        }
        else
        {
            printf("Unknown Symbol!\n");

            exit(-1);
        }
    }

    return string_to_double(strings_top(copy));
}

#endif // POSTFIX_H