#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encode.h"

extern char code[MAX_SYMBOLS][MAX_LEN];
extern struct tnode* root;
extern struct tnode* qhead;



int main()
{
    /*test pq*/
    struct tnode* p=NULL;
    struct tnode* lc,*rc;
    float freq[]={0.01,0.04,0.05,0.11,0.19,0.20,0.4};
	int   NCHAR=7; /*number of characters*/
    int i=0;
	const char *CODE_FILE="code.txt";
	const char *OUT_FILE="encoded.txt";
	FILE* fout=NULL;

	/*zero out code*/
	memset(code,0,sizeof(code));

	/*testing queue*/
    pq_insert(talloc('a',0.1));
    pq_display(qhead);
    pq_insert(talloc('b',0.2));
    pq_display(qhead);
    pq_insert(talloc('c',0.15));
    pq_display(qhead);

    /*making sure it pops in the right order*/
	puts("making sure it pops in the right order");
	while((p=pq_pop()))
    {
        free(p);
    }
	qhead=NULL;

    /*initialize with freq*/
    for(i=0;i<NCHAR;i++)
    {
        pq_insert(talloc('a'+i,freq[i]));
    }

    /*build tree*/
    for(i=0;i<NCHAR-1;i++)
    {
        lc=pq_pop();
        rc=pq_pop();
        p=talloc(0,lc->freq+rc->freq); //create parent
        lc->parent=rc->parent=p; //set parent link
        p->right=rc; p->left=lc; //set child link
		p->isleaf=0; //make it non-leaf
        pq_insert(p); //add the new node to the queue
    }
    root=pq_pop(); //get root
	generate_code(root,0); //build code
	puts("code:"); //output code
	fout=fopen(CODE_FILE,"w");
	dump_code(stdout);
	dump_code(fout);
	fclose(fout);

	/*encode a sample string*/
	puts("orginal:aged egg faced bad cabbage");
	fout=fopen(OUT_FILE,"w");
	encode("aged egg faced bad cabbage",stdout);
	encode("aged egg faced bad cabbage",fout);
	fclose(fout);
	printf("\n");

	/*TODO: clear resources*/
	freetree(root);
	
    return 0;
}