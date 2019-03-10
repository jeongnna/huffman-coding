#define MAX_SYMBOLS 128
#define MAX_LEN     7

struct tnode
{
    struct  tnode* left; //used when in tree
    struct  tnode*right; //used when in tree
    struct  tnode*parent;//used when in tree
    struct  tnode* next; //used when in list
    float   freq;
    int     isleaf;
    char     symbol;
};

struct tnode* talloc(int symbol,float freq);
void pq_display(struct tnode* head);
void pq_insert(struct tnode* p);
struct tnode* pq_pop(void);
void generate_code(struct tnode* root,int depth);
void dump_code(FILE* fp);
void encode(char* str,FILE* fout);
void freetree(struct tnode* root);