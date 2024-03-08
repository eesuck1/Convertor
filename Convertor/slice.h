#ifndef SLICE_H
#define SLICE_H

#include "structures.h"

size_t slice_length(slice slice)
{
	double fractional = (double)(slice.high - slice.low) / (double)slice.step;
	size_t plus_one = (fractional - (size_t)(fractional)) == 0 ? 0 : 1;

	return (size_t)fractional + plus_one;
}

#endif // SLICE_H