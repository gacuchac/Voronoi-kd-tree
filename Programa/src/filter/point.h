#pragma once


/** Representa un punto en 2D */
struct point
{
	double X;
	double Y;
};

/** Representa un punto en 2D */
typedef struct point Point;

/** Obtiene la distancia entre un punto y un píxel de la imagen */
double euclidean_distance(Point a, double row, double col);
