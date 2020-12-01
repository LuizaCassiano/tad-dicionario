#include "Dicionario.h"
#define M 19

Dict tabelaHash[M];

void inicializarTabelaHashLinear()
{
    int i;

    for(i = 0; i < M; i++)
    {
        tabelaHash[i].chave = -1;
    }        
}

int gerarCodigoHash(int chave)
{
    return chave % M;
}

void inserirTabelaHashLinear(Dict dict)
{
    int indice = gerarCodigoHash(dict.chave);

    while(tabelaHash[indice].chave != -1)
    {
        indice = gerarCodigoHash(indice + 1);
    }
        
    tabelaHash[indice] = dict;
}

Dict* buscarTabelaHashLinear(int chave)
{
    int indice = gerarCodigoHash(chave);

    while(tabelaHash[indice].chave != -1){

        if(tabelaHash[indice].chave == chave)
            return &tabelaHash[indice];
        else
            indice = gerarCodigoHash(indice + 1);
    }
    return NULL;
}

void imprimir()
{
    int i;

    for(i = 0; i < M; i++){

        if(tabelaHash[i].chave != -1)
            printf("Numero: %d\n", tabelaHash[i].chave);
    }
}

void removendoHashLinear(int chave)
{
    int i;

    for (i = 0; i < M; i++)
    {
        if(tabelaHash[i].chave == chave)
        {
            tabelaHash[i].chave = -1;
        }
    }   
}