#pragma once

//ÁRVORE BINÁRIA BALANCEADA - AVL
struct nodeStruct
{
    struct nodeStruct *esq;
    struct nodeStruct *dir;
    int chave;
};

typedef struct nodeStruct node;

struct treeStruct
{
    struct nodeStruct *raiz;
};

typedef struct treeStruct tree;

void deletar(node *nodePtr, int valor);
void liberarMemoriaImpl(node *nodePtr);
void liberarMemoria(tree *treePtr);
tree *initTree();
node *initNode(int valor);
int altura(const node *const nodePtr);
int fatorBal(const node *const nodePtr);
node *rotacionarEsqEsq(node *nodePtr);
node *rotationarEsqDir(node *nodePtr);
node *rotacionarDirEsq(node *nodePtr);
node *rotacionarDirDir(node *nodePtr);
node *balancearNode(node *const nodePtr);
void balancearTree(tree *const treePtr);
void inserir(tree *treePtr, int valor);
node *encontrarValor(const tree *const tree, int valor);
void avlTraverseNodeDfs(node *node, int depth);
void avlTraverseDfs(tree *tree);

//ÁRVORE BINÁRIA NÃO BALANCEADA
struct No {
    int chave;
    int alt;
    struct No *esquerda;
    struct No *direita;
};

typedef struct No Dicionario;

typedef int number;

void inicializarArvoreNaoBalanceada(Dicionario **pRaiz);
void inserirArvoreNaoBalanceada(Dicionario **pRaiz, int numero);
Dicionario *MaiorDireitaNaoBalanceada(Dicionario **no);
Dicionario *MenorEsquerdaNaoBalanceada(Dicionario **no);
void removerArvoreNaoBalanceada(Dicionario **pRaiz, int numero);
number pesquisarArvoreNaoBalanceada(Dicionario **pRaiz, int numero);
void exibirEmOrdemNaoBalanceada(Dicionario *pRaiz);

//HASH COM SOLUÇÃO DE COLISÃO POR ENDEREÇAMENTO ABERTO 
struct dic {
    int chave;
};

typedef struct hash Hash;

Hash* criaHash(int tableSize);
void liberaHash(Hash* ha);
int chaveDivisao(int chave, int tableSize);
int sondagemLinear(int pos, int i, int tableSize);
int inserirHash(Hash* ha, struct dic dic);
int buscaHash(Hash* ha, int chave, struct dic* dic);
void listarHash(Hash* ha);
void removendoHash(Hash* ha, int chave);

//HASH COM SOLUÇÃO DE COLISÃO POR LISTA LINEAR 
typedef struct {
    int chave;
} Dict;

void inicializarTabelaHashLinear();
int gerarCodigoHash(int chave);
void inserirTabelaHashLinear(Dict dict);
Dict* buscarTabelaHashLinear(int chave);
void imprimir();
void removendoHashLinear(int chave);