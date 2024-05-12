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

/*
Insere um novo nó na árvore
raiz -> raiz da árvore
x -> valor a ser inserido
retorna: endereço do novo nó ou nova raiz após o balanceamento
*/
No* inserir(No* raiz, int x){
    if(raiz == NULL) // árvore vazia
        return novoNo(x);
    else{ // inserção será à esquerda ou à direita
        if(x < raiz->valor)
            raiz->esquerda = inserir(raiz->esquerda, x);
        else if(x > raiz->direita)
            raiz->direita = inserir(raiz->direita, x);
        else
            printf("\nInserção não realizada!\nO elemento %d já existe!\n", x);
    }

    //Recalcular a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;

    //verifica a necessidade rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

/*Função para realizar o balanceamento da árvore aṕos uma inserção ou remoção
Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento*/

No* balancear(No* raiz){
    short fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direita) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita
    if(fb > 1 && fatorDeBalanceamento(raiz->esquerda) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação esquerda-direita
    if(fb > 1 && fatorDeBalanceamento(raiz->esquerda) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação direita-esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direita) > 0)
        raiz = rotacaoDireitaEsquerda(raiz->direita);
    
    return raiz;
}

No* remover(No* raiz, int chave){
    if(raiz == NULL){
        printf("Valor não encontrado!\n");
        return NULL;
    }else{ // Procura o nó a remover
        if(raiz->valor == chave){
            // remove nós folhas (nós sem filhos)
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                printf("Elemento folha removido: %d!\n", chave);

            }else{
                if(raiz->esquerda != NULL && raiz->direita != NULL){
                    No* aux = raiz->esquerda;
                    while(aux->direita != NULL)
                        aux = aux->direita;

                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    printf("Elmento trocado: %d!\n", chave);
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                }else{
                    //remover nós que possuem apenas 1 filho
                    No* aux;
                    if(raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d!\n", chave);
                    return aux;
                }
            }
        }else{
            if(chave < raiz->esquerda)
                remover(raiz->esquerda, chave);
            else
                remover(raiz->direita, chave);
        }
        // Recalculae a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;

        //verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);
        
        return raiz;
    }
}

int main(){


    return 0;
}