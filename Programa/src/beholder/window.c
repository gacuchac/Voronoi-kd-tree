#include <stdlib.h>
#include <gtk/gtk.h>
#include <math.h>
#include "window.h"
#include "animating/animation.h"

/** Dibuja la imagen en la ventana */
static gboolean draw(GtkWidget* widget, cairo_t* cr, gpointer data)
{
	return drawing_draw(cr, data);
}

/** Inicializa el canvas de acuerdo al tablero que se va a dibujar */
static void gtk_canvas_init(GtkWidget* canvas, Content* cont)
{
	gtk_widget_set_size_request(canvas, cont -> width, cont -> height);
}

void window_create(Content* cont)
{
	/* Se cierra el canal para errores para que GTK no moleste */
  fclose(stderr);

  /* Inicializar GTK */
  gtk_init(0, NULL);

	/* Inicializar ventana */
  GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(window, "destroy", G_CALLBACK(animation_abort), NULL);

  /* Inicializar canvas */
  GtkWidget* canvas = gtk_drawing_area_new();
	gtk_canvas_init(canvas, cont);

	/* Ligar eventos */
  g_signal_connect(canvas, "draw", G_CALLBACK(draw), cont);
  g_signal_connect(canvas, "realize", G_CALLBACK(animation_init), cont);

	/* Meter canvas a la ventana */
  gtk_container_add(GTK_CONTAINER(window), canvas);

  /* Mostrar todo */
  gtk_widget_show(canvas);
  gtk_widget_show(window);

	/* Comenzamos la ejecución de GTK */
  gtk_main();
}
