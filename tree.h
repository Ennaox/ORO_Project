#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
	int value;
	struct node * root;
	struct node * father;
	struct node * left;
	struct node * right;
} NODE;

NODE * init_tree(int value);
void add_left(NODE * tree,int value);
void add_right(NODE * tree,int value);
void desalloc_tree(NODE * node);
void print_tree(NODE * node);