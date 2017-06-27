#include"proiect.h"
#include<stdio.h>
#include<fstream>
#include<string.h>
#include<stdlib.h>


 int n,n_mat,v[10000];
 struct bazacunostinte baza[MAX_2];
 cautare mat[MAX_3];
 Nod *head;

FILE *file,*file2;
void citire()
{
    int i,j;
    char c,d[100];
    v[0]=0;
    file=fopen("in.txt","r");
    while(!feof(file)){
        c=fgetc(file);
        if(((c>=48)&&(c<=57))||((c>=97)&&(c<=122))){
            d[strlen(d)]=c;
            d[strlen(d)]=NULL;
        }else{
            if(strlen(d)!=0){
                if((d[0]>=97)&&(d[0]<=122)){
                    v[++v[0]]=d[0];
                }
                if((d[0]>=48)&&(d[0]<=57)){
                    v[++v[0]]=atoi(d);
                }
                for(i=0;i<100;i++)
                    d[i]=NULL;
            }
        }
    }
    fclose(file);
}

void atribuire()
{
    int i,*p,j,m;
    p=v+1;
    n=*p;
    p++;
    for(i=0;i<n;i++){
        baza[i].a=*p;
        p++;
        baza[i].k=*p;
        p++;
        for(j=0;j<baza[i].k;j++){
            baza[i].r[j][0]=*p;
            p++;
            for(m=1;m<=baza[i].r[j][0];m++){
                baza[i].r[j][m]=*p;
                p++;
            }
        }
    }
    head=new Nod;
    head->r[0]=*p;
    p++;
    for(i=1;i<=head->r[0];i++){
        head->r[i]=*p;
        p++;
    }
}

void creare_arbore(Nod *p,int r[MAX_3])
{
    int i,j,sw,h,l,id;
    int rr[MAX_3];
    if(p!=NULL){
        for(i=0,sw=0;(i<n)&&(sw==0);i++)
            if(r[1]==baza[i].a){
                sw=1;
                id=i;
            }
        if(sw!=0){
            if(baza[id].k>0){
                for(i=0;i<baza[id].k;i++){
                    for(j=1;j<=r[0];j++)
                        rr[j]=r[j];
                    rr[0]=r[0];
                    for(h=1;h<baza[id].r[i][0];h++){
                        for(j=rr[0];j>=1;j--)
                            rr[j+1]=rr[j];
                        rr[0]=rr[0]+1;
                    }
                    for(h=1;h<=baza[id].r[i][0];h++){
                        rr[h]=baza[id].r[i][h];
                    }
                    p->leg[i]=new Nod;
                    p->leg[i]->r[0]=rr[0];
                    for(l=1;l<=rr[0];l++)
                        p->leg[i]->r[l]=rr[l];
                    creare_arbore(p->leg[i],rr);
                }
                p->leg[baza[id].k]=NULL;
            }else{
                if(baza[id].k==0){
                    if(p->r[0]>0){
                        for(j=1;j<r[0];j++)
                            r[j]=r[j+1];
                        r[0]=r[0]-1;
                        p->leg[0]=new Nod;
                        p->leg[0]->r[0]=r[0];
                        for(l=1;l<=r[0];l++)
                            p->leg[0]->r[l]=r[l];
                        p->leg[1]=NULL;
                        creare_arbore(p->leg[0],r);
                    }else{
                        p->leg[0]=NULL;
                    }
                }
            }
        }else{
            p->leg[0]=NULL;
        }
    }
}

void afisare_arbore(Nod *p, Nod *q)
{
    int i,j;
    if(p!=NULL){
    	if(p->r[0]==0)
    	    fprintf(file2,"0 ");
        for(i=1;i<p->r[0];i++)
            fprintf(file2,"%c^",p->r[i]);
        fprintf(file2,"%c",p->r[p->r[0]]);
        if(q!=NULL){
        	fprintf(file2,"(");
            for(j=1;j<q->r[0];j++)
                fprintf(file2,"%c^",q->r[j]);
            fprintf(file2,"%c",q->r[q->r[0]]);
            fprintf(file2,")");
            q=p;
        }else{
        	q=p;
        }
        fprintf(file2,"\n");
        for(i=0;p->leg[i]!=NULL;i++)
            afisare_arbore(p->leg[i],q);
    }
}

void afisare()
{
    Nod *p,*q;
    file2=fopen("out.txt","w");
    p=head;
    q=NULL;
    afisare_arbore(p,q);
    fclose(file2);
}

void initializare_mat()
{
    int i;
    for(i=0;i<MAX_3;i++)
        mat[i].n_adr=mat[i].l=mat[i].ok=0;

}

void a_star(Nod *p, Nod *q)
{
    int i;
    if (p!=NULL){
        if(q==NULL){
            n_mat=1;
            mat[0].l=p->r[0];
            mat[0].adr[0]=p;
            mat[0].n_adr=1;
            q=p;
            for(i=0;p->leg[i]!=NULL;i++)
                a_star(p->leg[i],q);
        }//else{}

    }
}
