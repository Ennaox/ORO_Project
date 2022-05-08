#include "tree.h"

NODE * init_tree(int value)
{
	NODE * node = malloc(sizeof(NODE));
	node->value = value;
	node->root = node;
	node->father = NULL;
	node->left = NULL;
	node->right = NULL;

	return node;
}


void add_left(NODE * tree,int value)
{
	if(tree->left!= NULL)
	{
		printf("Can't insert, there is already a left child\n");
		return;
	}
	tree->left = malloc(sizeof(NODE));
	tree->left->value = value;
	tree->left->father = tree;
	tree->left->root = tree->root;
	tree->left->left = NULL;
	tree->left->right = NULL;
	
}

void add_right(NODE * tree,int value)
{
	if(tree->right!= NULL)
	{
		printf("Can't insert, there is already a left child\n");
		return;
	}
	tree->right = malloc(sizeof(NODE));
	tree->right->value = value;
	tree->right->father = tree;
	tree->right->root = tree->root;
	tree->right->left = NULL;
	tree->right->right = NULL;
}

void tree_go_brrrr(NODE * node)
{
	if(node->left!=NULL)
	{
		tree_go_brrrr(node->left);
	}
	if(node->right!=NULL)
	{
		tree_go_brrrr(node->right);
	}
	free(node);
}

void desalloc_tree(NODE * node)
{
	tree_go_brrrr(node);
}

void print_tree(NODE * node)
{
	if(node==NULL)
	{
		return;
	}
	printf("%d ",node->value);
	print_tree(node->left);
	print_tree(node->right);
	if(node->left==NULL && node->right==NULL)
	{
		printf("\n");
	}
}