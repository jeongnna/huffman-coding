#define MAX_SYMBOLS 256
#define MAX_LEN	100
#define MAX_FILENAME 100

struct tnode
{
    struct  tnode* left; //used when in tree
    struct  tnode*right; //used when in tree
    struct  tnode*parent;//used when in tree
    struct  tnode* next; //used when in list
    int		freq;
    int     isleaf;
    int     symbol;
};

struct tnode* talloc(int symbol,int freq);
void pq_display(struct tnode* head);
void pq_insert(struct tnode* p);
struct tnode* pq_pop(void);
void generate_code(struct tnode* root,int depth);
void dump_code(FILE* fp);
void encode(FILE* fin,FILE* fout);
void compfreq(FILE* fp);
void freetree(struct tnode* root);