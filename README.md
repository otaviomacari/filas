# Fila de Pessoas em C

Projeto desenvolvido em **linguagem C** para implementar e demonstrar o funcionamento de uma **Fila (Queue)** utilizando **lista encadeada** e **alocação dinâmica de memória**.

O programa possui uma lista pré-definida de pessoas, seleciona aleatoriamente 20 delas e as insere em uma fila. Em seguida, as pessoas são removidas e exibidas na mesma ordem em que foram inseridas, demonstrando na prática o princípio **FIFO — First In, First Out**.

---

## Objetivo

O principal objetivo do projeto é praticar conceitos de **Estruturas de Dados em C**, especialmente:

* Filas;
* Listas encadeadas;
* Estruturas (`struct`);
* Ponteiros;
* Alocação dinâmica de memória;
* `malloc()` e `free()`;
* Manipulação de estruturas;
* Geração de números aleatórios;
* Modularização de código através de arquivos `.c` e `.h`.

---

## Estrutura do Projeto

O projeto é dividido nos seguintes arquivos:

```text
.
├── filas.c
├── filas.h
├── lista_pessoas.h
└── main.c
```

Cada arquivo possui uma responsabilidade específica.

---

# Conceito de Fila

Uma fila é uma estrutura de dados que segue o princípio:

> **FIFO — First In, First Out**

Ou seja:

> **O primeiro elemento que entra é o primeiro elemento que sai.**

Um exemplo do funcionamento de uma fila no projeto:

```text
ENTRADA                              SAÍDA

Pessoa A ──┐
Pessoa B ──┤
Pessoa C ──┤
Pessoa D ──┘

  ↓

┌─────────┬─────────┬─────────┬─────────┐
│ Pessoa A│ Pessoa B│ Pessoa C│ Pessoa D│
└─────────┴─────────┴─────────┴─────────┘
     ↑                                  ↑
   INÍCIO                               FIM
```

Quando a remoção acontece, `Pessoa A` é retirada primeiro, seguida por `Pessoa B`, `Pessoa C` e `Pessoa D`.

---

# `filas.h`

O arquivo `filas.h` contém as estruturas utilizadas pela fila e os protótipos das funções.

## Estrutura `Pessoa`

```c
typedef struct {
    char nome[50];
    char cpf[20];
    int senha;
} Pessoa;
```

A estrutura `Pessoa` representa uma pessoa que será armazenada na fila.

Ela possui três informações:

* `nome` → nome da pessoa;
* `cpf` → CPF da pessoa;
* `senha` → senha numérica associada à pessoa.

---

## Estrutura `No`

```c
typedef struct no {
    Pessoa dado;
    struct no *prox;
} No;
```

Cada elemento da fila é armazenado em um **nó**.

O nó possui:

* `dado` → armazena uma estrutura `Pessoa`;
* `prox` → ponteiro para o próximo nó da fila.

Visualmente:

```text
┌─────────────────────┐
│ Pessoa              │
│ nome                │
│ cpf                 │
│ senha               │
├─────────────────────┤
│ prox ───────────────┼───► próximo nó
└─────────────────────┘
```

---

## Estrutura `Fila`

```c
typedef struct {
    No *inicio;
    No *fim;
    int tamFila;
} Fila;
```

A estrutura `Fila` possui três informações:

### `inicio`

Aponta para o primeiro elemento da fila.

É de onde os elementos são removidos.

### `fim`

Aponta para o último elemento da fila.

É onde novos elementos são inseridos.

### `tamFila`

Armazena a quantidade atual de elementos presentes na fila.

---

# `filas.c`

O arquivo `filas.c` contém a implementação das operações da fila.

---

## `cria()`

```c
void cria(Fila *q){
    q->inicio = NULL;
    q->fim = NULL;
    q->tamFila = 0;
}
```

Inicializa a fila.

No início:

```text
inicio → NULL
fim    → NULL
tamanho = 0
```

Isso significa que a fila está vazia.

---

# `insere()`

```c
int insere(Fila *q, Pessoa dado)
```

Essa função adiciona uma pessoa ao **final da fila**.

Primeiro é criado um novo nó utilizando alocação dinâmica:

```c
No *novo = (No*) malloc(sizeof(No));
```

Caso não seja possível alocar memória:

```c
if(novo == NULL)
    return 0;
```

A função retorna `0`, indicando que a inserção não foi realizada.

Caso a alocação seja bem-sucedida:

```c
novo->dado = dado;
novo->prox = NULL;
```

O novo nó recebe os dados da pessoa e, inicialmente, aponta para `NULL`, pois será o último elemento da fila.

---

## Inserção em uma fila vazia

Quando:

```c
q->inicio == NULL
```

significa que a fila está vazia.

Nesse caso:

```c
q->inicio = novo;
q->fim = novo;
```

O novo elemento passa a ser simultaneamente o início e o fim da fila.

```text
inicio
  ↓
┌─────────┐
│ Pessoa A│
└─────────┘
  ↑
 fim
```

---

## Inserção em uma fila que já possui elementos

Caso a fila não esteja vazia:

```c
q->fim->prox = novo;
q->fim = novo;
```

O antigo último elemento passa a apontar para o novo elemento, e `fim` é atualizado.

Exemplo:

```text
Antes:

inicio                         fim
  ↓                             ↓
[A] ─────────► [B] ─────────► NULL
```

Inserindo `C`:

```text
inicio                                  fim
  ↓                                      ↓
[A] ─────────► [B] ─────────► [C] ───► NULL
```

Por fim:

```c
q->tamFila++;
```

incrementa o tamanho da fila.

A função retorna `1`, indicando que a inserção foi realizada com sucesso.

---

# `retira()`

```c
int retira(Fila *q, Pessoa *dado)
```

Essa função remove a pessoa que está no **início da fila**.

Primeiro é verificado se a fila está vazia:

```c
if(q->inicio == NULL)
    return 0;
```

Se estiver vazia, não existe nenhuma pessoa para remover.

---

## Removendo o primeiro elemento

Um ponteiro auxiliar recebe o endereço do primeiro nó:

```c
No *aux = q->inicio;
```

Os dados da pessoa são copiados para a variável fornecida:

```c
*dado = aux->dado;
```

Depois, o início da fila passa para o próximo elemento:

```c
q->inicio = aux->prox;
```

O tamanho é decrementado:

```c
q->tamFila--;
```

Caso a fila tenha ficado vazia após a remoção:

```c
if(q->inicio == NULL)
    q->fim = NULL;
```

O `fim` também precisa voltar para `NULL`.

Finalmente, a memória do nó removido é liberada:

```c
free(aux);
```

A função retorna `1`, indicando que a remoção ocorreu com sucesso.

---

# `vazia()`

```c
int vazia(Fila q){
    return (q.inicio == NULL);
}
```

Verifica se a fila está vazia.

Retorna:

* `1` → fila vazia;
* `0` → fila possui elementos.

---

# `pegaTamanho()`

```c
int pegaTamanho(Fila q){
    return q.tamFila;
}
```

Retorna a quantidade de pessoas atualmente presentes na fila.

Por exemplo, se a fila possui:

```text
[A] → [B] → [C]
```

o resultado será:

```text
3
```

---

# `lista_pessoas.h`

O arquivo `lista_pessoas.h` contém um vetor com **50 pessoas pré-cadastradas**.

Exemplo:

```c
Pessoa lista_pessoas[50] = {

    {"Alice", "123.456.789-00", 1234},
    {"Bob", "987.654.321-00", 2345},
    {"Charlie", "456.789.123-00", 3456},

    ...
};
```

Cada posição do vetor contém:

```text
Nome
CPF
Senha
```

O vetor é utilizado pelo `main.c` como fonte de dados para preencher a fila.

---

# `main.c`

O arquivo `main.c` contém a execução principal do programa.

Primeiramente são declaradas:

```c
Fila fila;
Pessoa p;
int indice;
```

Onde:

* `fila` → representa a fila;
* `p` → variável auxiliar utilizada para armazenar uma pessoa;
* `indice` → armazena um índice aleatório do vetor de pessoas.

---

## Geração de números aleatórios

O programa utiliza:

```c
srand(time(NULL));
```

para inicializar o gerador de números aleatórios utilizando o horário atual como semente.

Depois:

```c
indice = rand() % 50;
```

gera um número entre:

```text
0 e 49
```

Esse número é utilizado para selecionar uma pessoa do vetor:

```c
p = lista_pessoas[indice];
```

---

# Inserção das pessoas

O programa executa:

```c
for(int i = 0; i < 20; i++){
```

Assim, são realizadas **20 inserções**.

Em cada repetição:

1. É gerado um índice aleatório;
2. Uma pessoa é selecionada do vetor;
3. A pessoa é inserida na fila.

```c
indice = rand() % 50;

p = lista_pessoas[indice];

insere(&fila, p);
```

É importante observar que como o índice é escolhido aleatoriamente, **a mesma pessoa pode ser selecionada mais de uma vez**.

---

# Remoção das pessoas

Depois das inserções, o programa executa:

```c
for(int i = 0; i < 20; i++){

    if(retira(&fila, &p)){
        printf("%s\n", p.nome);
    }
}
```

São realizadas até 20 remoções.

A função `retira()` sempre remove a pessoa que está no início da fila.

Por isso, as pessoas são exibidas na ordem em que foram inseridas.

### Exemplo

Suponha que as pessoas tenham sido inseridas nesta ordem:

```text
Alice
Carlos
Maria
João
Pedro
```

A fila será:

```text
INÍCIO                              FIM
  ↓                                  ↓
Alice → Carlos → Maria → João → Pedro
```

As remoções acontecerão assim:

```text
1º → Alice
2º → Carlos
3º → Maria
4º → João
5º → Pedro
```

Isso demonstra o funcionamento do princípio **FIFO**.

---

# Verificação da fila

Após as 20 remoções, o programa verifica:

```c
if(vazia(fila)){
    printf("\nFila vazia!\n");
} else {
    printf("\nFila nao esta vazia!\n");
}
```

Como foram inseridas 20 pessoas e o programa tenta remover 20 pessoas, normalmente a fila estará vazia ao final.

A saída será:

```text
Fila vazia!
```

---

# Fluxo do programa

O funcionamento geral pode ser representado da seguinte forma:

```text
              INÍCIO
                 │
                 ▼
          Cria a fila vazia
                 │
                 ▼
       Gera uma pessoa aleatória
                 │
                 ▼
          Insere na fila
                 │
                 ▼
       Repetir até 20 pessoas
                 │
                 ▼
       Remove pessoa do início
                 │
                 ▼
          Exibe o nome
                 │
                 ▼
       Repetir até 20 remoções
                 │
                 ▼
       Verifica se está vazia
                 │
                 ▼
                FIM
```

---

# Representação da estrutura

A fila utiliza dois ponteiros principais:

```text
                   FILA

              inicio             fim
                ↓                  ↓
           ┌────────┐        ┌────────┐
           │ Pessoa │        │ Pessoa │
           │   A    │───────►│   C    │
           └────────┘        └────────┘
                │                  │
                ▼                  ▼
           próximo nó             NULL
```

O `inicio` é utilizado para **remoção**.

O `fim` é utilizado para **inserção**.

Essa organização permite realizar as operações de inserção e remoção sem precisar percorrer toda a fila.

---

# Complexidade

Como a fila mantém ponteiros para o início e para o fim:

### Inserção — `insere()`

A inserção acontece diretamente no final:

```text
O(1)
```

### Remoção — `retira()`

A remoção acontece diretamente no início:

```text
O(1)
```

### Verificação de fila vazia — `vazia()`

```text
O(1)
```

### Consulta do tamanho — `pegaTamanho()`

Como o tamanho é armazenado em `tamFila`:

```text
O(1)
```

---

# Gerenciamento de memória

A fila utiliza **alocação dinâmica** para criar seus nós:

```c
malloc(sizeof(No));
```

Quando um elemento é removido, sua memória é liberada:

```c
free(aux);
```

Esse gerenciamento é importante porque evita que os nós removidos continuem ocupando memória desnecessariamente.

---

# Exemplo de execução

Uma possível execução do programa:

```text
Alice
Xander
Bob
Tina
Grace
Pedro
Vera
Charlie
Mia
Frank
...
```

A ordem varia a cada execução porque as pessoas são escolhidas utilizando números aleatórios.

Ao final:

```text
Fila vazia!
```

---

# Conceitos praticados

Este projeto trabalha principalmente os seguintes conceitos:

* **Fila (Queue);**
* **FIFO — First In, First Out;**
* **Lista encadeada;**
* **Nós;**
* **Ponteiros;**
* **Structs;**
* **Alocação dinâmica;**
* **`malloc()`;**
* **`free()`;**
* **Vetores de estruturas;**
* **Números aleatórios com `rand()`;**
* **Modularização utilizando arquivos `.c` e `.h`;**
* **Manipulação de dados estruturados.**

---

# Compilação

Utilizando o GCC, compile os arquivos:

```bash
gcc main.c filas.c -o fila
```

Depois execute:

### Windows

```bash
fila.exe
```

### Linux/macOS

```bash
./fila
```

---

# Conclusão

O projeto apresenta uma implementação prática de uma **fila dinâmica em C utilizando lista encadeada**.

A estrutura mantém dois ponteiros, `inicio` e `fim`, permitindo que elementos sejam inseridos no final e removidos no início de maneira eficiente.

Através do cadastro de pessoas e da seleção aleatória de 20 registros, o programa demonstra o comportamento **FIFO (First In, First Out)**, um dos conceitos fundamentais de estruturas de dados.

Além da implementação da fila, o projeto também permite praticar **ponteiros, structs, alocação dinâmica de memória, modularização e manipulação de dados em C**.
