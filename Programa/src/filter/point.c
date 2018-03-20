#include "point.h"
#include <math.h>

double euclidean_distance(Point a, double row, double col)
{
	return sqrt(pow(a.X - col,2) + pow(a.Y - row, 2));
}
