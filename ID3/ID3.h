#ifndef ID3_H_INCLUDED
#define ID3_H_INCLUDED

struct esquema{
    char nome[30];
   // struct arquivo *proximo;
    struct instancia *filho;
};
typedef struct esquema Esquema;

/*
struct instancia{
    int atrib;
    int quantidade;
    struct lista_simples *classes;
    struct lista_simples *amostras;
    struct instancia *proximo;
    };
typedef struct instancia Instancia;
*/

struct lista_simples{
    int valor;
    struct lista_simples *proximo;
};
    typedef struct lista_simples ListaSim;

struct lista{
    char nome[30];
    int intReferente;
    struct lista *proximo;
};
 typedef struct lista Lista;
// \*classe é um vetor onde usar o valor da classe para chegar na possição e nesta posição saber quantas
//vezes ela ocorre . posRefVet serve para saber a onde neste vetor possui classes validas
struct isntancia{
    int quantidade;
    //acessa o indice referente a classe e o valor correspondente é o numero de ocorrencia
    int *classe;
    struct lista_simples *linhasDeOcorrencia;
    struct lista_simples *posRefVet;
    float entropia;
};
typedef struct isntancia Instancias;

int linhas , colunas;

void imprimeMatriz(int matriz[linhas][colunas]);

Esquema *criaEsq(char nome[]);

void carregaArquivo(int matriz[linhas][colunas]);

void passarArqParaNum(Esquema *esquemas[],int tamEsq , Lista **lista ,int *numDistintos);

//void leArquivo(Esquema esquema , Instancia *instancia);

int buscaLista(Lista *lista , char palavra[]);

void imprimeEsq(Esquema *esquemas);

Lista *insere(char nome[],int intReferente,Lista *lista);

float calculaEntropiaGeral(int instancias[] , ListaSim *lista , int quantAmostra);

float calculaEntropia(int quantidaClasse , int quantAmostra);

//Instancia *insereAtributos(int atrib , int quantidade , Instancia *proximo);
//Lspn *inicializa();
void calculaGanho(int matriz[linhas][colunas] , Esquema *esquemas , int instancias[] ,int numDistintos);

ListaSim *insereListaSim(ListaSim *lista , int valor);

Instancias *criaInstancias(int numDistintos , int lin , int refVet);
// se retorna 1 pq inseriu se retornar 0 pq não inseriu
int *buscaIncrementaClasses(Instancias **clas , int classe , int instancia);

void imprimeClasses(Instancias *clas);

Instancias *incPosRef(Instancias *inst , int refVet);

Instancias *incLinOcor(Instancias *inst , int lin);

Instancias *incrementaInstancia(Instancias *inst , int refVet ,int lin);

void imprimeInstancia(Instancias *inst);
#endif // ID3_H_INCLUDED
