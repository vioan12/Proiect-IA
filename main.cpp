#include"proiect.h"
#include<stdlib.h>
using namespace std;
int main()
{
    int i,d[MAX];
    Nod *p,*q;
    citire();
    atribuire();
    for(i=0;i<=head->r[0];i++)
        d[i]=head->r[i];
    creare_arbore(head,d);
    afisare();
    p=head;
    q=NULL;
    initializare_mat();
    a_star(head,q);
    return 0;
}
