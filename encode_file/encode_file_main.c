#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encode_file.h"

extern char code[MAX_SYMBOLS][MAX_LEN];
extern struct tnode* root;
extern struct tnode* qhead;
extern int freq[MAX_SYMBOLS];
extern int NCHAR;


int main()
{
    struct tnode *p=NULL;
    struct tnode *lc, *rc;
    int i=0;
	char IN_FILE[MAX_FILENAME];
	char CODE_FILE[MAX_FILENAME];
	char OUT_FILE[MAX_FILENAME];
	FILE* fin = NULL;
	FILE* fout = NULL;

	/*zero out code*/
	memset(code, 0, sizeof(code));


	/*input file names*/
	printf("Input text file name: ");	scanf("%s", &IN_FILE);
	printf("Input code file name: ");	scanf("%s", &CODE_FILE);
	printf("Input encoded file name: ");	scanf("%s", &OUT_FILE);
	fin = fopen(IN_FILE, "r");
	if (fin==NULL) {
		printf("%s 파일을 찾을 수 없습니다. 파일 경로를 확인하십시오.\n", IN_FILE);
		system("pause");
		return 0;
	}
	fclose(fin);

    /*initialize with freq*/
	fin=fopen(IN_FILE, "r");
	compfreq(fin); //compute frequency
	fclose(fin);
    for(i=0;i<MAX_SYMBOLS;i++)
        pq_insert(talloc(i,freq[i]));
	pq_display(qhead);

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
	fout=fopen(CODE_FILE, "w");
	dump_code(stdout);
	dump_code(fout);
	fclose(fout);
	
	fin=fopen(IN_FILE, "r");
	fout=fopen(OUT_FILE, "w");
	encode(fin, fout);

	/*TODO: clear resources*/
	freetree(root);
	
    return 0;
}