#include <stdio.h>
#include <stdlib.h>
#include "decode.h"

extern struct tnode* root;

int main()
{
	const char* IN_FILE="out13.txt";
	const char* CODE_FILE="code13.txt";
	const char* OUT_FILE="decoded.txt";
	FILE* fout;
	FILE* fin;

	/*allocate root*/
	root=talloc();
	fin=fopen(CODE_FILE,"r");

	/*build tree*/
	build_tree(fin);
	fclose(fin);

	/*decode*/
	fin=fopen(IN_FILE,"r");
	fout=fopen(OUT_FILE,"w");
	decode(fin,fout);
	fclose(fin);
	fclose(fout);

	/*cleanup*/
	freetree(root);

	return 0;
}