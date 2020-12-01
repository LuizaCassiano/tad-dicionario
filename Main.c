#include <C:\TAD\ArvoreNaoBalanceada.c>
#include <C:\TAD\ArvoreBalanceada.c>
#include <C:\TAD\HashEnderecamentoAberto.c>
#include <C:\TAD\HashListaLinear.c>

void testesHashListaLinear()
{
    //Inicializando
    inicializarTabelaHashLinear();

    //Inserindo
    Dict dict;

    dict.chave = 17;
    inserirTabelaHashLinear(dict);

    dict.chave = 7;
    inserirTabelaHashLinear(dict);

    dict.chave = 5;
    inserirTabelaHashLinear(dict);

    dict.chave = 13;
    inserirTabelaHashLinear(dict);

    dict.chave = 18;
    inserirTabelaHashLinear(dict);

    dict.chave = 2;
    inserirTabelaHashLinear(dict);

    //Exibindo antes de remover
    printf("------------------ LISTANDO ANTES DE REMOVER ------------------\n");
    imprimir();

    //Removendo
    printf("\n------------------ REMOVENDO ------------------\n");
    removendoHashLinear(7);

    //Exibindo depois de remover
    printf("\n------------------ LISTANDO DEPOIS DE REMOVER ------------------\n");
    imprimir();

    //Buscando e encontrando
    printf("\n------------------ BUSCANDO NA TABELA HASH ------------------\n");
    Dict *dictionary;

    dictionary = buscarTabelaHashLinear(2);

    if (dictionary == 0)
        printf("Numero nao encontrado!\n");
    else
        printf("Numero encontrado!\n");

    //Buscando e nao encontrando
    dictionary = buscarTabelaHashLinear(3);

    if (dictionary == 0)
        printf("Numero nao encontrado!\n");
    else
        printf("Numero encontrado!\n");    
}

void testesHashEnderecamentoAberto()
{
    //Inicializando
    Hash *ha = criaHash(17);

    //Inserindo
    struct dic dic;

    dic.chave = 34;
    inserirHash(ha, dic);

    dic.chave = 30;
    inserirHash(ha, dic);

    dic.chave = 12;
    inserirHash(ha, dic);

    dic.chave = 55;
    inserirHash(ha, dic);

    dic.chave = 23;
    inserirHash(ha, dic);

    //Listando antes de remover
    printf("------------------ LISTANDO ANTES DE REMOVER ------------------\n");
    listarHash(ha);

    //Removendo
    printf("\n------------------ REMOVENDO ------------------\n");
    removendoHash(ha, 55);

    //Buscando e não encontrando
    printf("\n------------------ BUSCANDO NA TABELA HASH ------------------\n");

    int y = buscaHash(ha, 3, *ha->itens);

    if (y == 1)
        printf("Numero encontrado!\n");
    else
        printf("Numero nao encontrado!\n");

    //Buscando e encontrando
    int w = buscaHash(ha, 23, *ha->itens);

    if (w == 1)
        printf("Numero encontrado!\n");
    else
        printf("Numero nao encontrado!\n");

    //Liberando tabela
    printf("\n------------------ LIBERANDO TABELA HASH ------------------\n");
    liberaHash(ha);
}

void testesArvoreBalanceada()
{
    //Inicializando
    tree *treePtr = initTree();
    node *nodePtr;
    node *searchNodePtr;

    //Inserindo nós
    inserir(treePtr, 34);
    inserir(treePtr, 50);
    inserir(treePtr, 13);
    inserir(treePtr, 56);
    inserir(treePtr, 28);

    //Exibindo árvore antes de remover o nó
    printf("------------------ LISTANDO NOS ANTES DE REMOVER ------------------\n");
    listar(treePtr->raiz);

    //Buscando e removendo nó
    printf("\n------------------ REMOVENDO NO ------------------\n");
    searchNodePtr = encontrarValor(treePtr, 34);
    deletar(searchNodePtr, 34);

    //Buscando e encontrando
    printf("\n------------------ BUSCANDO NOS NA ARVORE ------------------\n");
    nodePtr = encontrarValor(treePtr, 50);

    if (nodePtr != NULL)
        printf("Numero encontrado!\n");
    else
        printf("Numero nao encontrado!\n");

    //Buscando e não encontrando
    nodePtr = encontrarValor(treePtr, 40);

    if (nodePtr != NULL)
        printf("Numero encontrado!\n");
    else
        printf("Numero nao encontrado!\n");
}

void testesArvoreNaoBalanceada()
{
    Dicionario *dicionario;

    //Inicializando
    inicializarArvoreNaoBalanceada(&dicionario);

    //Inserindo nós
    inserirArvoreNaoBalanceada(&dicionario, 400);
    inserirArvoreNaoBalanceada(&dicionario, 2);
    inserirArvoreNaoBalanceada(&dicionario, 500);
    inserirArvoreNaoBalanceada(&dicionario, 4);
    inserirArvoreNaoBalanceada(&dicionario, 200);

    //Exibindo árvore antes de remover o nó
    printf("------------------ LISTANDO NOS ANTES DE REMOVER ------------------\n");
    exibirEmOrdemNaoBalanceada(dicionario);

    //Removendo nó
    printf("\n------------------ REMOVENDO NO ------------------\n");
    removerArvoreNaoBalanceada(&dicionario, 4);

    //Exibindo árvore depois de remover o nó
    printf("\n------------------ LISTANDO NOS DEPOIS DE REMOVER ------------------\n");
    exibirEmOrdemNaoBalanceada(dicionario);

    //Buscando e encontrando
    printf("\n------------------ BUSCANDO NOS NA ARVORE ------------------\n");
    int achou = pesquisarArvoreNaoBalanceada(&dicionario, 500);

    if (achou == 1)
        printf("Numero encontrado!\n");
    else
        printf("Numero nao encontrado!\n");

    //Buscando e não encontrando
    achou = pesquisarArvoreNaoBalanceada(&dicionario, 5000);

    if (achou == 1)
        printf("Numero encontrado!\n");
    else
        printf("Numero nao encontrado!\n");
}

int main()
{
    printf("\nARVORE NAO BALANCEADA!\n");
    testesArvoreNaoBalanceada();

    printf("\nARVORE BALANCEADA!\n");
    testesArvoreBalanceada();

    printf("\nHASH LISTA LINEAR!\n");
    testesHashListaLinear();
    
    printf("\nHASH ENDERECAMENTO ABERTO!\n");
    testesHashEnderecamentoAberto();
}