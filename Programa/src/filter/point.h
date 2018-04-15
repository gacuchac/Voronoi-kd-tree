#pragma once

/** Representa un punto en 2D */
typedef struct point Point;
int eucli;
/** Representa un punto en 2D */
struct point
{
	double X;
	double Y;
	int derecha;
	int izquierda;
	Point *right;
	Point *left;
	int posicion;
};

/** Obtiene la distancia entre un punto y un píxel de la imagen */
double euclidean_distance(Point *a, double row, double col);
/** Agrega un punto a la izquierda o la derecha*/
void point_append(Point *root, Point point, int comparacion);
/** Arma el arbol de puntos a partir de un root*/
void point_tree(Point *root, Point* arreglo, int comparacion, int nuclei_count);
/* Devuelve punto en que hay k elementos menores que él en el eje Y**/
Point qselectY(Point *v, int len, int k);
/* Devuelve punto en que hay k elementos menores que él en el eje X**/
Point qselectX(Point *v, int len, int k);
/** Inicializa variables para nearest_node*/
Point* nearest_root(Point *root, double row, double column);
/** Encuentra vecino mas cercano*/
double nearest_node(Point *root, double row, double column, int comparacion);
/** Retorna cuantas veces se llamo a euclidean_distance*/
int euclidean();
/** Libera memoria de arbol*/
void destroy_tree(Point *root, int primera_vez);
