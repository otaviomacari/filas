#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "filas.h"
#include "lista_pessoas.h"

int main(){

    Fila fila; // cria fila
    Pessoa p; // variável auxiliar
    int indice;

    srand(time(NULL)); // inicializa aleatoriedade

    cria(&fila); // inicializa fila

    // inserindo 20 pessoas aleatorias
    for(int i = 0; i < 20; i++){

        indice = rand() % 50; // indice entre 0 e 49

        p = lista_pessoas[indice]; // pega pessoa da lista

        insere(&fila, p); // insere na fila
    }

    // removendo e imprimindo 20 pessoas
    for(int i = 0; i < 20; i++){

        if(retira(&fila, &p)){
            printf("%s\n", p.nome);
        }
    }

    // verificando se a fila esta vazia
    if(vazia(fila)){
        printf("\nFila vazia!\n");
    } else {
        printf("\nFila nao esta vazia!\n");
    }

    return 0;
}