#include "point.h"
#include <math.h>


/** Obtiene la distancia entre un punto y un píxel de la imagen */
double euclidean_distance(Point a, double row, double col)
{
	return sqrt(pow(a.X - col,2) + pow(a.Y - row, 2));
}
