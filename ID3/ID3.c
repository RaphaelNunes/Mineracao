#include <stdio.h>
#include <stdlib.h>
#include "ID3.h"

//pega os elementos das matrizes e a transformam em numeros referentes
void passarArqParaNum(Esquema *esquemas[] , int tamEsq , Lista **lista, int *numDistintos)
{
    FILE *leitura = fopen("Joga-Tenis.txt","r");
    FILE *escrita = fopen("Joga-Tenis-Num.txt","w");
    char linha[200];
    char palavra[30];
    int numReferente = 0;
    int i =0 , aux = 0 , posEsq = 0 , intRef;
    if(leitura == NULL || escrita == NULL)
    {
        printf("Erro na abertura de algum arquivo");
    }
    else
    {
        fgets(linha,sizeof(linha),leitura);
        //Preenche o vetor com o nome das estruturas
        while(linha[i] != '\n')
        {
            if(linha[i]!= ' ')
            {
                palavra[aux] = linha[i];
                aux++;
            }
            else
            {
                //esquema[]
                esquemas[posEsq] = criaEsq(palavra);
                aux = 0;
                posEsq++;
                //esvazia o vetor palavra;
                strncpy(palavra,"",sizeof(palavra));
            }
            i++;
        }
        esquemas[posEsq] = criaEsq(palavra);
        strncpy(palavra,"",sizeof(palavra));

        //le os atributos e cria uma matriz com numReferentes
        aux = 0;
        i =0;
        while( (fgets(linha,sizeof(linha),leitura)) !=NULL)
        {
            while(linha[i] != '\0')
        {
                if(linha[i]== ' ' || linha[i] =='\n' || (linha[i+1] =='\0' && linha[i] != '\n'))
                {   //pegar o ultimo caracter da ultima linha
                    if(linha[i+1] =='\0' && linha[i] != '\n')
                        palavra[aux] = linha[i];
                    //busca o inteiro que representa a string na lista
                    intRef = buscaLista((*lista) , palavra);
                    //printf("%s ",palavra);
                    if(intRef == -1)
                    {
                        (*lista) = insere(palavra,numReferente,(*lista));
                        fprintf(escrita,"%d ",numReferente);
                        numReferente++;
                    }
                    else{
                        fprintf(escrita,"%d ",intRef);
                    }
                    aux = 0;
                    //esvazia o vetor palavra;
                    strncpy(palavra,"",sizeof(palavra));
                }
                     else
                {
                    palavra[aux] = linha[i];
                    aux++;
                }
            i++;
        }
        fprintf(escrita,"\n");
        i =0;
        }
        *numDistintos = numReferente;
        fclose(leitura);
        fclose(escrita);
    }

}

void carregaArquivo(int matriz[linhas][colunas])
{
    FILE *arquivo = fopen("Joga-Tenis-Num.txt","r");
    if(arquivo == NULL)
        printf("Erro ao abrir arquivo na função Carrega arquivo");
    else{
        char frase[20] , num[10];
        int i =0 , aux = 0, lin =0 , col=0  ,teste =0;
        while(fgets(frase,sizeof(frase),arquivo)!= NULL)
        {
            while(frase[i]!='\n')
            {
                if(frase[i]!=' ' && frase[i]!='\n')
                {
                    num[aux] = frase[i];
                    aux++;
                }
                else
                {   //printf("%s ",num);
                    matriz[lin][col] = atoi(num);
                    teste = atoi(num);
                    col++;
                    strncpy(num,"",sizeof(num));
                    aux = 0;

                }
                i++;
            }
            col =0;
            i =0;
            lin++;
        }
        fclose(arquivo);
    }
}

Esquema *criaEsq(char nome[])
{
    Esquema *nova = (Esquema*)malloc(sizeof(Esquema));
    nova->filho = NULL;
    strncpy(nova->nome,nome,sizeof(nova->nome));
    //printf("%s",nova->nome);
    return nova;

}

void imprimeEsq(Esquema *esquemas)
{
    //printf("entesta");
    int i = 0;
    Esquema *aux;
    aux = esquemas;
    printf("%s\n",aux->nome);

    if(aux->filho == NULL)
     printf("Filho NULL\n");
}

int buscaLista(Lista *lista , char palavra[])
{
    Lista *aux;
    aux = lista;
    int iguais;
    while(aux != NULL)
    {
    iguais = strcmp(aux->nome,palavra);
    if(iguais == 0)
      return aux->intReferente;
    aux = aux->proximo;
    }
    return -1;
}

Lista *insere(char nome[],int intReferente,Lista *lista)
{
    Lista *nova = (Lista*)malloc(sizeof(Lista));
    nova->intReferente = intReferente;
    strncpy(nova->nome,nome,sizeof(nova->nome));
    nova->proximo = lista;
    return nova;
}

void imprimeMatriz(int matriz[linhas][colunas]){
    int lin = 0 , col = 0 ;
    for(lin;lin < linhas ; lin ++)
    {
        for(col;col < colunas ; col++)
            printf("%d ",matriz[lin][col]);
        col = 0;
        printf("\n");
    }
}
float calculaEntropiaGeral(int instancias[] , ListaSim *lista , int quantAmostra)
{
    float somatorio = 0;
    ListaSim *aux;
    aux = lista;
    while(aux != NULL)
    {   //printf("%d",aux->valor);
        somatorio = somatorio + calculaEntropia(instancias[aux->valor],quantAmostra);
        aux = aux->proximo;
    }
    return somatorio;
}

float calculaEntropia(int quantidaClasse, int quantAmostra)
{
    float somatorio = 0;
    float prob = 0;
    prob = quantidaClasse/(float)quantAmostra;
    //printf("%d %d\n",quantidaClasse,quantAmostra);
    somatorio =  somatorio - (prob*(log(prob)/log(2)));
    return somatorio;
}

/*
Instancia *insereAtributos(int atrib , int quantidade , Instancia *proximo){
    Instancia *novo = (Instancia*)(malloc(sizeof(Instancia)));
    novo->proximo = proximo;
    novo->atrib = atrib;
    novo->quantidade = quantidade;
    return novo;
} */

void calculaGanho(int matriz[linhas][colunas] , Esquema *esquemas , int instancias[] ,int numDistintos){

   int lin , i;
   float entropiageral;
   ListaSim *lista_simples = NULL;
   for(lin = 0 ; lin < linhas ; lin ++)
   {
        if(instancias[ matriz[lin][colunas-1] ] == 0)
        {
            instancias[matriz[lin][colunas-1] ]= 1;
            lista_simples = insereListaSim(lista_simples,matriz[lin][colunas-1]);
        }
        else
            instancias[matriz[lin][colunas-1] ] ++;
   }
   entropiageral = calculaEntropiaGeral(instancias,lista_simples,lin);
   printf("%f\n",entropiageral);
   Instancias *classes[numDistintos];
   for( i = 0 ; i < numDistintos ; i++)
    classes[numDistintos] = NULL;

   for(lin = 0; lin < linhas; lin ++)
        if(classes[i]==NULL)
            classes[i] = criaInstancias(numDistintos,lin,matriz[lin][colunas-1]);
        else
            classes[i] = incrementaInstancia(classes[i],matriz[lin][colunas-1],lin);

}

ListaSim *insereListaSim(ListaSim *lista , int valor){
    ListaSim *nova = (ListaSim*)malloc(sizeof(ListaSim));
    nova->proximo = lista;
    nova->valor = valor;
    return nova;
}

Instancias *criaInstancias(int numDistintos , int lin , int refVet){
    int i;
    Instancias *nova = (Instancias*)malloc(sizeof(Instancias));
    nova->classe = (int*)malloc(sizeof(int)*numDistintos);
    for(i = 0 ; i < numDistintos ; i ++)
        nova->classe[i] = 0 ;
    nova->classe[refVet] = 1;
    nova->posRefVet = NULL;
    nova->posRefVet = insereListaSim(nova->posRefVet,refVet);
    nova->quantidade = 1;
    nova->linhasDeOcorrencia = NULL;
    nova->linhasDeOcorrencia = insereListaSim(nova->linhasDeOcorrencia,lin);
    nova->entropia = 0;
    return nova;
}

Instancias *incPosRef(Instancias *inst , int refVet)
{
    inst->posRefVet = insereListaSim(inst->posRefVet,refVet);
    return inst;
}

Instancias *incLinOcor(Instancias *inst , int lin)
{
    inst->linhasDeOcorrencia = insereListaSim(inst->linhasDeOcorrencia,lin);
    return inst;
}
//incrementa a ocorrencia e o vetor
Instancias *incrementaInstancia(Instancias *inst , int refVet , int lin)
{
    if(inst->classe[refVet] == 0)
    {
        inst = incPosRef(inst,refVet);
        inst = incLinOcor(inst,lin);
        inst->quantidade++;
        inst->classe[refVet]++;
    }
    else
    {
        inst = incLinOcor(inst,lin);
        inst->classe[refVet]++;
        inst->quantidade++;
    }
    return inst;
}

void imprimeInstancia(Instancias *inst)
{
    Instancias *aux;
    aux = inst;
    printf("Quantidade : %d\n Entropia : %f \n",aux->quantidade);


}


