#include<stdio.h>
#include<stdlib.h>

typedef struct lista
{
    int freq;
    char simbolo;
    struct lista *prox;
}Lista;

typedef struct fila
{
    Lista *ini;
    Lista*fim;
} Fila;

Fila* fila_cria()
{
    Fila *f=(Fila*)malloc(sizeof(Fila));
    f->fim=f->ini=NULL;
    return f;
}

int fila_busca(Fila *f, char c)
{
    
}

void fila_insere(Fila* f,char c)
{
    Lista* l=(Lista*)malloc(sizeof(Lista));
    l->simbolo=c;
    l->freq=1;
    l->prox=NULL;

    if(f->fim!=NULL)
    {
        f->fim->prox=l;
    }
    else
    {
        f->ini=l;
    }
    f->fim=l;
}

int fila_vazia(Fila* f)
{
    return(f->ini==NULL);
}

void fila_retira(Fila* f,char c,int freq)
{
    Lista *t;
    if(fila_vazia(f))
    {
        printf("Fila Vazia!!\n");
        exit(1);
    }
    t=f->ini;
    c=t->simbolo;
    freq=t->freq;
    f->ini=t->prox;
    if(f->ini==NULL)
        f->fim==NULL;
    free(t);
    return;
}

void fila_libera(Fila *f)
{
    Lista *l=f->ini;
    while(l!=NULL)
    {
        Lista *p=l->prox;
        free(l);
        l=p;
    }
    free(f);
}

