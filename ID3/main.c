#include <stdio.h>
#include <stdlib.h>
#include "ID3.h"
int main()
{
    int lin = 14 , col = 5 , i =0;
    linhas = lin;
    colunas = col;
    //guarda o numero que representa a string
    Esquema *esquemas[colunas];
    int matriz[linhas][colunas];
   // Atributos *
    for(i ; i < colunas ; i++)
            esquemas[i] = NULL;
    //contem os valores que cada string respresenta
    int numDistintos;
    Lista *intRefs = NULL;
    passarArqParaNum(esquemas,colunas,&intRefs,&numDistintos);
    carregaArquivo(matriz);
    int instancias[numDistintos];
    for( i =0 ; i < numDistintos ; i++)
        instancias[i] = 0;

    calculaGanho(matriz,esquemas,instancias,numDistintos);
    /*
    //imprime os esquemas
    while(i < coluna)
    {
        imprimeEsq(esquemas[i]);
        i++;
    }
    */
   //passarArqParaNum(esquemas , coluna);
   return 0;
}
