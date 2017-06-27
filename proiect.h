#define MAX 100
#define MAX_2 30
#define MAX_3 200

struct bazacunostinte
{
    int a,r[MAX][MAX],k;
};

struct cautare
{
    struct Nod *adr[MAX_3];
    int n_adr,l,ok;
};



struct Nod
{
    int r[MAX_3];
    Nod *leg[MAX];
};

extern Nod *head;

void citire();
void atribuire();
void creare_arbore(Nod *p,int r[]);
void afisare_arbore(Nod *p, Nod *q);
void initializare_mat();
void a_star(Nod *p, Nod *q);
void afisare();
