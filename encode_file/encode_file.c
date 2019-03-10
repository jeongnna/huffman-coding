#include <stdio.h>
#include <stdlib.h>
#include <string.h>	//memset()
#include "encode_file.h"

/*global variables*/
char code[MAX_SYMBOLS][MAX_LEN];
struct tnode* root=NULL; //tree of symbols
struct tnode* qhead=NULL; //list of current symbols
int freq[MAX_SYMBOLS];
int NCHAR; //number of symbols

/*
    @function   talloc
    @desc       allocates new node 
*/
struct tnode* talloc(int symbol,int freq)
{
    struct tnode* p=(struct tnode*)malloc(sizeof(struct tnode));
    if(p!=NULL)
    {
        p->left=p->right=p->parent=p->next=NULL;
        p->symbol=symbol;
        p->freq=freq;
		p->isleaf=1;
    }
    return p;
}

/*
    @function display_tnode_list
    @desc     displays the list of tnodes during code construction
*/
void pq_display(struct tnode* head)
{
    struct tnode* p=NULL;
    printf("list:");
    for(p=head;p!=NULL;p=p->next)
    {
        printf("(%c,%d) ",p->symbol,p->freq);
    }
    printf("\n");
}

/*
    @function pq_insert
    @desc     inserts an element into the priority queue
    NOTE:     makes use of global variable qhead
*/
void pq_insert(struct tnode* p)
{
    struct tnode* curr=NULL;
    struct tnode* prev=NULL;
    if (p->freq==0) return; //no insert
    if(qhead==NULL) //qhead is null
    {
		/*TODO: write code to insert when queue is empty*/
 	    qhead = p;
    }
    /*TODO: write code to find correct position to insert*/
    curr = qhead;
    while (curr != NULL) {
 	   if (curr->freq > p->freq) {
 		   break;
 	   }
	   else if (curr->freq == p->freq && curr->symbol == 0 && p->symbol != 0); //additional condition (a)
	   else if (curr->freq == p->freq && curr->symbol != 0 && p->symbol == 0) break; //additional condition (a)
	   else if (curr->freq == p->freq && curr->symbol == 0 && p->symbol == 0) break;//additional condition (c)
	   else if (curr->freq == p->freq && curr->symbol < p->symbol) break; //additional condition (b)
	   prev = curr;
	   curr = curr->next;
   }
   if(curr==qhead)
   {
   	 	/*TODO: write code to insert before the current start*/
	   p->next = curr;
	   qhead = p;
   }
   else /*insert between prev and next*/
   {
	 	/*TODO: write code to insert in between*/
	   prev->next = p;
	   p->next = curr;
   }
}

/*
    @function pq_pop
    @desc     removes the first element
    NOTE:     makes use of global variable qhead
*/

struct tnode* pq_pop()
{
    struct tnode* p=NULL;
    /*TODO: write code to remove front of the queue*/
	if (qhead == NULL) return qhead;
	p = qhead;
	qhead = p->next;
    return p;
}

/*
	@function generate_code
	@desc     generates the string codes given the tree
	NOTE: makes use of the global variable root
*/
void generate_code(struct tnode* root,int depth)
{
	int symbol;
	int len; /*length of code*/
    int i;
	struct tnode * curr;
	if(root->isleaf)
	{
		symbol=root->symbol;
		len   =depth;
		/*start backwards*/
		code[symbol][len]=0;
		/*
			TODO: follow parent pointer to the top
			to generate the code string
		*/
		curr = root;
		for (i = len; i > 0; i--) {
			if (curr->parent->left == curr)
				code[symbol][i-1] = '0';
			if (curr->parent->right == curr)
				code[symbol][i-1] = '1';
			curr = curr->parent;
		}
		printf("built code:%c,%s\n",symbol,code[symbol]);
	}
	else
	{
		generate_code(root->left,depth+1);
		generate_code(root->right,depth+1);
	}
	
}

/*
	@func	dump_code
	@desc	output code file
*/
void dump_code(FILE* fp)
{
	int i=0;
	for(i=0;i<MAX_SYMBOLS;i++)
	{
		if(code[i][0]) /*non empty*/
			fprintf(fp,"%d %s\n",i,code[i]);
	}
}

/*
	@func	encode
	@desc	outputs compressed stream
*/
void encode(FILE* fin,FILE* fout)
{
	int i;
	while((i=fgetc(fin))!=EOF)
	{
		fprintf(fout,"%s",code[i]);
	}
}

/*
	@func	compfreq
	@desc	compute each symbol's frequency
*/
void compfreq(FILE* fp) {
	int i;
	NCHAR=0;
	while ((i=fgetc(fp))!=EOF)
		if (freq[i]++==0) NCHAR++;
	printf("The number of symbols: %d\n", NCHAR);
}

/*
	@func	freetree
	@desc	clears all memories in a tree
*/
void freetree(struct tnode* root)
{
	if (!root) return;
	freetree(root->left);
	freetree(root->right);
	free(root);
}