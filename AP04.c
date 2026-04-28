#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  char palavra[100];
  int valor;
} words;

int main() {
  int N, k;
  scanf("%d", &N); //numero de palavras
  words A[N+1] = (words*)malloc(N * sizeof(words));
  scanf("%d", &k); //numero de repetiçoes
  printf("N: %d, k: %d\n", N, k);
  for (int i = 0; i < N; i++) {
    scanf("%s", &A[i]);
    printf("%s\n", A[i]->palavra);
  }

  
  return 0;
}
