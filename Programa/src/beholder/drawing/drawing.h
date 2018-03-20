#pragma once

#include <cairo.h>
#include <stdbool.h>
#include "color.h"
#include <pthread.h>

/** Contiene la información de lo que ha de ser dibujado en el canvas */
struct content
{
	/** Ancho de la ventana */
	int width;
	/** Alto de la ventana */
	int height;
	/** Color actual */
	Color current_color;
	/** Imagen vectorial, para dibuar los segmentos de recta */
	cairo_surface_t* vector_image;
	/** Imagen en píxeles, para la información de visibilidad de cada punto */
	cairo_surface_t* pixel_image;
	/* El ancho en bits de la imagen */
	int stride;
	/* La información de los pixeles de la imagen completa */
	uint8_t* data;
};
/** Contiene la información de lo que ha de ser dibujado en el canvas */
typedef struct content Content;

/** Inicializa las herramientas de dibujo*/
Content* drawing_init         (int height, int width);
/** Dibuja sobre el canvas dado */
bool     drawing_draw         (cairo_t* cr, Content* cont);
/** Actualiza el valor de un pixel dado */
void     drawing_paint_pixel  (Content* cont, int row, int col);
/** Dibuja un segmento de recta entre dos puntos */
void     drawing_draw_segment (Content* cont, double xi, double yi, double xf, double yf);
/** Genera una imagen en pdf para un estado en particular */
void     drawing_snapshot     (Content* cont, char* filename);
/** Libera los recursos asociados a las herramientas de dibujo */
void     drawing_free         (Content* cont);
