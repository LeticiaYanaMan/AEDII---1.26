#include <stdio.h>
#include <stdlib.h>
 
//definimos a variavel que vai contabilizar as quedas
long long int quedas = 0; 
 
void merge(int *vet, int comeco, int meio, int fim) {
    // separa em dois tamanhos: um que contabiliza do começo ao meio, e outro do meio ao fim
    int tamcom = meio - comeco + 1;
    int tamfim = fim - meio;
 
    // cria vetores desses tamanhos que comportam dados de tamanho int
    int *L = (int *)malloc(tamcom * sizeof(int));
    int *R = (int *)malloc(tamfim * sizeof(int));
 
    // preenche os vetores com os números devidos do vetor principal
    for (int i = 0; i < tamcom; i++) 
        L[i] = vet[comeco + i];
    for (int i = 0; i < tamfim; i++) 
        R[i] = vet[meio + 1 + i];
 
    //criamos uma variavel auxiliar aux
    int aux = 0;
    for (int i = 0; i < tamfim; i++) {
        while (aux < tamcom && L[aux] <= 2 * R[i]) //garantindo que o valor de aux será menor que a primeira metade e 
        // que o primeiro vetor tem valor menor ou igual a 2 vezes o valor no segundo vetor 
            aux++; // a variavel auxiliar vai somar 1 só se cumprir o fator que categoriza a queda
        quedas += (tamcom - aux); // as quedas vaõ se aumentando conforme o tamanho da primeira metade - da variavel auxiliar
    }
 
    int i = 0, j = 0, idx = comeco; //variaveis auxiliares
    while (i < tamcom && j < tamfim) { 
        if (L[i] <= R[j]) 
            vet[idx++] = L[i++]; // se houver essa necessidade de troca, faz a troca que,
        // no final, vai dar no vetor principal ordenado
        else vet[idx++] = R[j++];
    }
    // agora vai substituir os valores no vetor principal, com os que precisavam já organizados
    while (i < tamcom) 
        vet[idx++] = L[i++];
    while (j < tamfim) 
        vet[idx++] = R[j++];
 
    // libera os vetores auxiliares que criamos
    free(L);
    free(R);
}
 
void mergesort(int *vet, int comeco, int fim) {
    if (comeco < fim) {
        // vai dividindo o vetor de dois em dois até só ter 1 número armazenado em cada (comeco não vai ser < que fim)
        int meio = comeco + (fim - comeco) / 2;
        mergesort(vet, comeco, meio);
        mergesort(vet, meio + 1, fim);
        // chama a função merge, que vai organizar cada vetor dividido
        merge(vet, comeco, meio, fim);
    }
}
 
int main(void) {
    int N;
    scanf("%d", &N); // número de dias
    // cria um vetor desse tamanho
    int *v = (int *)malloc(N * sizeof(int));
    // vai ler essa quantidade N de números e armazena-los no vetor criado
    for (int i = 0; i < N; i++) 
        scanf("%d", &v[i]);
    // vetor começa em 0 e termina em N-1
    mergesort(v, 0, N - 1);
 
    printf("%lld\n", quedas);
    // imprime o vetor
    for (int i = 0; i < N; i++) 
        printf("%d ", v[i]);
    printf("\n");
 
    free(v); // libera o vetor
    return 0;
}
