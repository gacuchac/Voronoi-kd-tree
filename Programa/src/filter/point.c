#include "point.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double distancia;

/** Obtiene la distancia entre un punto y un píxel de la imagen */
double euclidean_distance(Point *a, double row, double col)
{
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
				Point *punto = malloc(sizeof(Point));
				punto->derecha = 0;
				punto->izquierda = 0;
				punto->X = point.X;
				punto->Y = point.Y;
				root->left = punto;
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
				Point *punto = malloc(sizeof(Point));
				punto->derecha = 0;
				punto->izquierda = 0;
				punto->X = point.X;
				punto->Y = point.Y;
				root->right = punto;
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
				Point *punto = malloc(sizeof(Point));
				punto->derecha = 0;
				punto->izquierda = 0;
				punto->X = point.X;
				punto->Y = point.Y;
				root->left = punto;
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
				Point *punto = malloc(sizeof(Point));
				punto->derecha = 0;
				punto->izquierda = 0;
				punto->X = point.X;
				punto->Y = point.Y;
				root->right = punto;
				root->derecha = 1;
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
	// for (int i = 0; i < nuclei_count; i++) {
	//  printf("Nucleo X: %f ; Y:%f\n",nuclei[i].X,nuclei[i].Y);
	// }
}
/** Arma el arbol de puntos a partir de un root*/
void point_tree(Point *root, Point* nuclei, int comparacion, int nuclei_count)
{
	if (nuclei_count == 0) {
		return;
	}
	// printf("nuclei_count: %i\n", nuclei_count);
	int medio = (int) nuclei_count/2;
	int tamanio = nuclei_count-medio-1;
	// printf("medio: %i\n", medio);
	// printf("Arreglo nuclei\n");
	point_print(nuclei, nuclei_count);
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
		}
	}
}
/** Encuentra vecino mas cercano*/
Point* nearest_neighbour(Point *root, double row, double column, int comparacion, int primera_vez, Point* vecino, double distancia)
{
	if (primera_vez == 1) {
		vecino = malloc(sizeof(Point));
		distancia = INFINITY;
	}
	// Column es posicion X, Row es Y
	// printf("Distancia antes de actualizar: %f\n", distancia);
	double temp = euclidean_distance(root, row, column);
	if (temp < distancia) {
		distancia = temp;
		vecino = root;
		// printf("Distancia entre %f;%f y %f;%f es: %f\n",root->X, root->Y, column, row, distancia );
	}
	// printf("Distancia despues de actualizar: %f\n", distancia);
	// printf("Distancia entre %f;%f y %f;%f es: %f\n",root->X, root->Y, column, row, distancia );
	// Si comparacion == 0 comparamos eje X, si no, comparamos eje Y
	// Comparamos eje Y
	if(comparacion == 1)
	{
		// Vemos si es menor que root en eje Y
		if ( row < root->Y) {
			// printf("%f menor que %f\n",row, root->Y);
			// Si hay nodo a la izquierda
			if (root->izquierda == 1) {
				// Comparamos eje X con punto de la izquierda
				vecino = nearest_neighbour(root->left, row, column, 0, 0, vecino, distancia);

				// Comparamos la distancia menor con el nodo actual
				double temp = euclidean_distance(root, row, column);
				if (temp < distancia) {
					distancia = temp;
					vecino = root;
					// printf("Distancia entre %f;%f y %f;%f es: %f\n",root->X, root->Y, column, row, distancia );
				}

				// Calculamos la distancia del nodo actual al de la derecha si existe
				if (root->derecha == 1) {
					double dist = euclidean_distance(root, root->right->Y, root->right->X);

					// Si la distancia entre el nodo actual con el de la derecha es menor
					// que la del nodo actual con el pixel, buscamos nearest_neighbour
					// en el sub arbol de la derecha
					if (dist < distancia) {
						vecino = nearest_neighbour(root->right, row, column, 0,0,vecino,distancia);
					}
				}
			}
			// No hay nodo a la izquierda
			else
			{
				// printf("No hay nodo a la izquierda\n");
				// printf("root es X: %f Y: %f\n",root->X,root->Y);
				// Calculamos la distacia a la hoja
				double temp = euclidean_distance(root, row, column);
				// printf("temp es: %f\n distancia es: %f\n", temp,distancia);
				// if (temp < distancia) {
				// 	distancia = temp;
				// 	vecino = root;
				// 	printf("Distancia entre %f;%f y %f;%f es: %f\n",root->X, root->Y, column, row, distancia );
				// }

				// Calculamos la distancia del nodo actual al de la derecha si existe
				if (root->derecha == 1) {
					double dist = euclidean_distance(root, root->right->Y, root->right->X);

					// Si la distancia entre el nodo actual con el de la derecha es menor
					// que la del nodo actual con el pixel, buscamos nearest_neighbour
					// en el sub arbol de la derecha
					if (dist < distancia) {
						vecino = nearest_neighbour(root->right, row, column, 0,0,vecino,distancia);
					}
				}
			}
		}
		// Es mayor que root en eje Y
		else
		{
				// printf("%f mayor que %f\n",row, root->Y);
			// Si hay nodo derecha
			if (root->derecha == 1) {
				// Comparamos con nodo derecha
				vecino = nearest_neighbour(root->right, row, column, 0, 0,vecino,distancia);
				// Comparamos la distancia menor con el nodo actual
				double temp = euclidean_distance(root, row, column);
				if (temp < distancia) {
					distancia = temp;
					vecino = root;
					// printf("Distancia entre %f;%f y %f;%f es: %f\n",root->X, root->Y, column, row, distancia );
				}

				// Calculamos la distancia del nodo actual al de la izquierda si existe
				if (root->izquierda == 1) {
					double dist = euclidean_distance(root, root->left->Y, root->left->X);

					// Si la distancia entre el nodo actual con el de la izquierda es menor
					// que la del nodo actual con el pixel, buscamos nearest_neighbour
					// en el sub arbol de la izquierda
					if (dist < distancia) {
						vecino = nearest_neighbour(root->left, row, column, 0,0,vecino,distancia);
					}
				}
			}
			// No hay nodo a la derecha
			else
			{
				// Calculamos la distacia a la hoja
				double temp = euclidean_distance(root, row, column);
				if (temp < distancia) {
					distancia = temp;
					vecino = root;
					// printf("Distancia entre %f;%f y %f;%f es: %f\n",root->X, root->Y, column, row, distancia );
				}

				// Calculamos la distancia del nodo actual al de la izquierda si existe
				if (root->izquierda == 1) {
					double dist = euclidean_distance(root, root->left->Y, root->left->X);

					// Si la distancia entre el nodo actual con el de la derecha es menor
					// que la del nodo actual con el pixel, buscamos nearest_neighbour
					// en el sub arbol de la derecha
					if (dist < distancia) {
						vecino = nearest_neighbour(root->left, row, column, 0,0,vecino,distancia);
					}
				}
			}
		}
	}

	// Comparamos eje X
	else
	{
		// Vemos si es menor que root en eje X
		if ( row < root->X) {
			// printf("%f menor que %f\n",row, root->X);
			// Si hay nodo a la izquierda
			if (root->izquierda == 1) {
				// printf("Hay nodo a la izquierda\n");
				// printf("distancia es: %f\n", distancia);
				double temp = euclidean_distance(root, row, column);
				if (temp < distancia) {
					distancia = temp;
					vecino = root;
					// printf("Distancia entre %f;%f y %f;%f es: %f\n",root->X, root->Y, column, row, distancia );
				}
				// Comparamos eje X con punto de la izquierda
				// printf("Entrando a la izquierda\n");
				vecino = nearest_neighbour(root->left, row, column, 1,0,vecino,distancia);
				// Comparamos la distancia menor con el nodo actual
				temp = euclidean_distance(root, row, column);
				if (temp < distancia) {
					distancia = temp;
					vecino = root;
					// printf("Distancia entre %f;%f y %f;%f es: %f\n",root->X, root->Y, column, row, distancia );
				}

				// Calculamos la distancia del nodo actual al de la derecha si existe
				if (root->derecha == 1) {
					double dist = euclidean_distance(root, root->right->Y, root->right->X);

					// Si la distancia entre el nodo actual con el de la derecha es menor
					// que la del nodo actual con el pixel, buscamos nearest_neighbour
					// en el sub arbol de la derecha
					if (dist < distancia) {
						vecino = nearest_neighbour(root->right, row, column, 1,0,vecino,distancia);
					}
				}
			}
			// No hay nodo a la izquierda
			else
			{
				// Calculamos la distacia a la hoja
				double temp = euclidean_distance(root, row, column);
				if (temp < distancia) {
					distancia = temp;
					vecino = root;
					// printf("Distancia entre %f;%f y %f;%f es: %f\n",root->X, root->Y, column, row, distancia );
				}

				// Calculamos la distancia del nodo actual al de la derecha si existe
				if (root->derecha == 1) {
					double dist = euclidean_distance(root, root->right->Y, root->right->X);

					// Si la distancia entre el nodo actual con el de la derecha es menor
					// que la del nodo actual con el pixel, buscamos nearest_neighbour
					// en el sub arbol de la derecha
					if (dist < distancia) {
						vecino = nearest_neighbour(root->right, row, column, 1,0,vecino,distancia);
					}
				}
			}
		}
		// Es mayor que root en eje X
		else
		{
			// printf("%f mayor que %f\n",row, root->X);
			// Si hay nodo derecha
			if (root->derecha == 1) {
				// Comparamos con nodo derecha
				vecino = nearest_neighbour(root->right, row, column, 1,0,vecino,distancia);
				// Comparamos la distancia menor con el nodo actual
				double temp = euclidean_distance(root, row, column);
				if (temp < distancia) {
					distancia = temp;
					vecino = root;
					// printf("Distancia entre %f;%f y %f;%f es: %f\n",root->X, root->Y, column, row, distancia );
				}

				// Calculamos la distancia del nodo actual al de la izquierda si existe
				if (root->izquierda == 1) {
					double dist = euclidean_distance(root, root->left->Y, root->left->X);

					// Si la distancia entre el nodo actual con el de la izquierda es menor
					// que la del nodo actual con el pixel, buscamos nearest_neighbour
					// en el sub arbol de la izquierda
					if (dist < distancia) {
						vecino = nearest_neighbour(root->left, row, column, 1,0,vecino,distancia);
					}
				}
			}
			// No hay nodo a la derecha
			else
			{
				// Calculamos la distacia a la hoja
				double temp = euclidean_distance(root, row, column);
				if (temp < distancia) {
					distancia = temp;
					vecino = root;
					// printf("Distancia entre %f;%f y %f;%f es: %f\n",root->X, root->Y, column, row, distancia );
				}

				// Calculamos la distancia del nodo actual al de la izquierda si existe
				if (root->izquierda == 1) {
					double dist = euclidean_distance(root, root->left->Y, root->left->X);

					// Si la distancia entre el nodo actual con el de la derecha es menor
					// que la del nodo actual con el pixel, buscamos nearest_neighbour
					// en el sub arbol de la derecha
					if (dist < distancia) {
						vecino = nearest_neighbour(root->left, row, column, 1,0,vecino,distancia);
					}
				}
			}
		}
	}
	// printf("Vecino es X: %f; Y: %f\n",vecino->X,vecino->Y);
	return vecino;
}
