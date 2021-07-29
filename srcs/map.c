#include "../include/fract.h"

int	*setbound(int start1, int stop1, int start2, int stop2)
{
	int	*bound;

	bound = (int *)malloc(sizeof(int) * 4);
	bound[0] = start1;
	bound[1] = stop1;
	bound[2] = start2;
	bound[3] = stop2;
	return (bound);
}

/*
** It provides the same function as map() of p5.js
*/
int	map(int	value, int *bound)
{
	const unsigned int size1 = abs(bound[1] - bound[0]);
	const unsigned int size2 = abs(bound[3] - bound[2]);

	if (bound[3] > bound[2])
		value = bound[2] + (abs(value - bound[0]) * size2) / size1;
	else
		value = bound[2] - (abs(value - bound[0]) * size2) / size1;
	free(bound);
	return (value);
}
