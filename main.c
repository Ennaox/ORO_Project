#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#include "tree.h"
#include "lifo.h"

void print_mat_cost(MAT pb)
{
	for(int i = 0; i<pb.dim; i++)
	{
		for(int j = 0; j<pb.dim; j++)
		{
			printf("%ld\t",pb.mat[i * pb.dim + j]);
		}
		printf("\n");
	}
}

long reduction(MAT matrix)
{
	long val = 0;
	//Calcul du minimum de chaque ligne et soustraction de ce minimum
	for(int i = 0; i<matrix.dim;i++)
	{
		long min = LONG_MAX;
		for(int j = 0; j<matrix.dim;j++)
		{
			if(min>matrix.mat[i*matrix.dim + j] && matrix.mat[i*matrix.dim + j]>=0)
			{
				min = matrix.mat[i*matrix.dim + j];
			}
		}
		for(int j = 0; j<matrix.dim;j++)
		{
			if(matrix.mat[i*matrix.dim + j]>=0)
			{
				matrix.mat[i*matrix.dim + j] -= min;
			}
		}
		if(min == 0 || min == LONG_MAX)
		{
			min = 0;
		}
		val += min;
	}

	//Calcul du minimum de chaque colone et soustraction de ce minimum
	for(int j = 0; j<matrix.dim;j++)
	{
		long min = LONG_MAX;
		for(int i = 0; i<matrix.dim;i++)
		{
			if(min>matrix.mat[i*matrix.dim + j] && matrix.mat[i*matrix.dim + j]>=0)
			{
				min = matrix.mat[i*matrix.dim + j];
				
			}
		}
		for(int i = 0; i<matrix.dim;i++)
		{
			if(matrix.mat[i*matrix.dim + j]>=0)
			{
				matrix.mat[i*matrix.dim + j] -= min;
			}
		}
		if(min == 0 || min == LONG_MAX)
		{
			min = 0;
		}
		val += min;
	}
	return val;
}

long calc_regret(MAT mat,int row, int col)
{

	long min_col = LONG_MAX;
	long min_row = LONG_MAX;
	
	for(int i = 0; i<mat.dim; i++ )
	{
		if(min_col>mat.mat[i*mat.dim + col] && mat.mat[i*mat.dim + col]>=0 && i!=row)
		{
			min_col = mat.mat[i*mat.dim + col]; 
		}
		if(min_row>mat.mat[row*mat.dim + i] && mat.mat[row*mat.dim + i]>=0 && i!=col)
		{
			min_row = mat.mat[row*mat.dim + i]; 
		}
	}
	if(min_row < 0 || min_row == LONG_MAX)
		min_row = 0;

	if(min_col < 0 || min_col == LONG_MAX)
		min_col = 0;
	return min_row + min_col;
}

void regret(NODE * tree)
{
	tree->max_reg = -1;
	long tmp;
	for(int i = 0; i<tree->mat.dim; i++)
	{
		for(int j = 0; j<tree->mat.dim; j++)
		{
			if(tree->mat.mat[i*tree->mat.dim + j] == 0)
			{
				tmp = calc_regret(tree->mat,i,j);
				if(tmp>tree->max_reg)
				{
					tree->max_reg = tmp;
					tree->traj.src = i;
					tree->traj.dest = j;
				}
			}
		}
	}
}

MAT read_config(char* F_name)
{
	MAT pb;
	
	FILE * F_config = fopen(F_name,"r");
	
	if(F_config == NULL)
	{
		printf("Error 404: %s not found\n",F_name);
		exit(404);
	}
	int dim[2];
	int err;
	
	err = fscanf(F_config,"Dimension: %dx%d \nMatrice: \n",&dim[0],&dim[1]);
	if(!err)
	{
		printf("Fatal Error: %s bad format\nRead the README.md for more info\n",F_name);
		fclose(F_config);
		exit(2);
	}
	if(dim[0] != dim[1])
	{
		printf("Fatal Error: the given matrice is not square\n");
		fclose(F_config);
		exit(3);
	}
	pb.dim = dim[0];

	pb.mat = malloc(pb.dim * pb.dim * sizeof(long));
	for(int i = 0; i<pb.dim; i++)
	{
		for(int j = 0; j<pb.dim; j++)
		{
			err = fscanf(F_config,"%ld ",&pb.mat[i * pb.dim + j]);
			if(!err)
			{
				printf("Fatal Error: the matrix didn't fit the given dimensions\n");
				fclose(F_config);
				exit(4);
			} 
		}
	}

	fclose(F_config);
	printf("----------------------------------\n");
	printf("CONFIG:\n\n");
	printf("Dimension: %dx%d\n",pb.dim,pb.dim);
	print_mat_cost(pb);		
	printf("----------------------------------\n\n");
	
	return pb;
}

int check_end(MAT mat)
{
	for(int i = 0; i<mat.dim * mat.dim;i++)
	{
		if(mat.mat[i]!=-1)
			return 1;
	}
	return 0;
}

void little_print_status(NODE * tree, LIFO * pile)
{
		printf("Cost matrix:\n");
		print_mat_cost(tree->mat);
		printf("\nTree:\n");
		print_tree(tree->root);
		printf("\nStack:\n");
		print_lifo(pile);
		printf("----------------------------------------------\n");
}

NODE * little(NODE * tree, LIFO * pile,NODE * ref)
{
	long val;
	if(ref==NULL)
	{
		while(check_end(tree->mat))
		{
			val = reduction(tree->mat);
			tree->value += val;
			regret(tree);
			add_left(tree);
			add_right(tree);
			push(pile,tree->right);
			
			little_print_status(tree,pile);
			val = tree->value;
			tree=tree->left;
		}
		return tree;	
	}
	if(tree->value>=ref->value)
	{
		little_print_status(tree,pile);
		return ref;
	}
	else
	{
		while(check_end(tree->mat))
		{
			val = reduction(tree->mat);
			tree->value += val;
			regret(tree);
			add_left(tree);
			add_right(tree);
			push(pile,tree->right);
			
			little_print_status(tree,pile);
			val = tree->value;
			tree=tree->left;
			if(ref->value<=tree->value)
				return ref;
		}
		return tree;	
	}
	return NULL;
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Fatal Error: bad number of argument\nUsage: %s <config_file.txt>\n",argv[0]);
		return 1;
	}
	
	MAT mat = read_config(argv[1]);

	//Début de l'algorithme
	LIFO * pile = init_lifo();
	long val = reduction(mat);
	NODE * tree = init_tree(val,mat);
	regret(tree);
	add_left(tree);
	add_right(tree);
	push(pile,tree->right);
	tree=tree->left;
	
	little_print_status(tree,pile);
	
	NODE * ref = little(tree,pile,NULL);
	printf("Reference value: %ld\n",ref);

	while(pile->size!=0)
	{
		ref = little(pop(pile),pile,ref);	
	}
	printf("Best solution score: %ld\n",ref->value);
	printf("With path %s\n",ref->all_path->path);
}