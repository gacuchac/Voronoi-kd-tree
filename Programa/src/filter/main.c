#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../watcher/watcher.h"
#include "../imagelib/imagelib.h"
#include "../random/pcg_basic.h"
#include "point.h"
#include "linkedlist.h"
#include <math.h>


int main(int argc, char** argv)
{

	/**************************************************************************/
	/*                              Preparación                               */
	/**************************************************************************/

	if(argc != 4)
	{
		printf("Modo de uso: %s <img.txt> <núcleos> <seed>\nDonde\n", argv[0]);
		printf("\tscene.txt es el archivo donde se describe la escena\n");
		printf("\tnúcleos es la cantidad de núcleos\n");
		printf("\tseed es la semilla aleatoria\n");

		return 1;
	}

	/* Leer la cantidad de núcleos */
	int nuclei_count = atoi(argv[2]);
	if (nuclei_count <= 0)
	{
		printf("Debe haber al menos 1 núcleo\n");
		return 1;
	}

	/* Seteamos la semilla aleatoria*/
	int seed = atoi(argv[3]);
	random_seed(seed);

	/* Lee el archivo de la imagen */
	Image* img = img_png_read_from_file(argv[1]);
	/* Abre la ventana de las dimensiones especificadas */
	watcher_open(img -> height, img -> width);

	/* Pinta la imagen en la ventana. Para cada pixel: */
	for(int row = 0; row < img -> height; row++)
	{
		for(int col = 0; col < img -> width; col++)
		{
			/* Toma el color del pixel */
			Color c = img -> pixels[row][col];
			/* Le dice a la ventana que se ponga ese color */
			watcher_set_color(c.R, c.G,  c.B);
			/* Y que pinte específicamente ese pixel */
			watcher_paint_pixel(row, col);
		}
	}

	/**************************************************************************/
	/*                                  PASO 1                                */
	/*                                                                        */
	/* Crear el conjunto de núcleos de forma aleatoria                        */
	/**************************************************************************/

	Point* nuclei = malloc(nuclei_count * sizeof(Point));

	for(int i = 0; i < nuclei_count; i++)
	{
		nuclei[i].X = random_bounded_double(img -> width);
		nuclei[i].Y = random_bounded_double(img -> height);
		nuclei[i].left = NULL;
		nuclei[i].right = NULL;
		printf("X: %f ; Y: %f\n",nuclei[i].X, nuclei[i].Y);
	}

	int medio = (int)nuclei_count/2;
	Point medianaX = qselectX(nuclei, nuclei_count,medio);

	// Creamos el arbol
	// Agregamos los nodos menores que medianaX
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
		if (nuclei[i].X < medianaX.X) {
			izquierda[izq] = nuclei[i];
			izq++;
		}
		else if (nuclei[i].X > medianaX.X) {
			derecha[der] = nuclei[i];
			der++;
		}
	}
	point_tree(&medianaX, izquierda, 0, medio);

	/**************************************************************************/
	/*                                  PASO 2                                */
	/*                                                                        */
	/* Buscar el núcleo más cercano a cada píxel y asociarlo a él             */
	/**************************************************************************/

	/* OJO: Sólo importa medir la mejora en tiempo de esta sección */

	/* Los elementos de la celda de voronoi asociada a cada núcleo */
	/* Es un arreglo de listas */
	List** cells = calloc(nuclei_count, sizeof(List*));

	/* Para cada píxel de la imagen */
	for(int row = 0; row < img -> height; row++)
	{
		for(int col = 0; col < img -> width; col++)
		{
			/* Identifica cual es el núcleo más cercano al pixel */
			double closest_distance = INFINITY;
			int closest_point;

			/* Se revisa la distancia del pixel con cada núcleo */
			for(int i = 0; i < nuclei_count; i++)
			{
				/* Guardando siempre el más cercano */
				double distance = euclidean_distance(nuclei[i], row, col);
				if (distance < closest_distance)
				{
					closest_distance = distance;
					closest_point = i;
				}
			}

			/* Se asocia el píxel a su núcleo más cercano */
			cells[closest_point] = list_prepend(cells[closest_point], row, col);
		}
	}

	/**************************************************************************/
	/*                                  PASO 3                                */
	/*                                                                        */
	/* Pintar el diagrama de voronoi de acuerdo a los pixeles de una celda    */
	/**************************************************************************/

	/* Para cada núcleo */
	for(int i = 0; i < nuclei_count; i++)
	{
		/* Nota: los colores se dividen en componentes R,G y B */
		double R = 0;
		double G = 0;
		double B = 0;
		int count = 0;

		/* c es el promedio de los colores de cada los pı́xel dentro de su celda */
		for(List* curr = cells[i]; curr; curr = curr -> next)
		{
			Color c = img -> pixels[curr -> row][curr -> col];

			R += c.R;
			G += c.G;
			B += c.B;

			count++;
		}

		R /= count;
		G /= count;
		B /= count;

		/* Pintar de color c todos los píxeles asociados al núcleo */
		watcher_set_color(R, G, B);

		/* Por cada píxel dentro de la celda correspondiente al i-ésimo núcleo */
		for(List* curr = cells[i]; curr; curr = curr -> next)
		{
			watcher_paint_pixel(curr -> row, curr -> col);
		}
	}

	/* Imprime la ventana en una imagen para se la muestres a tu mamá */
	watcher_snapshot("mira_mama_que_lindo_mi_programa.png");

	/* Detiene el programa por 5 segundos para que contemples el resultado */
	sleep(5);

	/**************************************************************************/
	/*                          Liberación de Memoria                         */
	/**************************************************************************/

	for(int i = 0; i < nuclei_count; i++)
	{
		list_destroy(cells[i]);
	}
	free(cells);
	free(nuclei);
	img_png_destroy(img);

	/* OJO: Lo que sea que haya en la ventana cuando llames esta función será */
	/* lo que se considere para tu corrección */
	watcher_close();

	/* OJO: Si no retornas 0 en el main, se considera que tu programa falló */
	return 0;
}
