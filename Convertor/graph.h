#ifndef GRAPH_H
#define GRAPH_H

#include <windows.h>
#include "structures.h"

graph create_graph(size_t capacity)
{
	graph graph = {
		(strings*)VirtualAlloc(NULL, capacity, MEM_COMMIT, PAGE_READWRITE),
		capacity,
		0
	};

	return graph;
}

void graph_append(graph* graph, strings value)
{
	if (graph->count == graph->capacity)
	{
		printf("Graph is Full");

		return;
	}

	graph->values[graph->count++] = value;
}

#endif // !GRAPH_H
