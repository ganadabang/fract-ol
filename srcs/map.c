#include "../include/fract.h"

double	*setbound(double start1, double stop1, double start2, double stop2)
{
	double	*bound;

	bound = (double *)malloc(sizeof(double) * 4);
	bound[0] = start1;
	bound[1] = stop1;
	bound[2] = start2;
	bound[3] = stop2;
	return (bound);
}

/*
** It provides the same function as map() of p5.js
*/
double	map(double value, double *bound)
{
	value = bound[2] + (value - bound[0]) * fabs(bound[3] - bound[2]) / \
			fabs(bound[1] - bound[0]);
	free(bound);
	return (value);
}
