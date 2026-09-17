#include "filas.h"

// inicializando a fila
void cria(Fila *q){
    q->inicio = NULL;
    q->fim = NULL;
    q->tamFila = 0;
}

// inserindo a pessoa na fila
int insere(Fila *q, Pessoa dado){

    No *novo = (No*) malloc(sizeof(No));

    if(novo == NULL) // vendo se tem erro de memoria
        return 0;

    novo->dado = dado; // copia dados da pessoa
    novo->prox = NULL;

    // se a fila esta vazia ou nao
    if(q->inicio == NULL){
        q->inicio = novo;
        q->fim = novo;
    } else {
        q->fim->prox = novo;
        q->fim = novo;
    }

    q->tamFila++;
    return 1;
}

// removendo a pessoa da fila
int retira(Fila *q, Pessoa *dado){

    if(q->inicio == NULL) // fila vazia
        return 0;

    No *aux = q->inicio;

    *dado = aux->dado; // copia a pessoa removida

    q->inicio = aux->prox;
    q->tamFila--;

    if(q->inicio == NULL) // fila ficando vazia
        q->fim = NULL;

    free(aux);

    return 1;
}

// verificando se a fila esta vazia
int vazia(Fila q){
    return (q.inicio == NULL);
}

// retornando o tamanho da fila
int pegaTamanho(Fila q){
    return q.tamFila;
}