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
