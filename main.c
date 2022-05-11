#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "lifo.h"

typedef struct problem
{
	int dim;
	int * MAT_cost;	
} problem;

problem read_config(char* F_name)
{
	problem pb;
	
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

	pb.MAT_cost = malloc(pb.dim * pb.dim * sizeof(int));
	for(int i = 0; i<pb.dim; i++)
	{
		for(int j = 0; j<pb.dim; j++)
		{
			err = fscanf(F_config,"%d ",&pb.MAT_cost[i * pb.dim + j]);
			if(!err)
			{
				printf("Fatal Error: the matrix didn't fit the given dimensions\n");
				fclose(F_config);
				exit(4);
			} 
		}
	}

	fclose(F_config);
	return pb;
}

void print_mat_cost(problem pb)
{
	printf("----------------------------------\n");
	printf("CONFIG:\n\n");
	printf("Dimension: %dx%d\n",pb.dim,pb.dim);
	for(int i = 0; i<pb.dim; i++)
	{
		for(int j = 0; j<pb.dim; j++)
		{
			printf("%d ",pb.MAT_cost[i * pb.dim + j]);
		}
		printf("\n");
	}
	printf("----------------------------------\n");
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Fatal Error: bad number of argument\nUsage: %s <config_file.txt>\n",argv[0]);
		return 1;
	}
	
	problem pb = read_config(argv[1]);
	print_mat_cost(pb);
}