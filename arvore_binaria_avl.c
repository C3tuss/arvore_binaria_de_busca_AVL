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

int main(){


    return 0;
}