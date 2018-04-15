#include "point.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Variables globales
double distancia;
Point* vecino = NULL;

/** Obtiene la distancia entre un punto y un píxel de la imagen */
double euclidean_distance(Point *a, double row, double col)
{
	eucli++;
	return sqrt(pow(a->X - col,2) + pow(a->Y - row, 2));
}
/** Agrega un punto a la izquierda o la derecha*/
void point_append(Point *root, Point point, int comparacion)
{
	// Si comparacion == 0 comparamos eje X, si no, comparamos eje Y
	// Comparamos eje Y
	if(comparacion == 1)
	{
		// Vemos si es menor que root en eje Y
		if (point.Y < root->Y) {
			// Si hay nodo a la izquierda
			if (root->izquierda == 1) {
				// Comparamos eje X con punto de la izquierda
				point_append(root->left, point, 0);
			}
			// No hay nodo a la izquierda
			else
			{
				// Le asignamos el punto como nodo
				root->left = malloc(sizeof(Point));
				// punto->derecha = 0;
				// punto->izquierda = 0;
				// punto->X = point.X;
				// punto->Y = point.Y;
				// punto->posicion = point.posicion;
				// root->left = punto;
				// root->izquierda = 1;

				root->left->derecha = 0;
				root->left->izquierda = 0;
				root->left->X = point.X;
				root->left->Y = point.Y;
				root->left->posicion = point.posicion;
				root->izquierda = 1;
			}
		}
		// Es mayor que root en eje Y
		else
		{
			// Si hay nodo derecha
			if (root->derecha == 1) {
				// Comparamos con nodo derecha
				point_append(root->right, point, 0);
			}
			// No hay nodo a la derecha
			else
			{
				// Le asignamos el punto como nodo
				root->right = malloc(sizeof(Point));
				// punto->derecha = 0;
				// punto->izquierda = 0;
				// punto->X = point.X;
				// punto->Y = point.Y;
				// punto->posicion = point.posicion;
				// root->right = punto;
				// root->derecha = 1;

				root->right->derecha = 0;
				root->right->izquierda = 0;
				root->right->X = point.X;
				root->right->Y = point.Y;
				root->right->posicion = point.posicion;
				root->derecha = 1;
			}
		}
	}

	// Comparamos eje X
	else
	{
		// Vemos si es menor que root en eje X
		if (point.X < root->X) {
			// Si hay nodo a la izquierda
			if (root->izquierda == 1) {
				// Comparamos eje X con punto de la izquierda
				point_append(root->left, point, 1);
			}
			// No hay nodo a la izquierda
			else
			{
				// Le asignamos el punto como nodo
				root->left = malloc(sizeof(Point));
				// punto->derecha = 0;
				// punto->izquierda = 0;
				// punto->X = point.X;
				// punto->Y = point.Y;
				// punto->posicion = point.posicion;
				// root->left = punto;
				// root->izquierda = 1;

				root->left->derecha = 0;
				root->left->izquierda = 0;
				root->left->X = point.X;
				root->left->Y = point.Y;
				root->left->posicion = point.posicion;
				root->izquierda = 1;
			}
		}
		// Es mayor que root en eje X
		else
		{
			// Si hay nodo derecha
			if (root->derecha == 1) {
				// Comparamos con nodo derecha
				point_append(root->right, point, 1);
			}
			// No hay nodo a la derecha
			else
			{
				// Le asignamos el punto como nodo
				root->right = malloc(sizeof(Point));
				// punto->derecha = 0;
				// punto->izquierda = 0;
				// punto->X = point.X;
				// punto->Y = point.Y;
				// punto->posicion = point.posicion;
				root->right->derecha = 0;
				root->right->izquierda = 0;
				root->right->X = point.X;
				root->right->Y = point.Y;
				root->right->posicion = point.posicion;
				root->derecha = 1;
				// root->right = punto;
			}
		}
	}
}
// Adaptado de https://wikicoding.org/wiki/c/Quickselect/
/* Intercambia puntos del arreglo**/
void swap(int num1, int num2, Point* nucleos) {
   Point temp = nucleos[num1];
   nucleos[num1] = nucleos[num2];
   nucleos[num2] = temp;
}
/* Devuelve punto en que hay k elementos menores que él en el eje X**/
Point qselectX(Point *v, int len, int k)
{
	int i = 0, st = 0;

	for (st = i = 0; i < len - 1; i++) {
		if (v[i].X > v[len-1].X) continue;
		swap(i, st, v);
		st++;
	}

	swap(len-1, st,v);

	return k == st	?v[st]
			:st > k	? qselectX(v, st, k)
				: qselectX(v + st, len - st, k - st);
}
/* Devuelve punto en que hay k elementos menores que él en el eje Y**/
Point qselectY(Point *v, int len, int k)
{
	int i, st;

	for (st = i = 0; i < len - 1; i++) {
		if (v[i].Y > v[len-1].Y) continue;
		swap(i, st, v);
		st++;
	}

	swap(len-1, st,v);

	return k == st	? v[st]
			:st > k	? qselectY(v, st, k)
				: qselectY(v + st, len - st, k - st);
}
void point_print(Point *nuclei, int nuclei_count)
{
	for (int i = 0; i < nuclei_count; i++) {
	 printf("Nucleo X: %f ; Y:%f\n",nuclei[i].X,nuclei[i].Y);
	}
}
/** Arma el arbol de puntos a partir de un root*/
void point_tree(Point *root, Point* nuclei, int comparacion, int nuclei_count)
{
	if (nuclei_count == 0) {
		return;
	}
	// printf("nuclei_count: %i\n", nuclei_count);
	int medio = (int) nuclei_count/2;
	// printf("medio: %i\n",medio);

	// printf("medio: %i\n", medio);
	// printf("Arreglo nuclei\n");
	// point_print(nuclei, nuclei_count);
	// Si comparacion == 0, tomamos medianaX, si no, medianaY
	if (comparacion) {
		if (nuclei_count == 1) {
			// printf("Queda un nucleo\n");
			point_append(root, nuclei[0], 0);
		}

		// Si quedan puntos
		else
		{
			Point medianaY = qselectY(nuclei, nuclei_count, medio);
			// printf("medianaY: %f;%f\n",medianaY.X,medianaY.Y);
			// printf("MedianaY X: %f ; Y: %f\n",medianaY.X, medianaY.Y);
			point_append(root, medianaY, 0);
			Point *izquierda = malloc(medio*sizeof(Point));
			int izq = 0;
			int tamanio = nuclei_count-medio-1;
			Point *derecha = malloc(tamanio*sizeof(Point));
			int der = 0;

			for (int i = 0; i < nuclei_count; i++) {
				//printf("Mediana Y: %f Nucleo Y: %f\n",medianaY.Y,nuclei[i].Y);
				if (nuclei[i].Y < medianaY.Y) {
					izquierda[izq] = nuclei[i];
					izq++;
				}
				else if (nuclei[i].Y > medianaY.Y) {
					derecha[der] = nuclei[i];
					der++;
				}
			}

			// agregamos la proxima medianaX  recursivamente
			point_tree(root, izquierda, 0, medio);
			point_tree(root, derecha, 0, tamanio);
			free(izquierda);
			free(derecha);
		}

	}

	// Comparamos eje X
	else
	{
		if (nuclei_count == 1) {
			// printf("Queda un nucleo\n");
			point_append(root, nuclei[0], 0);
		}
		else
		{
			Point medianaX = qselectX(nuclei, nuclei_count, medio);
			// printf("medianaX: %f;%f\n",medianaX.X,medianaX.Y);
			point_append(root, medianaX, 0);
			// Si quedan puntos
			Point *izquierda = malloc(medio*sizeof(Point));
			int izq = 0;
			int tamanio = nuclei_count-medio-1;

			Point *derecha = malloc(tamanio*sizeof(Point));
			int der = 0;

			for (int i = 0; i < nuclei_count; i++) {
				//printf("Mediana X: %f Nucleo X: %f\n",medianaX.X,nuclei[i].X);
				if (nuclei[i].X < medianaX.X) {
					izquierda[izq] = nuclei[i];
					izq++;
				}
				else if (nuclei[i].X > medianaX.X) {
					derecha[der] = nuclei[i];
					der++;
				}
			}
			// for (int i = 0; i < medio; i++) {
			// 	printf("Izquierda: %f; %f\n",izquierda[i].X,izquierda[i].Y);
			// }
			// agregamos las medianaX y medianaY recursivamente
			point_tree(root, izquierda, 0, medio);
			point_tree(root, derecha, 0, tamanio);
			free(izquierda);
			free(derecha);
		}
	}
}
/** Encuentra vecino mas cercano*/
double nearest_node(Point *root, double row, double column, int comparacion)
{
	// Root es el nodo actual
	// Column es eje X Row es eje Y
	// Comparacion 0 = X ; 1 = Y
	// printf("root: %f;%f\n", root->X,root->Y);
	// printf("punto: %f;%f\n",column, row);
	// printf("distancia: %f\n", distancia);
	// dist es distancia entre nodo actual y punto
	double dist = euclidean_distance(root,row,column);
	// printf("dist entre actual %f;%f y pixel %f;%f es: %f\n",root->X,root->Y,column,row,dist);
	// Si actual es mejor, actualizamos
	if (dist < distancia) {
		vecino->X = root->X;
		vecino->Y = root->Y;
		vecino->posicion = root->posicion;
		distancia = dist;
	}
	// Vemos si estamos en una hoja
	if (root->izquierda == 0 && root->derecha == 0) {
		// printf("Estamos en una hoja\n");
		// Estamos en una hoja
		// Comparamos la distancia del nodo actual al punto con la mejor distancia
		if (dist < distancia) {
			// Mejor vecino cecano es nodo actual
			vecino->X = root->X;
			vecino->Y = root->Y;
			vecino->posicion = root->posicion;
			distancia = dist;
		}
		// Devolvemos la distancia del nodo actual al punto
		// printf("return de hoja\n");
		return distancia;
	}
	// printf("No estamos en una hoja\n");
	// No estamos en hoja
	if (comparacion == 0) {
		// Comparamos eje X
		// printf("Comparando eje X\n");
		if (column < root->X) {
			// Es menor que root en X
			// printf("Es menos que root en X\n");
			// Vemos si hay nodo izquierdo
			if (root->izquierda == 1) {
				// Hay nodo en la izquierda
				// printf("Hay nodo en la izquierda\n");
				distancia = nearest_node(root->left, row, column,1);
				// printf("Saliendo de nearest_node de la izquierda\n");
				// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
				// printf("Comparando con nodo actual: %f;%f\n",root->X,root->Y);
				// Comparamos mejor vecino de la izquierda con nodo actual
				if (dist < distancia) {
					// Mejor vecino cecano es nodo actual
					vecino->X = root->X;
					vecino->Y = root->Y;
					vecino->posicion = root->posicion;
					distancia = dist;
				}
				// printf("Comparado\n");
				// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
			}
			// Vemos si hay nodo derecho y si hay que entrar
			// printf("Revisando nodo a la derecha\n");
			if (root->derecha == 1) {
				// printf("Hay nodo en la derecha\n");
				// Vemos si tenemos que buscar en sub arbol derecho
				// Comparamos la distancia X entre nodo actual y pixel vs distancia
				// printf("root: %f;%f\n", root->X,root->Y);
				// printf("punto: %f;%f\n",column, row);
				double dist_X = fabs(root->X-column);
				// printf("dist_X: %f\n", dist_X);
				if (dist_X < distancia) {
					// Entramos a sub arbol de la derecha
					// printf("Entrando a sub arbol de la derecha\n");
					distancia = nearest_node(root->right, row, column, 1);
					// printf("Saliendo de nearest_node de sub arbol de la derecha\n");
					// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
					// printf("Comparando con nodo actual: %f;%f\n", root->X,root->Y);
					// Comparamos mejor vecino de la derecha con nodo actual
					if (dist < distancia) {
						// Mejor vecino cecano es nodo actual
						vecino->X = root->X;
						vecino->Y = root->Y;
						vecino->posicion = root->posicion;
						distancia = dist;
					}
					// printf("Comparado\n");
					// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
				}
			}
			else {
				// printf("No hay nodo a la derecha\n");
			}
		}
		else {
			// Es mayor que root en X
			// printf("Es mas que root en X\n");
			// Vemos si hay nodo derecho
			if (root->derecha == 1) {
				// Hay nodo en la derecha
				// printf("Hay nodo en la derecha\n");
				distancia = nearest_node(root->right, row, column, 1);
				// printf("Saliendo de nearest_node de la derecha\n");
				// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
				// printf("Comparando con nodo actual: %f;%f\n",root->X,root->Y);
				// Comparamos mejor vecino de la derecha con nodo actual
				if (dist < distancia) {
					// Mejor vecino cecano es nodo actual
					vecino->X = root->X;
					vecino->Y = root->Y;
					vecino->posicion = root->posicion;
					distancia = dist;
				}
				// printf("Comparado\n");
				// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
			}
			// Vemos si hay nodo izquierdo y si hay que entrar
			// printf("Revisando nodo a la izquierda\n");
			if (root->izquierda == 1) {
				// printf("Hay nodo en la izquierda\n");
				// Vemos si tenemos que buscar en sub arbol izquierdo
				// Comparamos la distancia X entre nodo y pixel vs distancia
				// printf("root: %f;%f\n", root->X,root->Y);
				// printf("punto: %f;%f\n",column, row);
				double dist_X = fabs(root->X-column);
				// printf("dist_X: %f\n", dist_X);
				if (dist_X < distancia) {
					// printf("Entrando a sub arbol de la izquierda\n");
					// Entramos a sub arbol de la izquierda
					distancia = nearest_node(root->left, row, column, 1);
					// printf("Saliendo de nearest_node de sub arbol de la izquierda\n");
					// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
					// printf("Comparando con nodo actual: %f;%f\n", root->X,root->Y);
					// Comparamos mejor vecino de la derecha con nodo actual
					if (dist < distancia) {
						// Mejor vecino cecano es nodo actual
						vecino->X = root->X;
						vecino->Y = root->Y;
						vecino->posicion = root->posicion;
						distancia = dist;
					}
					// printf("Comparado\n");
					// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
				}
			}
		}
	}
	else {
		// Comparamos eje Y
		// printf("Comparando eje Y\n");
		if (row < root->Y) {
			// Es menor que root en Y
			// printf("Es menos que root en Y\n");
			// Vemos si hay nodo izquierdo
			if (root->izquierda == 1) {
				//Hay nodo en la izquierda
				// printf("Hay nodo en la izquierda\n");
				distancia = nearest_node(root->left, row, column, 0);
				// printf("Saliendo de nearest_node de la izquierda\n");
				// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
				// printf("Comparando con nodo actual: %f;%f\n",root->X,root->Y);
				// Comparamos mejor vecino de la izquierda con nodo actual
				if (dist < distancia) {
					// Mejor vecino cecano es nodo actual
					vecino->X = root->X;
					vecino->Y = root->Y;
					distancia = dist;
					vecino->posicion = root->posicion;
				}
				// printf("Comparado\n");
				// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
			}
			// Vemos si hay nodo derecho y si hay que entrar
			// printf("Revisando nodo a la derecha\n");
			if (root->derecha == 1) {
				// printf("Hay nodo en la derecha\n");
				// Vemos si tenemos que buscar en sub arbol derecho
				// Comparamos la distancia Y entre nodo actual y pixel vs distancia
				// printf("root: %f;%f\n", root->X,root->Y);
				// printf("punto: %f;%f\n",column, row);
				double dist_Y = fabs(root->Y-row);
				// printf("dist_X: %f\n", dist_Y);
				if (dist_Y < distancia) {
					// Entramos a sub arbol de la derecha
					// printf("Entrando a sub arbol de la derecha\n");
					distancia = nearest_node(root->right, row, column, 0);
					// printf("Saliendo de nearest_node de sub arbol de la derecha\n");
					// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
					// printf("Comparando con nodo actual: %f;%f\n",root->X,root->Y);
					// Comparamos mejor vecino de la derecha con nodo actual
					if (dist < distancia) {
						// Mejor vecino cecano es nodo actual
						vecino->X = root->X;
						vecino->Y = root->Y;
						vecino->posicion = root->posicion;
						distancia = dist;
					}
					// printf("Comparado\n");
					// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
				}
			}
		}
		else {
			// Es mayor que root en Y
			// printf("Es mas que root en Y\n");
			// Vemos si hay nodo derecho
			if (root->derecha == 1) {
				// printf("Hay nodo en la derecha\n");
				// Hay nodo en la derecha
				distancia = nearest_node(root->right, row, column, 0);
				// printf("Saliendo de nearest_node de la derecha\n");
				// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
				// printf("Comparando con nodo actual: %f;%f\n",root->X,root->Y);
				// Comparamos mejor vecino de la derecha con nodo actual
				if (dist < distancia) {
					// Mejor vecino cecano es nodo actual
					vecino->X = root->X;
					vecino->Y = root->Y;
					vecino->posicion = root->posicion;
					distancia = dist;
				}
				// printf("Comparado\n");
				// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
			}
			// Vemos si hay nodo izquierdo y si hay que entrar
			// printf("Revisando nodo a la Izquierda\n");
			if (root->izquierda == 1) {
				// printf("Hay nodo en la izquierda\n");
				// Vemos si tenemos que buscar en sub arbol izquierdo
				// Comparamos la distancia X entre nodo actual y pixel vs distancia
				// printf("root: %f;%f\n", root->X,root->Y);
				// printf("punto: %f;%f\n",column, row);
				double dist_Y = fabs(root->Y-row);
				// printf("dist_X: %f\n", dist_Y);
				if (dist_Y < distancia) {
					// Entramos a sub arbol de la izquierda
					// printf("Entrando a sub arbol de la izquierda\n");
					distancia = nearest_node(root->left, row, column, 0);
					// printf("Saliendo de nearest_node de sub arbol de la izquierda\n");
					// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
					// printf("Comparando con nodo actual: %f;%f\n",root->X,root->Y);
					// Comparamos mejor vecino de la derecha con nodo actual
					if (dist < distancia) {
						// Mejor vecino cecano es nodo actual
						vecino->X = root->X;
						vecino->Y = root->Y;
						vecino->posicion = root->posicion;
						distancia = dist;
					}
					// printf("Comparado\n");
					// printf("distancia: %f\n Vecino: %f;%f\n",distancia, vecino->X, vecino->Y);
				}
			}
		}
	}
	return distancia;
}
/** Inicializa variables para nearest_node*/
Point* nearest_root(Point *root, double row, double column)
{
	distancia = INFINITY;
	vecino = malloc(sizeof(Point));
	vecino->X = root->X;
	vecino->Y = root->Y;
	vecino->posicion = root->posicion;
	// printf("NEAREST_ROOT\n");
	nearest_node(root, row, column, 0);
	return vecino;
}
/** Retorna cuantas veces se llamo a euclidean_distance*/
int euclidean()
{
	return eucli;
}
/** Libera memoria de arbol*/
void destroy_tree(Point *root, int primera_vez)
{
	if (primera_vez == 1) {
		// Vemos si hay sub arboles
		if (root->izquierda == 1) {
			destroy_tree(root->left,0);
		}
		if (root->derecha == 1) {
			destroy_tree(root->right,0);
		}
	}
	else {
		// Vemos si hay sub arboles
		if (root->izquierda == 1) {
			destroy_tree(root->left,0);
		}
		if (root->derecha == 1) {
			destroy_tree(root->right,0);
		}
		printf("free de %f;%f\n",root->X,root->Y);
		free(root);
		printf("liberado %p\n",root);
	}
}
