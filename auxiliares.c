#include<stdio.h>
#include<stdlib.h>


typedef struct elem
{
    char simbolo;
    int freq;
    struct elem *prox;
    struct elem *esq;
    struct elem *dir;
}Elem;

Elem *lista_cria()
{
    return NULL;
}

Elem* lista_insere(Elem* lista, char c)
{
    Elem *novo=(Elem*)malloc(sizeof(Elem));
    novo->simbolo=c;
    novo->freq=1;
    novo->prox=lista;
    novo->esq=novo->dir=NULL;
    return novo;
}

void lista_imprime(Elem *lista)
{
    Elem *p;
    for(p=lista;p!=NULL;p=p->prox)
    {
        printf("%d - %d\n",p->simbolo,p->freq);
    }
}

int lista_vazia(Elem* lista)
{
    if(lista==NULL)
        return 1;
    else
    {
        return 0;
    }    
}

int lista_busca(Elem*lista, char c)
{
    Elem* p;
    for(p=lista;p!=NULL;p=p->prox)
    {
        if(p->simbolo==c)
        {
            p->freq++;
            return 1;
        }
    }
    return 0;
}

Elem* lista_retira(Elem* lista, char c, int freq)
{
    Elem* a=NULL;
    Elem* p=lista;
    while(p!=NULL&&p->simbolo!=c)
    {
        a=p;
        p=p->prox;
    }
    if(p==NULL)
        return lista;
    freq=p->freq;
    if(a==NULL)
        lista=p->prox;
    else
    {
        a->prox=p->prox;
    }
    free(p);
    return lista;
    
}

//cria um no da arvore
Elem* novoNoArvore(Elem* min1,Elem* min2)
{
    Elem* soma=(Elem*)malloc(sizeof(Elem));
    soma->freq=min1->freq+min2->freq;
    soma->simbolo='#';
    if(min1->freq>=min2->freq)
    {
        soma->esq=min2;
        soma->dir=min1;
    }
    else
    {
        soma->esq=min1;
        soma->esq=min2;
    }
    return soma;
}

//insere o no da arvore criado na lista encadeada
Elem* insereNoArv(Elem* lista, Elem* noArv)
{
    noArv->prox=lista;
    return noArv;
}

//so pode ser usada com a lista ordenada
//retira os dois primeiros nos da lista, cria o no pai deles, conecta e reinsere o no pai na lista
Elem* monta_arv(Elem* lista,int *flag)
{
    if(lista->prox==NULL){//chegamos a uma lista de 1 elemento
        *flag=1;
        return lista;
    }
    Elem* min1, *min2;
    min1=lista;
    lista=lista->prox;
    min2=lista;
    lista=lista->prox;
    Elem *noarv=novoNoArvore(min1,min2);
    lista=insereNoArv(lista, noarv);
    free(min1);
    free(min2);
    return lista;
}

Elem* merge_sorted(Elem* a, Elem* b)
{
    Elem* res=NULL;

    if(a==NULL)
        return b;
    else if (b==NULL)
        return a;
    
    if(a->freq<= b->freq)
    {
        res=a;
        res->prox=merge_sorted(a->prox,b);
    }
    else
    {
        res=b;
        res->prox=merge_sorted(a,b->prox);
    }
    return res;  
}

void frente_tras(Elem* a, Elem**b, Elem**c)
{
    Elem* rap;
    Elem *dev;
    dev=a;
    rap=a->prox;

    while(rap!=NULL)
    {
        rap=rap->prox;
        if(rap!=NULL)
        {
            dev=dev->prox;
            rap=rap->prox;
        }
    }
    *b=a;
    *c=dev->prox;
    dev->prox=NULL;
}

void merge_sort_lista(Elem** lista)
{
    Elem* head= *lista;
    Elem* a;
    Elem* b;

    if(lista_vazia(head)||head->prox==NULL)
        return;

    frente_tras(head,&a,&b);

    merge_sort_lista(&a);
    merge_sort_lista(&b);

    *lista=merge_sorted(a,b);
}

void exibe_preordem(Elem *p)
{
    if (p == NULL)
        printf("arvore nao foi criada\n");

    printf("ptr_no=%p, simbolo=%d freq=%d esq=%p dir=%p\n", p, p->simbolo,p->freq, p->esq, p->dir);
    
    if (p->esq != NULL)
        exibe_preordem(p->esq);
    if (p->dir != NULL)
        exibe_preordem(p->dir);
}

void lista_libera(Elem* lista)
{
    Elem* t;
    Elem* p=lista;
    while(p!=NULL)
    {
        t=p->prox;
        free(p);
        p=t;
    }
}

