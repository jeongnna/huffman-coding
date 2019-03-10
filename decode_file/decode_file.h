#define MAX_SYMBOLS 256
#define MAX_LEN	100
#define MAX_FILENAME 100

struct tnode
{
    struct  tnode* left; /*used when in tree*/
    struct  tnode*right; /*used when in tree*/  
    int     isleaf;
    int     symbol;
};

struct tnode* talloc(void);
void build_tree(FILE* fp);
void decode(FILE* fin,FILE* fout);
void freetree(struct tnode* root);