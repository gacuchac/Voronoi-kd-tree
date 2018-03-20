#pragma once

struct list;

typedef struct list List;

struct list
{
	int row;
	int col;
 	List* next;
};

List* list_prepend(List* list, int row, int col);

void  list_destroy(List* list);
