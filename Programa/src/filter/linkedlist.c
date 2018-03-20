#include "linkedlist.h"
#include <stdlib.h>

List* list_prepend(List* list, int row, int col)
{
	List* node = malloc(sizeof(List));

	node -> row = row;
	node -> col = col;
	node -> next = list;
	return node;
}

void  list_destroy(List* list)
{
	while(list)
	{
		List* prev = list;
		list = list -> next;
		free(prev);
	}
}
