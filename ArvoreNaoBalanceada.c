#include <stdio.h>
#include <stdlib.h>
#include "Dicionario.h"

#define false 0;
#define true 1;

void inicializarArvoreNaoBalanceada(Dicionario **pRaiz)
{
    *pRaiz = NULL;
}

void inserirArvoreNaoBalanceada(Dicionario **pRaiz, int numero)
{
    //Se dicionario aponta para null, a inserção é na raiz...
    if (*pRaiz == NULL)
    {
        *pRaiz = (Dicionario *)malloc(sizeof(Dicionario));

        (*pRaiz)->esquerda = NULL;
        (*pRaiz)->direita = NULL;
        (*pRaiz)->chave = numero;
    }
    else
    {
        //Se o dado a ser inserido for menor que o nó atual, recursividade à esquerda
        if (numero < ((*pRaiz)->chave))
        {
            inserirArvoreNaoBalanceada(&((*pRaiz)->esquerda), numero);
        }
        else
        {
            //Se o dado a ser inserido for menor que o nó atual, recursividade à direita
            inserirArvoreNaoBalanceada(&((*pRaiz)->direita), numero);
        }
    }
}

Dicionario *MaiorDireitaNaoBalanceada(Dicionario **no)
{
    if ((*no)->direita != NULL)
    {
        return MaiorDireitaNaoBalanceada(&(*no)->direita);
    }
    else
    {
        Dicionario *aux = *no;

        if ((*no)->esquerda != NULL) //Se nao houver essa verificacao, esse nó vai perder todos os seus filhos da esquerda!
        {
            *no = (*no)->esquerda;
        }
        else
        {
            *no = NULL;
        }

        return aux;
    }
}

Dicionario *MenorEsquerdaNaoBalanceada(Dicionario **no)
{
    if ((*no)->esquerda != NULL)
    {
        return MenorEsquerdaNaoBalanceada(&(*no)->esquerda);
    }
    else
    {
        Dicionario *aux = *no;

        if ((*no)->direita != NULL) //Se nao houver essa verificacao, esse nó vai perder todos os seus filhos da direita!
        {
            *no = (*no)->direita;
        }
        else
        {
            *no = NULL;
        }

        return aux;
    }
}

void removerArvoreNaoBalanceada(Dicionario **pRaiz, int numero)
{
    if (*pRaiz == NULL)
    {
        printf("Numero nao existe na arvore!\n");
        return;
    }

    if (numero < (*pRaiz)->chave)
    {
        removerArvoreNaoBalanceada(&(*pRaiz)->esquerda, numero);
    }
    else if (numero > (*pRaiz)->chave)
    {
        removerArvoreNaoBalanceada(&(*pRaiz)->direita, numero);
    }
    else
    {
        //Se nao e menor nem maior, e o numero que estou procurando!
        Dicionario *pAux = *pRaiz;

        if (((*pRaiz)->esquerda == NULL) && ((*pRaiz)->direita == NULL))
        {
            //Se nao houver filhos...
            free(pAux);
            (*pRaiz) = NULL;
        }
        else
        {
            //Se so tem o filho da direita
            if ((*pRaiz)->esquerda == NULL)
            {
                (*pRaiz) = (*pRaiz)->direita;
                pAux->direita = NULL;
                free(pAux);
                pAux = NULL;
            }
            else
            {
                //Se so tem filho da esquerda
                if ((*pRaiz)->direita == NULL)
                {
                    (*pRaiz) = (*pRaiz)->esquerda;
                    pAux->esquerda = NULL;
                    free(pAux);
                    pAux = NULL;
                }
                else
                {
                    //Escolhi fazer o maior filho direito da subarvore esquerda.
                    //Se vc quiser usar o Menor da esquerda, so o que mudaria seria isso: pAux = MenorEsquerda(&(*pRaiz)->direita);
                    pAux = MaiorDireitaNaoBalanceada(&(*pRaiz)->esquerda);
                    pAux->esquerda = (*pRaiz)->esquerda;
                    pAux->direita = (*pRaiz)->direita;
                    (*pRaiz)->esquerda = (*pRaiz)->direita = NULL;
                    free((*pRaiz));
                    *pRaiz = pAux;
                    pAux = NULL;
                }
            }
        }
    }
}

number pesquisarArvoreNaoBalanceada(Dicionario **pRaiz, int numero)
{
    Dicionario *temp = *pRaiz;
    int parar = 0;

    if (*pRaiz == NULL)
    {
        return false;
    }
    else if (temp->esquerda == NULL && temp->direita == NULL)
    {
        if (temp->chave == numero)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (temp->chave == numero)
    {
        return true;
    }
    else
    {
        while (parar == 0)
        {
            if (temp->chave < numero)
            {
                if (temp->esquerda == NULL)
                {
                    parar++;
                    if (temp->chave == numero)
                    {
                        break;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    temp = temp->direita;
                    if (temp->chave == numero)
                    {
                        return true;
                        break;
                    }
                }
            }
            else if (temp->chave > numero)
            {
                if (temp->direita == NULL)
                {
                    parar++;
                    if (temp->chave == numero)
                    {
                        return true;
                        break;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    temp = temp->esquerda;
                    if (temp->chave == numero)
                    {
                        return true;
                        break;
                    }
                }
            }
        }
    }

    return false;
}

void exibirEmOrdemNaoBalanceada(Dicionario *pRaiz)
{
    if (pRaiz != NULL)
    {
        exibirEmOrdemNaoBalanceada(pRaiz->esquerda);
        printf("No: %i\n", pRaiz->chave);
        exibirEmOrdemNaoBalanceada(pRaiz->direita);
    }
}