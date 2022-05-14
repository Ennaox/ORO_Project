#include "tree.h"

LIST * init_list(char * val)
{
	LIST * entry = malloc(sizeof(LIST));
	entry->next = NULL;
	entry->path = malloc(100*sizeof(char));
	memset(entry->path,0,100*sizeof(char));
	sprintf(entry->path,"%s\0",val);
	entry->prev = NULL;
	return entry;
}

void add_entry(LIST * liste, char * val)
{
	LIST * tmp = liste;
	while(tmp->next!=NULL)
	{
		tmp = tmp->next;
	}
	LIST * entry = malloc(sizeof(LIST));
	entry->next = NULL;
	entry->path = malloc(100*sizeof(char));
	memset(entry->path,0,100*sizeof(char));
	sprintf(entry->path,"%s\0",val);
	entry->prev = tmp;
	tmp->next = entry;
}

LIST * copy_list(LIST * liste)
{
	LIST * new_liste = init_list(liste->path);
	LIST * tmp = new_liste;
	liste = liste->next;
	while(liste!=NULL)
	{
		add_entry(tmp,liste->path);
		tmp = tmp->next;
		liste = liste->next;
	}
	return new_liste;
}

void free_entry(LIST * liste)
{
	if(liste->next != NULL)
		liste->next->prev = liste->prev;
	liste->prev->next = liste->next;
	free(liste);
}

void find_path(trajet T, NODE * tree)
{
	//3,4,8,5,6,7,2,1,9
	char * path = malloc(100*sizeof(char));
	memset(path,0,100*sizeof(char));
	char * fullpath = malloc(100*sizeof(char));
	memset(fullpath,0,100*sizeof(char));
	LIST *all_path = tree->all_path;
	
	if(!strlen(all_path->path))
	{
		sprintf(path,"%d,%d",T.src,T.dest);
		all_path->path=path;
		return;
	}
	LIST * tmp = all_path;
	while(tmp != NULL)
	{
		int last_site = -1;
		int indice_last;
		for(int i = strlen(tmp->path)-1;i>=0;i--)
		{
			if(tmp->path[i]<='9' && tmp->path[i]>='0'){indice_last = i;}
			else {break;}
		}
		last_site = atoi(tmp->path+indice_last);

		if(T.src == last_site)
		{
			sprintf(tmp->path,"%s,%d",tmp->path,T.dest);
			break;
		}
		last_site = -1;
		sscanf(tmp->path,"%d,",&last_site);
		if(T.dest == last_site)
		{
			char * tmp_char = malloc(100*sizeof(char));
			memset(tmp_char,0,100*sizeof(char));
			sprintf(tmp_char,"%d,\0",T.src);
			strcat(tmp_char,tmp->path);
			memset(tmp->path,0,100*sizeof(char));
			strcpy(tmp->path,tmp_char);
				
			//sprintf(tmp->path,"%s,%s",tmp_char,tmp->path);
			free(tmp_char);
			break;
		}
		else
		{
			if(tmp->next == NULL)
			{
				char * path = malloc(100*sizeof(char));
				memset(path,0,100*sizeof(char));
				sprintf(path,"%d,%d",T.src, T.dest);
				add_entry(tmp,path);
				break;
			}
		}
		tmp=tmp->next;
	}

	tmp = all_path;
	tmp = all_path->next;
	while(tmp!=NULL)
	{
		int last_site_main = 0;
		int last_site_tmp = 0;
		int indice_last_tmp, indice_last_main;
		for(int i = strlen(all_path->path)-1;i>=0;i--)
		{
			if(all_path->path[i]<='9' && all_path->path[i]>='0'){indice_last_main = i;}
			else {break;}
		}
		last_site_main = atoi(all_path->path+indice_last_main);
		
		sscanf(tmp->path,"%d,",&last_site_tmp);
		if(last_site_tmp == last_site_main)
		{
			memset(all_path->path+indice_last_main-1,0,strlen(all_path->path+indice_last_main-1)*sizeof(char));
			sprintf(all_path->path,"%s,%s",all_path->path,tmp->path);
			free_entry(tmp);
			break;
		}
		sscanf(all_path->path,"%d,",&last_site_main);

		for(int i = strlen(tmp->path)-1;i>=0;i--)
		{
			if(tmp->path[i]<='9' && tmp->path[i]>='0'){indice_last_tmp = i;}
			else {break;}
		}
		last_site_tmp = atoi(all_path->path+indice_last_tmp);

		if(last_site_main == last_site_tmp)
		{
			memset(tmp->path+indice_last_tmp-1,0,strlen(tmp->path+indice_last_tmp-1)*sizeof(char));
			sprintf(all_path->path,"%s,%s",tmp->path,all_path->path);
			free_entry(tmp);
			break;
		}
		tmp = tmp->next;
	}
	/*
	int last_indice=0;
	for(int i = strlen(fullpath)-1;i>=0;i--)
	{
		if(fullpath[i]<='9' && fullpath[i]>='0'){last_indice = i;}
			else {break;}
	}
	memset(fullpath+last_indice-1,0,strlen(fullpath+last_indice-1)*sizeof(char));
	*/
}

MAT matdup(MAT src)
{
	MAT dest; 
	dest.dim = src.dim;
	dest.mat = malloc(src.dim*src.dim*sizeof(long));
	for(int i = 0; i<src.dim * src.dim; i++)
	{
		dest.mat[i] = src.mat[i];
	}

	return dest;
}

void desalloc_matrix(MAT matrix)
{
	free(matrix.mat);
}

NODE * init_tree(long value,MAT matrix)
{
	NODE * node = malloc(sizeof(NODE));
	node->value = value;
	node->mat = matrix;
	node->root = node;
	node->father = NULL;
	node->left = NULL;
	node->right = NULL;
	char * val = malloc(100*sizeof(char));
	memset(val,0,100*sizeof(char));
	node->all_path = init_list(val);
	return node;
}


void add_left(NODE * tree)
{
	if(tree->left!= NULL)
	{
		printf("Can't insert, there is already a left child\n");
		return;
	}
	NODE * tmp = malloc(sizeof(NODE));
	tree->left = tmp;
	tmp->value = tree->value;
	tmp->father = tree;
	tmp->mat = matdup(tree->mat);
	tmp->root = tree->root;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->all_path = copy_list(tree->all_path);
	find_path(tree->traj,tmp);
	for(int i = 0; i<tree->mat.dim;i++)
	{
		tmp->mat.mat[i * tmp->mat.dim + tree->traj.dest] = -1;
		tmp->mat.mat[tree->traj.src * tmp->mat.dim + i] = -1;
	}
	LIST * tmp_list = tmp->all_path;
	while(tmp_list!=NULL)
	{
		char * first_site = malloc(10*sizeof(char)); 
		memset(first_site,0,10*sizeof(char));
		int indice_last;
		for(int i = strlen(tmp_list->path)-1;i>=0;i--)
		{
			if(tmp_list->path[i]<='9' && tmp_list->path[i]>='0'){indice_last = i;}
			else {break;}
		}
		int last_val = atoi(tmp_list->path+indice_last); 
		for(int i = 0;i<strlen(tmp_list->path);i++)
		{
			if(tmp_list->path[i]<='9' && tmp_list->path[i]>='0'){first_site[i] = tmp_list->path[i];}
			else {break;}
		}
		int first_val = atoi(first_site);
		tmp->mat.mat[last_val * tmp->mat.dim + first_val] = -1;
		tmp_list = tmp_list->next;
	}
}

void add_right(NODE * tree)
{
	if(tree->right!= NULL)
	{
		printf("Can't insert, there is already a right child\n");
		return;
	}
	tree->right = malloc(sizeof(NODE));
	tree->right->value = tree->value+tree->max_reg;
	tree->right->father = tree;
	tree->right->mat = matdup(tree->mat);
	tree->right->root = tree->root;
	tree->right->left = NULL;
	tree->right->right = NULL;
	tree->right->mat.mat[tree->traj.src * tree->left->mat.dim + tree->traj.dest] = -1;
	tree->right->all_path = copy_list(tree->all_path);
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
	desalloc_matrix(node->mat);
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
	printf("%ld : ",node->value);
	LIST * tmp = node->all_path;
	while(tmp!=NULL)
	{
		printf("%s ;",tmp->path);
		tmp = tmp->next;
	}
	printf(" | ");
	print_tree(node->left);
	print_tree(node->right);
	if(node->left==NULL && node->right==NULL)
	{
		printf("\n");
	}
}