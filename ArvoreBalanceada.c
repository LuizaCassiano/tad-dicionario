#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "Dicionario.h"
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))

void deletar(node *nodePtr, int valor)
{
    if (nodePtr == NULL)
    {
        printf("Numero nao existente na arvore");
        system("pause");
    }

    if (valor < nodePtr->chave)
    {
        deletar(nodePtr->esq, valor);
    }
    else if (valor > nodePtr->chave)
    {
        deletar(nodePtr->dir, valor);
    }
    else
    {
        //Se nao e menor nem maior, e o numero que estou procurando!
        node *nodeAux = nodePtr;

        if (nodePtr->esq == NULL && nodePtr->dir == NULL)
        {
            free(nodeAux);
            nodePtr = NULL;
        }
        else
        {
            //Se so tem o filho da direita
            if (nodePtr->esq == NULL)
            {
                nodePtr = nodePtr->dir;
                nodeAux->dir = NULL;
                free(nodeAux);
                nodeAux = NULL;
            }
            else
            {
                //Se so tem filho da esquerda
                if (nodePtr->dir == NULL)
                {
                    nodePtr = nodePtr->esq;
                    nodeAux->esq = NULL;
                    free(nodeAux);
                    nodeAux = NULL;
                }
            }
        }
    }
}

void liberarMemoriaImpl(node *nodePtr)
{
    if (nodePtr == NULL)
        return;

    liberarMemoriaImpl(nodePtr->esq);
    liberarMemoriaImpl(nodePtr->dir);

    free(nodePtr);
}

void liberarMemoria(tree *treePtr)
{
    liberarMemoriaImpl(treePtr->raiz);
}

tree *initTree()
{
    tree *tree = NULL;

    if ((tree = malloc(sizeof(tree))) == NULL)
    {
        return NULL;
    }

    tree->raiz = NULL;

    return tree;
}

node *initNode(int valor)
{
    node *nodePtr;
    nodePtr = malloc(sizeof(node));

    if (nodePtr == NULL)
    {
        puts("O programa ficou sem memoria!\n");
        system("pause");
    }

    nodePtr->esq = NULL;
    nodePtr->dir = NULL;
    nodePtr->chave = valor;

    return nodePtr;
}

int altura(const node *const nodePtr)
{
    int alturaEsq = 0;
    int alturaDir = 0;

    if (nodePtr->esq)
        alturaEsq = altura(nodePtr->esq);

    if (nodePtr->dir)
        alturaDir = altura(nodePtr->dir);

    return max(alturaDir, alturaEsq) + 1;
}

int fatorBal(const node *const nodePtr)
{
    int fator = 0;

    if (nodePtr->esq)
        fator += altura(nodePtr->esq);

    if (nodePtr->dir)
        fator -= altura(nodePtr->dir);

    return fator;
}

node *rotacionarEsqEsq(node *nodePtr)
{
    node *tempPtr = nodePtr;
    node *esqPtr = tempPtr->esq;

    tempPtr->esq = esqPtr->dir;
    esqPtr->dir = tempPtr;

    return esqPtr;
}

node *rotationarEsqDir(node *nodePtr)
{
    node *tempPtr = nodePtr;
    node *esqPtr = tempPtr->esq;
    node *dirPtr = esqPtr->dir;

    tempPtr->esq = dirPtr->dir;
    esqPtr->dir = dirPtr->esq;
    dirPtr->esq = esqPtr;
    dirPtr->dir = tempPtr;

    return dirPtr;
}

node *rotacionarDirEsq(node *nodePtr)
{
    node *tempPtr = nodePtr;
    node *dirPtr = tempPtr->dir;
    node *esqPtr = dirPtr->esq;

    tempPtr->dir = esqPtr->esq;
    dirPtr->esq = esqPtr->dir;
    esqPtr->dir = dirPtr;
    esqPtr->esq = tempPtr;

    return esqPtr;
}

node *rotacionarDirDir(node *nodePtr)
{
    node *tempPtr = nodePtr;
    node *dirPtr = tempPtr->dir;

    tempPtr->dir = dirPtr->esq;
    dirPtr->esq = tempPtr;

    return dirPtr;
}

node *balancearNode(node *const nodePtr)
{
    node *nodeBalanceado = NULL;

    if (nodePtr->esq)
        nodePtr->esq = balancearNode(nodePtr->esq);

    if (nodePtr->dir)
        nodePtr->dir = balancearNode(nodePtr->dir);

    int fator = fatorBal(nodePtr);

    if (fator >= 2)
    {
        /* pesando pra esquerda */
        if (fatorBal(nodePtr->esq) <= -1)
            nodeBalanceado = rotationarEsqDir(nodePtr);
        else
            nodeBalanceado = rotacionarEsqEsq(nodePtr);
    }
    else if (fator <= -2)
    {
        /* pesando pra direita */
        if (fatorBal(nodePtr->dir) >= 1)
            nodeBalanceado = rotacionarDirEsq(nodePtr);
        else
            nodeBalanceado = rotacionarDirDir(nodePtr);
    }
    else
    {
        nodeBalanceado = nodePtr;
    }

    return nodeBalanceado;
}

void balancearTree(tree *const treePtr)
{
    node *novaRaiz = NULL;

    novaRaiz = balancearNode(treePtr->raiz);

    if (novaRaiz != treePtr->raiz)
    {
        treePtr->raiz = novaRaiz;
    }
}

void inserir(tree *treePtr, int valor)
{
    node *novoNodePtr = NULL;
    node *nextPtr = NULL;
    node *lastPtr = NULL;

    if (treePtr->raiz == NULL)
    {
        novoNodePtr = initNode(valor);
        treePtr->raiz = novoNodePtr;
    }
    else
    {
        nextPtr = treePtr->raiz;

        while (nextPtr != NULL)
        {
            lastPtr = nextPtr;

            if (valor < nextPtr->chave)
            {
                nextPtr = nextPtr->esq;
            }
            else if (valor > nextPtr->chave)
            {
                nextPtr = nextPtr->dir;
            }
            else if (valor == nextPtr->chave)
            {
                return;
            }
        }

        novoNodePtr = initNode(valor);

        if (valor < lastPtr->chave)
            lastPtr->esq = novoNodePtr;

        if (valor > lastPtr->chave)
            lastPtr->dir = novoNodePtr;
    }

    balancearTree(treePtr);
}

node *encontrarValor(const tree *const tree, int valor)
{
    node *atual = tree->raiz;

    while (atual && atual->chave != valor)
    {
        if (valor > atual->chave)
            atual = atual->dir;
        else
            atual = atual->esq;
    }

    return atual;
}

void listar(node *nodePtr)
{
    if (nodePtr != NULL)
    {
        printf("No: %d, Altura: %d, Fator de Balanceamento: %d\n", nodePtr->chave, altura(nodePtr), fatorBal(nodePtr));
        listar(nodePtr->esq);
        listar(nodePtr->dir);
    }
}