#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cairo-pdf.h>
#include "drawing.h"

/** El mutex de dibujo */
static pthread_mutex_t drawing_mutex;

/** Multiplica un color por un escalar, para aclararlo o oscurecerlo */
// static Color color_scale(Color color, double k)
// {
//   return (Color){.R = color.R * k,.G = color.G * k, .B = color.B * k};
// }
//
// /** Setea el color RGB de cairo */
// static void cairo_dip(cairo_t* cr, Color color)
// {
//   cairo_set_source_rgb(cr,color.R,color.G, color.B);
// }
//
static void cairo_dip_alpha(cairo_t* cr, Color color, double alpha)
{
  cairo_set_source_rgba(cr,color.R,color.G, color.B, alpha);
}

// static void cairo_circle(cairo_t* cr, double xc, double yc, double rad)
// {
//   cairo_arc(cr, xc, yc, rad, 0, 2*M_PI);
// }

static void cairo_line(cairo_t* cr, double x1, double y1, double x2, double y2)
{
  cairo_move_to(cr, x1, y1);
  cairo_line_to(cr, x2, y2);
}

/** Dibuja un segmento de recta entre dos puntos */
void drawing_draw_segment (Content* cont, double xi, double yi, double xf, double yf)
{
  cairo_t* cr = cairo_create(cont -> vector_image);

  cairo_dip_alpha(cr, cont -> current_color, 1);
  cairo_line(cr, xi, yi, xf, yf);
  cairo_stroke(cr);

  // cairo_circle(cr,xi,yi,3);
  // cairo_fill(cr);
  //
  // cairo_circle(cr,xf,yf,3);
  // cairo_fill(cr);

  cairo_destroy(cr);
}


/** Actualiza el valor de un pixel dado */
void drawing_paint_pixel(Content* cont, int row, int col)
{
  /* Nos aseguramos de que se terminen los cambios en la imagen */
  cairo_surface_flush(cont -> pixel_image);

  uint8_t R = cont -> current_color.R * 255;
  uint8_t G = cont -> current_color.G * 255;
  uint8_t B = cont -> current_color.B * 255;

  /* Cambiamos el pixel al color correspondiente*/
  cont -> data[row*cont -> stride + col*4 + 0] = B;
  cont -> data[row*cont -> stride + col*4 + 1] = G;
  cont -> data[row*cont -> stride + col*4 + 2] = R;

  /* Marcamos que la imagen fue modificada para que Cairo la cargue */
  cairo_surface_mark_dirty(cont -> pixel_image);
}

bool drawing_draw(cairo_t* restrict cr, Content* restrict cont)
{
  pthread_mutex_lock(&drawing_mutex);

  cairo_set_source_surface(cr, cont -> pixel_image, 0, 0);

  cairo_paint(cr);

  cairo_set_source_surface(cr, cont -> vector_image, 0, 0);

  cairo_paint(cr);

  pthread_mutex_unlock(&drawing_mutex);

	return true;
}

/* Inicializa la imágen de píxeles */
static void init_pixel_image(int height, int width, Content* cont)
{
  /* El formato de imagen: R G B de 8 bits cada uno */
  cairo_format_t format = CAIRO_FORMAT_RGB24;
  /* El ancho en bytes de la imagen */
  int stride = cairo_format_stride_for_width (format, cont -> width);
  /* La información de los pixeles de la imagen completa */
  uint8_t* data = malloc(stride * cont -> height);
  /* La imagen en sí */
  cont -> pixel_image = cairo_image_surface_create_for_data(data, format, width, height, stride);
  cont -> stride = stride;
  cont -> data = data;
}

static void init_vector_image(int height, int width, Content* cont)
{
  /* El formato de imagen: R G B de 8 bits cada uno */
  cairo_format_t format = CAIRO_FORMAT_ARGB32;
  /** La imagen vectorial misma */
  cont -> vector_image = cairo_image_surface_create(format, width, height);
}

/** Genera los contenedores para las dos imagenes superpuestas */
Content* drawing_init(int height, int width)
{
  Content* cont = malloc(sizeof(Content));

  cont -> height = height;
  cont -> width = width;

  cont -> current_color = color_init(1, 1, 1);

  /* Inicializa la imagen de píxeles */
  init_pixel_image(cont -> height, cont -> width, cont);
  /* Inicializa la imagen vectorial */
  init_vector_image(cont -> height, cont -> width, cont);

	pthread_mutex_init(&drawing_mutex, NULL);

  return cont;
}

/** Geenera una imagen en pdf para un estado en particular */
void drawing_snapshot(Content* cont, char* filename)
{
	double width = cont -> width;
	double height = cont -> height;

	/* Imprimimos las imagenes del tablero */
	cairo_surface_t* surface;
	cairo_t *cr;

  surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);

	// surface = cairo_pdf_surface_create (filename, width, height);
	cr = cairo_create(surface);

	/* Reseteamos los parámetros para generar correctamente la imagen */
	Content aux = *cont;

	/* Dibuja el estado actual */
	drawing_draw(cr, &aux);

  cairo_surface_write_to_png(surface, filename);

	cairo_surface_destroy(surface);
	cairo_destroy(cr);
}

/** Libera los recursos asociados a las herramientas de dibujo */
void drawing_free(Content* cont)
{
  cairo_surface_destroy(cont -> vector_image);
  cairo_surface_destroy(cont -> pixel_image);
  free(cont);
  pthread_mutex_destroy(&drawing_mutex);
}
