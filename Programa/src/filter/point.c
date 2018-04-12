#include "point.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/** Obtiene la distancia entre un punto y un píxel de la imagen */
double euclidean_distance(Point a, double row, double col)
{
	return sqrt(pow(a.X - col,2) + pow(a.Y - row, 2));
}

/** Agrega un punto a la izquierda o la derecha*/
void point_append(Point *root, Point point, int comparacion)
{
	printf("Comparacion: %i\n", comparacion);
	printf("Root: %f ; %f\n", root->X, root->Y);
	printf("Punto: %f ; %f\n", point.X, point.Y);
	// Si comparacion == 0 comparamos eje X, si no, comparamos eje Y

	// Comparamos eje Y
	if(comparacion == 1)
	{
		// Vemos si es menor que root en eje Y
		if (point.Y < root->Y) {
			printf("Point es menor en Y\n");
			// Si hay nodo a la izquierda
			if (root->left != NULL) {
				// Comparamos eje X con punto de la izquierda
				printf("El nodo a la izquierda es: %f ; %f\n",root->left->X,root->left->Y);
				point_append(root->left, point, 0);
			}
			// No hay nodo a la izquierda
			else
			{
				printf("No hay nodo a la izquierda\n");
				// Le asignamos el punto como nodo
				root->left = &point;
				root->left->left = NULL;
				root->left->right = NULL;
				root->left->X = point.X;
				root->left->Y = point.Y;
				if (root->left != NULL) {
					printf("Punto asignado\n");
				}
			}
		}
		// Es mayor que root en eje Y
		else
		{
			printf("Point es mayor en Y\n");
			// Si hay nodo derecha
			if (root->right !=NULL) {
				printf("Hay nodo en la derecha\n");
				// Comparamos con nodo derecha
				point_append(root->right, point, 0);
			}
			// No hay nodo a la derecha
			else
			{
				printf("No hay nodo en la derecha\n");
				// Le asignamos el punto como nodo
				root->right = &point;
				root->right->left = NULL;
				root->right->right = NULL;
				root->right->X = point.X;
				root->right->Y = point.Y;
				if (root->right != NULL) {
					printf("Punto asignado\n");
				}
			}
		}
	}

	// Comparamos eje X
	else
	{
		// Vemos si es menor que root en eje X
		if (point.X < root->X) {
			printf("Point es menor en X\n");
			// Si hay nodo a la izquierda
			if (root->left != NULL) {
				// Comparamos eje X con punto de la izquierda
				printf("El nodo a la izquierda es: %f ; %f\n",root->left->X,root->left->Y);
				point_append(root->left, point, 1);
			}
			// No hay nodo a la izquierda
			else
			{
				printf("No hay nodo a la izquierda\n");
				// Le asignamos el punto como nodo
				root->left = &point;
				root->left->left = NULL;
				root->left->right = NULL;
				root->left->X = point.X;
				root->left->Y = point.Y;
				if (root->left != NULL) {
					printf("Punto asignado\n");
				}
			}
		}
		// Es mayor que root en eje X
		else
		{
			printf("Point es mayor en X\n");
			// Si hay nodo derecha
			if (root->right !=NULL) {
				printf("Hay nodo en la derecha\n");
				// Comparamos con nodo derecha
				point_append(root->right, point, 1);
			}
			// No hay nodo a la derecha
			else
			{
				printf("No hay nodo en la derecha\n");
				// Le asignamos el punto como nodo
				root->right = &point;
				root->right->left = NULL;
				root->right->right = NULL;
				root->right->X = point.X;
				root->right->Y = point.Y;
				if (root->right != NULL) {
					printf("Punto asignado\n");
				}
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
	int i, st;

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
	printf("nuclei_count: %i\n", nuclei_count);
	int medio = (int) nuclei_count/2;
	int tamanio = nuclei_count-medio-1;
	// printf("medio: %i\n", medio);
	printf("Arreglo nuclei\n");
	point_print(nuclei, nuclei_count);
	// Si comparacion == 0, tomamos medianaX, si no, medianaY
	if (comparacion) {
		if (nuclei_count == 1) {
			point_append(root, nuclei[0], 0);
		}

		// Si quedan puntos
		else
		{
			Point medianaY = qselectY(nuclei, nuclei_count, medio);
			printf("MedianaY X: %f ; Y: %f\n",medianaY.X, medianaY.Y);
			point_append(root, medianaY, 1);
			Point *izquierda = malloc(medio*sizeof(Point));
			int izq = 0;
			int tamanio = medio;
			if (nuclei_count%2 == 0)
			{
				tamanio--;
			}
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

			for (int i = 0; i < medio; i++) {
				printf("Izquierda: %f; %f\n",izquierda[i].X,izquierda[i].Y);
			}
			// agregamos la proxima medianaX  recursivamente
			point_tree(root, izquierda, 0, medio);
			point_tree(root, derecha, 0, tamanio);
		}

	}

	// Comparamos eje X
	else
	{
		if (nuclei_count == 1) {
			point_append(root, nuclei[0], 0);
		}
		else
		{
			Point medianaX = qselectX(nuclei, nuclei_count, medio);
			point_append(root, medianaX, comparacion);
			// Si quedan puntos
			Point *izquierda = malloc(medio*sizeof(Point));
			int izq = 0;
			int tamanio = medio;
			if (nuclei_count%2 == 0)
			{
				tamanio--;
			}
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
			for (int i = 0; i < medio; i++) {
				printf("Izquierda: %f; %f\n",izquierda[i].X,izquierda[i].Y);
			}
			// agregamos las medianaX y medianaY recursivamente
			point_tree(root, izquierda, 0, medio);
			point_tree(root, derecha, 0, tamanio);
		}
	}
}
