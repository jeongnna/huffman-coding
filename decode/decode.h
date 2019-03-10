#define MAX_SYMBOLS 128
#define MAX_LEN     128

struct tnode
{
    struct  tnode* left; /*used when in tree*/
    struct  tnode*right; /*used when in tree*/  
    int     isleaf;
    char     symbol;
};

struct tnode* talloc(void);
void build_tree(FILE* fp);
void decode(FILE* fin,FILE* fout);
void freetree(struct tnode* root);