#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int valor;
    struct no *esquerda, *direita;
    short altura;

}No;

/*Função que cria um novo nó
  x -> valor a ser inserido no nó
  Retorna: o endereço do nó criado
*/

No* novoNo(int x){
    No *novo = calloc(1, sizeof(No));

    if(novo){
        novo->valor = x;
        novo-> esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    }else
        printf("\nERRO ao alocar nó em novoNo!\n");
    
    return novo;
}

/*Retorna o maior dentre dois valores
  a, b -> altura de dois nós da árvore*/

short maior(short a, short b){
    return (a > b)? a: b;
}

/*Retorna a altura de um nó ou -1 caso ele seja null*/

short alturaDoNo(No *no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

/*Calcua e retorna o fator de balanceamento de um nó*/

short fatorDeBalanceamento(No *no){
    if(no)
        return (alturaDoNo(no->esquerda)) - (alturaDoNo(no->direita));
    else
        return 0;
}

// função pra a rotação a esquerda

No* rotacaoEsquerda(No* r){
    No *y, *f;

    y = r->direita;
    f = y->esquerda;

    y->esquerda = r;
    r->direita = f;

    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;
}

// função para a rotação a direita

No* rotacaoDireita(No* r){
    No *y, *f;

    y = r->esquerda;
    f = y->direita;

    y->direita = r;
    r->esquerda = f;
    
    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y;
}

// função rotação direita-esquerda

No* rotacaoDireitaEsquerda(No* r){
    r->direita = rotacaoDireita(r->direita);
    return rotacaoEsquerda(r);
}

// função rotação esquerda-direita

No* rotacaoEsquerdaDireita(No* r){
    r->esquerda = rotacaoEsquerda(r->esquerda);
    return rotacaoDireita(r);
}

int main(){


    return 0;
}