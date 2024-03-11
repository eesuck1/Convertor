#ifndef VARIABLES_H
#define VARIABLES_H

#define HASHING_CONSTANT 12

#include "structures.h"
#include "windows.h"
#include "math.h"

variables create_variables(size_t capacity)
{
    variables variables = {
            (variable*)VirtualAlloc(NULL, capacity * sizeof(variable), MEM_COMMIT, PAGE_READWRITE),
            capacity,
            0
    };

    return variables;
}

size_t variable_hash(variable value, size_t capacity)
{
    size_t result = ULLONG_MAX;

    for (size_t index = 0; index < value.name.length; index++)
    {
        result += value.name.symbols[index] * (size_t)pow(HASHING_CONSTANT, (double)index);
    }

    return result % capacity;
}

void variables_insert(variables* destination, variable value)
{
    size_t insert_index = variable_hash(value, destination->capacity);

    destination->variables[insert_index] = value;
    destination->count++;
}

variable variables_get(variables source, variable value)
{
    size_t index = variable_hash(value, source.capacity);

    return source.variables[index];
}

#endif // VARIABLES_H
