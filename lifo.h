#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct entry{
	int value;
	struct entry * next;
} ENTRY;

typedef struct lifo{
	ENTRY * head;
	size_t size;
} LIFO;


LIFO* init_lifo();
void push(LIFO* lifo,int value);
int pop(LIFO *lifo);
void print_lifo(LIFO *lifo);
void desalloc_lifo(LIFO * lifo);
