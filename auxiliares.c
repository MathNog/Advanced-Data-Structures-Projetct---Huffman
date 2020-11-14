#include<stdio.h>
#include<stdlib.h>

/*Estrutura de um elemento de nossa lista encadeada*/
typedef struct elem
{
    char simbolo;
    int freq;
    struct elem *prox;
    struct elem *esq;
    struct elem *dir;
}Elem;

/*Funções auxiliares para nossa lista encadeada*/

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
        printf("Pont: %p - Simbolo: %d - Freq:% d - Dir: %p - Esq: %p\n",p,p->simbolo,p->freq,p->dir,p->esq);
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

Elem* lista_retira(Elem* lista, Elem* no)
{
    char c=no->simbolo;
    int freq=no->freq;
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

/*Funções auxiliares para criação da árvore de huffman*/

//cria um no da arvore
Elem* novoNoArvore(Elem* min1,Elem* min2)
{
    Elem* soma=(Elem*)malloc(sizeof(Elem));
    soma->freq = (min1->freq) + (min2->freq) +4;
    soma->simbolo='#';
    if(min1->freq>min2->freq)
    {
        soma->esq=min2;
        soma->dir=min1;
    }
    else
    {
        soma->esq=min1;
        soma->dir=min2;
    }
    return soma;
}

//insere o no da arvore criado na lista encadeada
Elem* insereNoArv(Elem* lista, Elem* noArv)
{
    noArv->prox=lista;
    //printf("Insere no arvore ---- %p --- %p\n",noArv,noArv->prox);
    return noArv;
}

Elem* no_copia(Elem* lista)
{
    Elem* novo=(Elem*)malloc(sizeof(Elem));
    
    novo->freq=lista->freq;
    novo->simbolo=lista->simbolo;
    novo->prox=lista->prox;
    novo->dir=lista->dir;
    novo->esq=lista->esq;
    return novo;
}

//so pode ser usada com a lista ordenada
//retira os dois primeiros nos da lista, cria o no pai deles, conecta e reinsere o no pai na lista
Elem* monta_arv(Elem* lista,int *flag)
{
    if(lista->prox==NULL)
    {//chegamos a uma lista de 1 elemento
        *flag=1;
        return lista;
    }
    Elem* min1, *min2;
    min1=no_copia(lista);
    lista=lista_retira(lista,min1);
    //printf("Criamos min1 ------- %p\n",min1);
    min2=no_copia(lista);
    lista=lista_retira(lista,min2);
    //printf("Criamos min2 -------%p\n",min2);

    Elem *noarv=novoNoArvore(min1,min2);
    //printf("Criamos no soma: pont %p - freq %d - esq %p - dir %p\n",noarv,noarv->freq,noarv->esq,noarv->dir);
    lista=insereNoArv(lista, noarv);
    //free(min1);
    //free(min2);
    return lista;
}

/*Funções auxiliares para ordenação da lista*/

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

/*Funcoes para obter os bits de cada simbolo*/

//funcao carrega o parametro seqBits com os bits corretos a fim de gerar o codigo de determinado simbolo
//ela devera ser chamada para cada simbolo do texto original
int geraSeqBits(Elem* arv,char c,char *seqBits,int tam)
{
    if(!(arv->esq||arv->dir)&&arv->simbolo==c)
    {
        seqBits[tam]='\0';
        return 1;
    }
    else
    {
        int achou=0;
        if(arv->esq)
        {
            seqBits[tam]='0';
            achou=geraSeqBits(arv->esq,c,seqBits,tam+1);
        }
        else if(!achou&&arv->dir)
        {
            seqBits[tam]='1';
            achou=geraSeqBits(arv->dir,c,seqBits,tam+1);
        }
        else if (!achou)
        {
            seqBits[tam]='\0';
        }
        return achou;   
    }
}

/*Funcao para escrever os bits obtidos no arquivo de saida (é nossa compactação)*/

void  comprimeDados(FILE* saida,Elem* arv,FILE* entrada)
{
    unsigned char c,aux;
    unsigned tam;
    printf("ENTROUN NO WHILE\n");
    while(fread(&c,1,1,entrada)>=1)//para cada simbolo de nosso texto original
    {
        printf("ENTROUN NO WHILE\n");
        char seqBits[1024]={0};
        geraSeqBits(arv,c,seqBits,tam);//temos a sequencia de bits do simbolo em seqBits

        //precisamos dividir os bits em sequencias de bytes
        for(char *i=seqBits;*i;i++)//para cada bit da nossa sequencia
        {
            aux=aux | (1<<(tam%8));
            printf("%c\n",aux);
        }
        tam+=1;

        if(tam%8==0)//se temos um numero fechado de bytes (demos sorte)
        {
            fwrite(&aux,1,1,saida);//passamos o byte para o arquivo de saida
            aux=0;
        }
        fwrite(&aux,1,1,saida);
        fseek(saida, 256*sizeof(unsigned),SEEK_SET);
        //precisa salvar o tamanho?
        //fwrite(&tam,1,sizeof(unsigned),saida);
    }
}


/*Funções auxiliares para manipulação de árvores binárias*/

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

