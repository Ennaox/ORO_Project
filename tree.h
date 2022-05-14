//Problème du voyageur de commerce
//Algorithme de Little
//
//Fait par LAPLANCHE Alexis

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct matrix
{
	int dim;
	long * mat;	
} MAT;

typedef struct trajet{
	int src;
	int dest;
} trajet;

typedef struct liste
{
	char * path;
	struct liste * next;
	struct liste * prev;
} LIST;

typedef struct node
{
	long value;
	long max_reg;
	MAT mat;
	trajet traj;
	LIST * all_path;
	struct node * root;
	struct node * father;
	struct node * left;
	struct node * right;
} NODE;

LIST * init_list(char * val);
void add_entry(LIST * liste, char * val);
LIST * copy_list(LIST * liste);
void free_entry(LIST * liste);
void find_path(trajet T, NODE * tree);
MAT matdup(MAT src);
void desalloc_matrix(MAT matrix);
NODE * init_tree(long value,MAT matrix);
void add_left(NODE * tree);
void add_right(NODE * tree);
void desalloc_tree(NODE * node);
void print_tree(NODE * node);