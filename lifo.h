//Problème du voyageur de commerce
//Algorithme de Little
//
//Fait par LAPLANCHE Alexis

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

typedef struct entry{
	NODE * value;
	struct entry * next;
} ENTRY;

typedef struct lifo{
	ENTRY * head;
	size_t size;
} LIFO;


LIFO* init_lifo();
void push(LIFO* lifo,NODE* value);
NODE* pop(LIFO *lifo);
void print_lifo(LIFO *lifo);
void desalloc_lifo(LIFO * lifo);
