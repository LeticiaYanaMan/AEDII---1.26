#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *proximo;
    struct No *anterior;
} No;

No* INIT(int val) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = val;
    novo->proximo = NULL;
    novo->anterior = NULL;
    return novo;
}

int ADD(No** cabeca, No** final, int val) {
    No* novo = INIT(val);
    //1
    if (*cabeca == NULL) { //lista vazia
        *cabeca = novo;
        *final = novo;
        return 0;
    }
    //2
    if (val <= (*cabeca)->valor) { //insere no inicio e vira nó inicial
        novo->proximo = *cabeca;
        (*cabeca)->anterior = novo;
        *cabeca = novo;
        return 0; //NEP = 0
    }
    //3
    if (val >= (*final)->valor) { //insere no fim e vira elemento final
        novo->anterior = *final;
        (*final)->proximo = novo;
        *final = novo;
        return 0; //NEP = 0
    }
    //4
    // distancias
    int d_cabeca = abs(val - (*cabeca)->valor);
    int d_final = abs(val - (*final)->valor);
    int cont = 0;
    //5
    if (d_cabeca <= d_final) { // se a menor distância for menor na frente - inicia a busca do nó inicial
        No* temp = *cabeca;
        cont = 1;

        while (temp->proximo != NULL && temp->proximo->valor < val) {
            temp = temp->proximo;
            cont++; //incrementa 1 ate encontrar o ponto de inserção
        }

        // adiciona o nó na lista depois de achar o ponto de inserção
        novo->proximo = temp->proximo;
        novo->anterior = temp;
        temp->proximo->anterior = novo;
        temp->proximo = novo;
    } 
    //6 
    else { // (d_cabeca > d_final) se a distância for menor no final - inicia  abusca do nó final
        No* temp = *final;
        cont = 1;

        while (temp->anterior != NULL && temp->anterior->valor > val) {
            temp = temp->anterior;
            cont++; //incrementa 1 ate encontrar o ponto de inserção
        }

        // adiciona o nó na lista depois de achar o ponto de inserção
        novo->anterior = temp->anterior;
        novo->proximo = temp;
        temp->anterior->proximo = novo;
        temp->anterior = novo;
    }

    return cont; //retorna o valor da saída
}

void PRINT(No** cabeca) {
    No* aux = *cabeca;
    while (aux != NULL) {
        printf("%d", aux->valor);
        if (aux->proximo != NULL) {
            printf(" ");
        }
        aux = aux->proximo;
    }
    printf("\n");
}

int main() {
    No* cabeca = NULL;
    No* final = NULL;
    int NEP = 0;
    int N;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int val;
        scanf("%d", &val);
        NEP += ADD(&cabeca, &final, val);
    }
    
    printf("%d\n", NEP);
    PRINT(&cabeca);

    return 0;
}
