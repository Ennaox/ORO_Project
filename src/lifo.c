#include "lifo.h"

LIFO* init_fifo()
{
	LIFO * lifo = malloc(sizeof(LIFO));
	lifo->head = NULL;
	lifo->size = 0;
	return lifo;
}

void push(LIFO* lifo,int value)
{
	ENTRY * new_entry = malloc(sizeof(ENTRY));
	new_entry->value = value;

	new_entry->next = lifo->head;
	lifo->head = new_entry;
	lifo->size ++;
}

int pop(LIFO *lifo)
{
	if(lifo->head==NULL)
	{
		printf("Fatal Error: the lifo is empty\n");
		exit(1);
	}
	int value = lifo->head->value;
	ENTRY * tmp = lifo->head;
	lifo->head = lifo->head->next;
	free(tmp);
	lifo->size --;
	return value;
}

void print_fifo(LIFO *lifo)
{
	if(lifo == NULL || !lifo->size)
	{
		printf("Error: can't print, the lifo is empty\n");
		return;
	}
	ENTRY * tmp = lifo->head;
	printf("%d ", tmp->value);
	while(tmp->next!=NULL)
	{
		tmp=tmp->next;
		printf("%d ", tmp->value);
	}
	printf("\n");
}

void desalloc_fifo(LIFO * lifo)
{
	if(lifo == NULL)
		return;
	while(lifo->size != 0)
	{
		pop(lifo);
	}
	free(lifo);
}