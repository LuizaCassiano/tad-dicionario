#include <stdio.h>
#include <stdlib.h>
#include "Dicionario.h"

struct hash
{
    int qtd, tableSize;
    struct dic **itens;
};

Hash *criaHash(int tableSize)
{
    Hash *ha = (Hash *)malloc(sizeof(Hash));

    if (ha != NULL)
    {
        int i;
        ha->tableSize = tableSize;
        ha->itens = (struct dic **)malloc(tableSize * sizeof(struct dic *));

        if (ha->itens == NULL)
        {
            free(ha);
            return NULL;
        }

        ha->qtd = 0;

        for (i = 0; i < ha->tableSize; i++)
        {
            ha->itens[i] = NULL;
        }

        return ha;
    }

    return NULL;
}

void liberaHash(Hash *ha)
{
    if (ha != NULL)
    {
        int i;
        for (i = 0; i < ha->tableSize; i++)
        {
            if (ha->itens[i] != NULL)
            {
                free(ha->itens[i]);
            }
            free(ha->itens);
            free(ha);
        }
    }
}

int chaveDivisao(int chave, int tableSize)
{
    return (chave & 0x7FFFFFFF) % tableSize;
}

int sondagemLinear(int pos, int i, int tableSize)
{
    return ((pos + i) & 0x7FFFFFFF) % tableSize;
}

int inserirHash(Hash* ha, struct dic dic)
{
    if(ha == NULL || ha->qtd == ha->tableSize)
        return 0;

    int chave = dic.chave;
    int i, pos, newPos;
    pos = chaveDivisao(chave, ha->tableSize);

    for (i = 0; i < ha->tableSize; i++)
    {
        newPos = sondagemLinear(pos, i, ha->tableSize);

        if (ha->itens[newPos] == NULL)
        {
            struct dic* novo;
            novo = (struct dic*)malloc(sizeof(struct dic));

            if(novo == NULL)
                return 0;

            *novo = dic;
            ha->itens[newPos] = novo;
            ha->qtd++;
            return 1;
        }        
    }
    return 0;
}

int buscaHash(Hash* ha, int chave, struct dic* dic)
{
    if(ha == NULL)
        return 0;
    
    int i, pos, newPos;
    pos = chaveDivisao(chave, ha->tableSize);

    for (i = 0; i < ha->tableSize; i++)
    {
        newPos = sondagemLinear(pos, i, ha->tableSize);

        if(ha->itens[newPos] == NULL)
            return 0;

        if(ha->itens[newPos]->chave == chave)
        {
            *dic = *(ha->itens[newPos]);
            return 1;
        }
    }
    return 0;
}

void listarHash(Hash* ha)
{
    if(ha == NULL)
    {
        printf("Tabela vazia!\n");
    }        
    else
    {
        int i;
        for (i = 0; i < ha->tableSize; i++)
        {
            if(ha->itens[i] != NULL)
            {
                printf("Numero: %d\n", ha->itens[i]->chave);
            }            
        }        
    }    
}

void removendoHash(Hash* ha, int chave)
{
    if(ha == NULL)
    {
        printf("Tabela vazia!\n");
    }
    else
    {
        int i;
        for (i = 0; i < ha->tableSize; i++)
        {
            if(ha->itens[i] != NULL)
            {
                if(ha->itens[i]->chave == chave)
                {
                    free(ha->itens[i]);
                }
            }  
        }
    }
    
}