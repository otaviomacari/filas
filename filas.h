#ifndef FILAS_H
#define FILAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct para pessoa (tipo de dado da fila)
typedef struct {
    char nome[50];
    char cpf[20];
    int senha;
} Pessoa;

// no da fila
typedef struct no {
    Pessoa dado;
    struct no *prox;
} No;

// estrutura da fila
typedef struct {
    No *inicio;
    No *fim;
    int tamFila;
} Fila;

// funcoes da fila 
void cria(Fila *q);
int insere(Fila *q, Pessoa dado);
int retira(Fila *q, Pessoa *dado);
int vazia(Fila q);
int pegaTamanho(Fila q);

#endif