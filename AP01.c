#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No* front;
    struct No* back;
} No;

No* init(No* cabeca, int N) {
    for (int i = 0; i < N; i++) {
        No* novo = malloc(sizeof(No));
        novo = NULL;
        novo->front = cabeca->back;
        cabeca->back = novo->front;
        novo->back = cabeca->front;
        cabeca->front = novo->back;
    }
    return cabeca;
}

void ADD(No* cabeca, int new) {
    if (cabeca == NULL) 
        cabeca->valor = new;
    else {
        if (new < cabeca->valor) {
            cabeca->back->valor = cabeca->valor;
            cabeca->valor = new;
        }
        else {
            if (cabeca->front->valor < cabeca->valor) return;
            else ADD(cabeca->front, new);
        }
    }
}

void PRINT(No* cabeca){
    printf("%d ", cabeca->valor);
    if (cabeca->front->valor < cabeca->valor)
        return;
    else 
        PRINT(cabeca->front);
}

int main() {
    int N, new;
    int cont = 0;
    No* cabeca = NULL;
    scanf("%d", &N);
    cabeca = init(cabeca, N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &new);
        ADD(cabeca, new);
    }
    PRINT(cabeca);
    printf("\n");
    printf("%d", cont);

    return 0;
}
