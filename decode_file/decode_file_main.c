#include <stdio.h>
#include <stdlib.h>
#include "decode_file.h"

extern struct tnode* root;

int main()
{
	char IN_FILE[MAX_FILENAME];
	char CODE_FILE[MAX_FILENAME];
	char OUT_FILE[MAX_FILENAME];
	FILE* fout = NULL;
	FILE* fin = NULL;

	/*input file names*/
	printf("Input encoded file name: ");	scanf("%s", &IN_FILE);
	printf("Input code file name: ");	scanf("%s", &CODE_FILE);
	printf("Input decoded file name: ");	scanf("%s", &OUT_FILE);
	fin = fopen(IN_FILE, "r");
	if (fin==NULL) {
		printf("%s ������ ã�� �� �����ϴ�. ���� ��θ� Ȯ���Ͻʽÿ�.\n", IN_FILE);
		system("pause");
		return 0;
	}
	fclose(fin);
	fin = fopen(CODE_FILE, "r");
	if (fin==NULL) {
		printf("%s ������ ã�� �� �����ϴ�. ���� ��θ� Ȯ���Ͻʽÿ�.\n", CODE_FILE);
		system("pause");
		return 0;
	}
	fclose(fin);

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