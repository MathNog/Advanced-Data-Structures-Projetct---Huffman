/*Visão geral do processo de compactação de arquivos via algoritmo de Huffman*/

/*Compactação*/
/*
1 - leitura dos dados e armazenamento em memória
2 - construção do heap baseado na frequencia de símbolos 
3 - criacao da arvore de huffman - enquanto houver entradas no heap, pega-se os dois primeiros (menores frequencias)
e cria-se um novo nó para a árvore cuja chave é a soma da frequencia dos elementos do heap. Os dois elementos retirados do heap
sao filhos deste nó criado
4 - construcao da tabela de codigos 
5 - tranformacao do texto original em sequencia de bits - via tabela construida
6 - construcao do fluxo de bytes comprimido
7 - gravacao dos dados em um novo arquivo
*/

/*Descompactação*/
/*
1 - leitura dos dados do arquivo compruimido
2 - reconstrucao da árvore de huffman - via tabela de codigos
3 - reconstrucao do fluxo de bits a partir dos bytes lidos
4 - descompactar os dados - basta percorrer a árvore de Huffman com base na cadeia de bits. 
Sempre que um nó-folha for encontrado, o cabeçote da árvore recomeça no nó raiz para que o próximo símbolo seja lido. Uma cadeia de saída é concatenada toda 
vez que um símbolo é reconhecido. Ao final deste processo, obtém-se a informação original;
5 - gravacao dos dados obtidos
*/

/*Código*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "auxiliares.c"


int main()
{
    //leitura dos dados do arquivo texto
    FILE *f,*saida;
    char dadosOriginais[10000];
    f=fopen("original.txt","rb");
    if(f==NULL)
    {
        printf("Erro na criação do arquivo!\n");
        exit(1);
    }
    fread(&dadosOriginais,sizeof(char),10000,f);
    printf("DADOS ORIINAIS\n%s\n",dadosOriginais);
    fclose(f);

    //criacao do arquivo de saida para os dados compactados
    saida=fopen("texto_compactado.txt","wb");
    if(saida==NULL)
    {
        printf("Erro na criação do arquivo!\n");
        exit(1);
    }

    //carregar a lista com os simbolos e suas frequencias
    Elem *lista=lista_cria();
    int achou;
    for(int i=0;i<strlen(dadosOriginais);i++)
    {
        achou=lista_busca(lista,dadosOriginais[i]);
        if(achou==0)
        {
            lista=lista_insere(lista,dadosOriginais[i]);
        }
    }
    //temos uma lista encadeada onde cada elemento é um simbolo com sua frequencia
    lista_imprime(lista);

    //vamos ordenar esta lista
    printf("\n----------------Impressao da lista ordenada-----------------\n");
    merge_sort_lista(&lista);
    lista_imprime(lista);

    //temos uma lista ordenada em ordem crescente de frequencia de simbolos
    //podemos começar a montar a arvore de huffman
    //ideia - retiro os dois primeiros da lista, criar o no da arvore e reinsiro na lista, ordenando novamente. 
    //fazer isso ate a lista so ter 1 elemento
    Elem* min;
    int flag=0; //flag para parada do while - indica que a lista so tem 1 elemento e a arvore esta pronta
    printf("%p\n",lista);
    printf("\n---------------------Montando a arvore de huffman-----------------\n");
    while(flag!=1)
    {
        lista = monta_arv(lista,&flag);
        merge_sort_lista(&lista);  
    }
    lista_imprime(lista);
    

    exibe_preordem(lista);

    //Nao rodar a partir daqui! Falta acertar a arvore!!!!!!!!!!
    //Uma vez pronta nossa arvore de huffman, precisamos saber o codigo para cada simbolo
    FILE* entrada;
    entrada=fopen("original.txt","rb");
    if(entrada==NULL)
    {
        printf("Erro no arquivo\n");
        exit(1);
    }
    
    comprimeDados(saida,lista,f);

    /*Neste ponto, temos nosso arquivo compactado em "texto_compactado.txt"*/
    /*Verifique externamente o tamanho do arquivo compactado para averiguar se nossa compactação foi reazoável*/

    fclose(saida);
    fclose(entrada);
}
