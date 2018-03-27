#pragma once

/** Una lista ligada simple */
struct list;

/** Una lista ligada simple */
typedef struct list List;

/** Una lista ligada simple */
struct list
{
	int row;
	int col;
 	List* next;
};

/** Agrega un nuevo elemento al principio de la lista */
List* list_prepend(List* list, int row, int col);
/** Libera todos los recursos asociados a la lista */
void  list_destroy(List* list);
