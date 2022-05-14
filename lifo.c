#include "lifo.h"

LIFO* init_lifo()
{
	LIFO * lifo = malloc(sizeof(LIFO));
	lifo->head = NULL;
	lifo->size = 0;
	return lifo;
}

void push(LIFO* lifo,NODE * value)
{
	ENTRY * new_entry = malloc(sizeof(ENTRY));
	new_entry->value = value;

	new_entry->next = lifo->head;
	lifo->head = new_entry;
	lifo->size ++;
}

NODE * pop(LIFO *lifo)
{
	if(lifo->head==NULL)
	{
		printf("Fatal Error: the lifo is empty\n");
		exit(1);
	}
	NODE * value = lifo->head->value;
	ENTRY * tmp = lifo->head;
	lifo->head = lifo->head->next;
	free(tmp);
	lifo->size --;
	return value;
}

void print_lifo(LIFO *lifo)
{
	if(lifo == NULL || !lifo->size)
	{
		printf("EMPTY\n");
		return;
	}
	ENTRY * tmp = lifo->head;
	print_tree(tmp->value);
	while(tmp->next!=NULL)
	{
		tmp=tmp->next;
		print_tree(tmp->value);
	}
	printf("\n");
}

void desalloc_lifo(LIFO * lifo)
{
	if(lifo == NULL)
		return;
	while(lifo->size != 0)
	{
		pop(lifo);
	}
	free(lifo);
}