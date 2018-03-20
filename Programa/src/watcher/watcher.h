#pragma once

/****************************************************************************/
/*                                Watcher                                   */
/*                                                                          */
/* Módulo a cargo de la visualización del problema.                         */
/****************************************************************************/

/** Abre una ventana para mostrar una imagen de las dimensiones dadas */
void watcher_open         (int height, int width);
/** Selecciona un color para las siguientes operaciones de dibujo */
void watcher_set_color    (double R, double G, double B);
/** Dibuja un segmento de recta de un punto a otro del color seleccionado */
// void watcher_draw_segment (double xi, double yi, double xf, double yf);
/** Pinta el pixel del color seleccionado */
void watcher_paint_pixel  (int row, int col);
/** Genera una imagen PNG con el contenido actual de la ventana */
void watcher_snapshot     (char* filename);
/** Cierra y libera los recursos de la ventana */
void watcher_close        ();
