#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
	char* symbols;
	size_t length;
} string;

typedef struct {
	size_t low;
	size_t high;
	size_t step;
} slice;

typedef struct {
	string* values;
	size_t capacity;
	size_t count;
} strings;

typedef struct {
	strings* values;
	size_t capacity;
	size_t count;
} graph;

typedef struct {
    string type;
    string name;
    string value;
} variable;

typedef struct {
    variable* variables;
    size_t capacity;
    size_t count;
} variables;

#endif // STRUCTURES_H