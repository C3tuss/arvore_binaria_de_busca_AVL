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

    return y;
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
        else if(x > raiz->valor)
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



No* remover(No* raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor não encontrado!\n");
        return NULL;
    }

    if (chave < raiz->valor)
        raiz->esquerda = remover(raiz->esquerda, chave);
    else if (chave > raiz->valor)
        raiz->direita = remover(raiz->direita, chave);
    else {
        if (raiz->esquerda == NULL || raiz->direita == NULL) {
            No* aux = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if (aux == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d!\n", chave);
                return NULL;
            } else {
                *raiz = *aux;
                free(aux);
                printf("Elemento com 1 filho removido: %d!\n", chave);
                return raiz;
            }
        } else {
            No* aux = raiz->esquerda;
            while (aux->direita != NULL)
                aux = aux->direita;

            raiz->valor = aux->valor;
            raiz->esquerda = remover(raiz->esquerda, aux->valor);
        }
    }

    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;

    raiz = balancear(raiz);

    return raiz;
}

void imprimir(No* raiz,int nivel){
    int i;
    if(raiz){
        imprimir(raiz->direita, nivel + 1);
        printf("\n\n");

        for(i = 0; i < nivel; i++)
            printf("\t");

        printf("%d", raiz->valor);
        imprimir(raiz->esquerda, nivel + 1);
    }
}

int main(){

    int opcao, valor;
    No* raiz = NULL;

    do{
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            printf("Saindo!!!");
            break;
        case 1:
            printf("\tDigite o valor a ser inserido: ");
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
            break;
        case 2:
            printf("\tDigite o valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        case 3:
            imprimir(raiz, 1);
            break;
        default:
            printf("\nOpção invalida!!!\n");
        }

    }while(opcao != 0);

    return 0;
}