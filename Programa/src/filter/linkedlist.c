#include "linkedlist.h"
#include <stdlib.h>

/** Agrega un nuevo elemento al principio de la lista */
List* list_prepend(List* list, int row, int col)
{
	List* node = malloc(sizeof(List));

	node -> row = row;
	node -> col = col;
	node -> next = list;

	return node;
}

/** Libera todos los recursos asociados a la lista */
void  list_destroy(List* list)
{
	while(list)
	{
		List* prev = list;
		list = list -> next;

		free(prev);
	}
}
