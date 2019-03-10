#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode_file.h"

/*global variables*/
struct tnode* root=NULL; /*tree of symbols*/

/*
    @function   talloc
    @desc       allocates new node 
*/
struct tnode* talloc()
{
    struct tnode* p=(struct tnode*)malloc(sizeof(struct tnode));
    if(p!=NULL)
    {
        p->left=p->right=NULL;
        p->symbol=0;
		p->isleaf=0;
    }
    return p;
}

/*
    @function build_tree
    @desc     builds the symbol tree given the list of symbols and code.h
	NOTE: alters the global variable root that has already been allocated in main
*/
void build_tree(FILE* fp)
{
	int	symbol;
	char	strcode[MAX_LEN];
	int		items_read;
	int		i,len;
	struct	tnode* curr=NULL;

	while(!feof(fp))
	{
		items_read = fscanf(fp,"%d %s\n",&symbol,strcode); 
		if(items_read!=2) break;
		curr = root;
		len = strlen(strcode);
		for(i=0; i<len; i++)
		{
			/*TODO: create the tree as you go*/
			if (strcode[i]=='1')
			{
				if (curr->right == NULL)
					curr = curr->right = talloc();
				else
					curr = curr->right;
			}
			else if (strcode[i]=='0')
			{
				if (curr->left==NULL)
					curr = curr->left = talloc();
				else
					curr = curr->left;
			}
		}

		/*assign code*/
		curr->isleaf=1;
		curr->symbol=symbol;
		printf("inserted symbol:%c\n",symbol);
	}
}

/*
	function decode
*/
void decode(FILE* fin,FILE* fout)
{
	char c;
	struct tnode* curr=root;
	while((c=getc(fin))!=EOF)
	{
		/*TODO:
			traverse the tree
			print the symbols only if you encounter a leaf node
		*/
		curr = root;
		while (!curr->isleaf)
		{
			if (c=='1')
				curr = curr->right;
			else
				curr = curr->left;

			if (curr->isleaf == 0)
				c = getc(fin);
		}
		fprintf(fout, "%c", curr->symbol);
	}
	printf("\n");
}

/*
	@function freetree
	@desc	  cleans up resources for tree
*/

void freetree(struct tnode* root)
{
	if(root==NULL) return;
	freetree(root->right);
	freetree(root->left);
	free(root);
}