#pragma once

struct point
{
	double X;
	double Y;
};

typedef struct point Point;

double euclidean_distance(Point a, double row, double col);
