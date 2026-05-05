#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char palavra[25];
    int pesos;
    int ordem;
} words;

void swap(words *A, int i, int j) {
    printf("ENTRANDO NO SWAP\n");
    printf(" i = %d / j = %d \n", i, j);
    printf("--------------------\n");
    words aux = A[i];
    A[i] = A[j];
    A[j] = aux;
    printf("-------------------- fim swap \n\n");
}

int max(words *A, words*B) { // define quem é maior no heap
    printf("ENTRANDO NO MAX\n");
    printf(" A = %s   B = %s \n", A->palavra , B->palavra);
    printf("--------------------\n");
    if (A->pesos > B->pesos) {
        printf("IF 1 \n");
        return 1;
    }
    if (A->pesos < B->pesos) {
        printf("IF 2 \n");
        return 0;
    }
    if (strcmp(A->palavra, B->palavra) > 0) {
        printf("IF 3 \n");
        return 1;
    }
    if (strcmp(A->palavra, B->palavra) < 0) {
        printf("IF 4\n");
        return 0;
    }
    if (A->ordem < B->ordem) {
        printf("IF 5\n");
        return 1;
    }

    printf("-------------------- fim max \n\n");
    return 0;
}

void HEAPIFY(words *A, int n, int i) { // garante maior elemento na posição 1
    // manutenção do heap
    printf("ENTRANDO NO HEAPIFY \n");
    printf(" n = %d / i = %d \n", n, i);
    printf("--------------------\n");
    int maior = i;
    int l = 2*i +1;
    int r = 2*i +2;
    printf(" i = %d / l = %d / r = %d \n", i, l, r);

    if (l < n && max(&A[l], &A[maior])) {
        maior = l;
        printf("maior = %d\n", maior);
    }
    if (r < n && max(&A[r], &A[maior])) {
        maior = r;
        printf("maior = %d\n", maior);
    }
    if (maior != i) {
        swap(A, i, maior);

        printf("Entrando no HEAPIFY de novo\n");
        HEAPIFY(A, n, maior);
    }
    printf("-------------------- fim HEAPIFY\n\n");
}

void BUILDHEAP(words *A, int M) { // constroi o heap maximo
    printf("ENTRANDO NO BUILDHEAP\n");
    printf(" M = %d \n", M);
    printf("--------------------\n");
    for (int i = (M/2)-1 ; i>=0; i--) {
        HEAPIFY(A, M, i);
    }
    printf("-------------------- fim BUILDHEAP\n\n");
}

void HEAPSORT(words *A, int M) {
    BUILDHEAP(A, M);

    printf("build_heap:");
    for (int i = 0; i < M; i++) {
        printf(" %s", A[i].palavra);
    }
    printf("\n"); // imprime o estado inicial do heap

    printf(" ao for: M-1 = %d \n", M-1);
    for (int i = M-1; i > 0; i--) {
        swap(A, 0, i); // move o maior para o final
        HEAPIFY(A, i, 0); // reconstroi heap
    }
    printf("-------------------- fim HEAPSORT \n\n");
}

void PRINT(words *A, int M) {
    printf("palavras:"); 
    for (int i = 0; i < M; i++) {
        printf(" %s", A[i].palavra);
    }
    printf("\n");
    printf("-------------------- fim PRINT \n\n");
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    words *inicio = (words*)malloc(N*sizeof(words));

    for (int i = 0; i < N; i++) {
        scanf("%s", inicio[i].palavra); 
        inicio[i].ordem = i;
    }

    printf("-------------------- comeco \n\n");

    //FASE DE CONTAGEM GLOBAL
    printf("Fase de Contagem Global\n");
    int freq[26];
    for (int i = 0; i < 26; i++) {
        freq[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        int len = strlen(inicio[i].palavra);
        printf("len = %d \n", len);
        for (int j = 0; j < len; j++) {
            freq[inicio[i].palavra[j] - 97]++; 
            printf("freq[inicio[%d].palavra[%d] - 97] = %d\n", i, j, freq[inicio[i].palavra[j] - 97]);
        }
    }

    printf("-------------------- Fase de Contagem Global\n");

    printf("Fase de Filtragem (K-densidade)\n");
    //FASE DE FILTRAGEM (K-Densidade)
    words *validas = (words*)malloc(N*sizeof(words));
    int M = 0;

    for (int i = 0; i < N; i++) {
        printf(" NO FOR : i = %d \n", i);
        int invalida = 0;
        int tam = strlen(inicio[i].palavra);

        for (int j = 0; j < tam; j++) {
            if(freq[inicio[i].palavra[j] -97] < K) {
                invalida++;
                printf("invalida +1\n");
            }
        }

        if (invalida > 0) {
            printf("A palavra %s eh invalida (K=%d)\n", inicio[i].palavra, K);
        }
        else {
            int pesos = 0;
            for (int k = 0; k < tam; k++) {
                pesos += freq[inicio[i].palavra[k] -97];
            }
            strcpy(validas[M].palavra, inicio[i].palavra);
            validas[M].pesos = pesos;
            printf("validas[%d].pesos = %d\n", M, validas[M].pesos);
            validas[M].ordem = inicio[i].ordem;
            printf("validas[%d].ordem = %d\n", validas[M].ordem);
            M++;
        }
    }
    printf("-------------------- fim da fase de filtragem (k-densidade)\n\n");

    printf("FASE DE ORDENACAOO (HEAPSORT)\n");
    // FASE DE ORDENAÇÃO (HEAPSORT)
    if (M==0) {
        printf("Erro: Sem palavras validas para ordenacao.\n");
    } else {
        printf("ENTRANDO NO HEAPSORT\n");
        printf("--------------------\n\n");
        HEAPSORT(validas, M);
        printf("ENTRANDO NO PRINT\n");
        printf("--------------------\n\n");
        PRINT(validas, M);
    }

    free(inicio);
    free(validas);
    printf("FIM DO CODIGO\n");
    printf("--------------------\n");

    return 0;
}
