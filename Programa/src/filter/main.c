#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../watcher/watcher.h"
#include "../imagelib/imagelib.h"
#include "../random/pcg_basic.h"
#include "point.h"
#include "linkedlist.h"
#include <math.h>

double bounded_random_double(double bound)
{
	double random = pcg32_random();
	random /= UINT32_MAX;
	return random * bound;
}

int main(int argc, char** argv)
{
	if(argc != 4)
	{
		printf("Modo de uso: %s <img.txt> <núcleos> <seed>\nDonde\n", argv[0]);
		printf("\tscene.txt es el archivo donde se describe la escena\n");
		printf("\tnúcleos es la cantidad de núcleos\n");
		printf("\tseed es la semilla aleatoria\n");

		return 1;
	}

	/* La cantidad de núcleos */
	int nuclei = atoi(argv[2]);
	if (nuclei <= 0)
	{
		printf("Debe haber al menos 1 núcleo\n");
		return 1;
	}

	/* Seteamos la semilla aleatoria*/
	int seed = atoi(argv[3]);
	pcg32_srandom(0x853c49e6748fea9bULL ^ seed, 0xda3e39cb94b95bdbULL);

	/* Lee el archivo de la imagen */
	Image* img = img_png_read_from_file(argv[1]);
	/* Abre la ventana de las dimensiones especificadas */
	watcher_open(img -> height, img -> width);

	// for(int row = 0; row < img -> height; row++)
	// {
	// 	for(int col = 0; col < img -> width; col++)
	// 	{
	// 		Color c = img -> pixels[row][col];
  //
	// 		watcher_set_color(c.R, c.G,  c.B);
	// 		watcher_paint_pixel(row, col);
	// 	}
	// }

	Point* points = malloc(nuclei * sizeof(Point));

	for(int i = 0; i < nuclei; i++)
	{
		points[i].X = bounded_random_double(img -> width);
		points[i].Y = bounded_random_double(img -> height);
	}

	List** zones = calloc(nuclei, sizeof(List*));

	for(int row = 0; row < img -> height; row++)
	{
		for(int col = 0; col < img -> width; col++)
		{
			double closest_distance = INFINITY;
			int closest_point;

			for(int i = 0; i < nuclei; i++)
			{
				double distance = euclidean_distance(points[i], row, col);
				if (distance < closest_distance)
				{
					closest_distance = distance;
					closest_point = i;
				}
			}

			zones[closest_point] = list_prepend(zones[closest_point], row, col);
		}

		if(row % 10 == 0) printf("%lf%%\n", 100.0 * (double)row / (double)img -> height);
	}

	printf("Encontrado el núcleo más cercano para cada píxel\n");

	for(int i = 0; i < nuclei; i++)
	{
		double R = 0;
		double G = 0;
		double B = 0;
		int count = 0;

		for(List* curr = zones[i]; curr; curr = curr -> next)
		{
			Color c = img -> pixels[curr -> row][curr -> col];

			R += c.R;
			G += c.G;
			B += c.B;

			count++;
		}

		printf("El núcleo %d tiene %d elementos\n", i, count);

		R /= count;
		G /= count;
		B /= count;

		watcher_set_color(R, G, B);

		for(List* curr = zones[i]; curr; curr = curr -> next)
		{
			watcher_paint_pixel(curr -> row, curr -> col);
		}
	}

	printf("Pintadas todas las zonas\n");


	for(int i = 0; i < nuclei; i++)
	{
		list_destroy(zones[i]);
	}
	free(zones);
	free(points);
	img_png_destroy(img);

	/* Imprime la ventana en una imagen para se la muestres a tu mamá */
	watcher_snapshot("mira_mama_que_lindo_mi_programa.png");

	// OJO: Lo que sea que haya en la ventana cuando llames esta función será
	// lo que se considere para tu corrección
	watcher_close();

	// OJO: Si no retornas 0 en el main, se considera que tu programa falló
	return 0;
}
