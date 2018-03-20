#include "watcher.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define WATCHER "./beholder"

static FILE* watcher = NULL;

/** Abre una ventana para mostrar una matriz de las dimensiones dadas */
void watcher_open(int height, int width)
{
	setlocale(LC_ALL, "C");

	char command[256];

	sprintf(command, "%s %d %d", WATCHER, height, width);

	if(watcher) watcher_close();

	watcher = popen(command, "w");
}

/** Selecciona un color para las siguientes operaciones de dibujo */
void watcher_set_color (double R, double G, double B)
{
	if(watcher)
	{
		if(fprintf(watcher, "C %lf %lf %lf\n", R, G, B) < 0)
		{
			watcher_close();
		}
		else
		{
			fflush(watcher);
		}
	}
}

/** Dibuja un segmento de recta de un punto a otro del color seleccionado */
void watcher_draw_segment (double xi, double yi, double xf, double yf)
{
	if(watcher)
	{
		if(fprintf(watcher, "L %lf %lf %lf %lf\n", xi, yi, xf, yf) < 0)
		{
			watcher_close();
		}
		else
		{
			fflush(watcher);
		}
	}
}

/** Pinta el pixel del color seleccionado */
void watcher_paint_pixel (int row, int col)
{
	if(watcher)
	{
		if(fprintf(watcher, "P %d %d\n", row, col) < 0)
		{
			watcher_close();
		}
		else
		{
			fflush(watcher);
		}
	}
}

/** Genera una imagen PNG con el contenido actual de la ventana */
void watcher_snapshot (char* filename)
{
	if(watcher)
	{
		if(fprintf(watcher, "S %s\n", filename) < 0)
		{
			watcher_close();
		}
		else
		{
			fflush(watcher);
		}
	}
}

/** Cierra y libera los recursos de la ventana */
void watcher_close()
{
	if(watcher)
  {
    if(fprintf(watcher, "%s\n", "X") >= 0)
    {
      fflush(watcher);
      pclose(watcher);
    }
    watcher = NULL;
  }
}
