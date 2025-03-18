#include <stdio.h>

int main() {
    int A[] = {5, 8, 1, 2, 4};
    int tamanho = sizeof(A) / sizeof(A[0]);
    
    printf("Vetor original: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    // Algoritmo de ordenação por inserção
    int i, chave, j;
    for (i = 1; i < tamanho; i++) {
        chave = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > chave) {
            A[j + 1] = A[j];
            j = j - 1;
            /**
                printf("%d - ", i); //representativo
                for (int k = 0; k < tamanho; k++) {
                    printf("%d ", A[k]);
                }
                printf("\n"); //representativo
            */
        }
        A[j + 1] = chave;
    }
    
    printf("Vetor ordenado: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    return 0;
}
