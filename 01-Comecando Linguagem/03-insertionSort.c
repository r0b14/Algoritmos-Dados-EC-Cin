#include <stdio.h>

void insertionSort(int arr[], int n) {
    int i, chave, j;
    for (i = 1; i < n; i++) {
        chave = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j = j - 1;
            /**
                printf("%d - ", i); //representativo
                for (int k = 0; k < n; k++) {
                    printf("%d ", arr[k]);
                }
                printf("\n"); //representativo
            */
        }
        arr[j + 1] = chave;
    }
}

int main() {
    int A[] = {5, 8, 1, 2, 4};
    int tamanho = sizeof(A) / sizeof(A[0]);
    
    printf("Vetor original: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    insertionSort(A, tamanho);
    
    printf("Vetor ordenado: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    return 0;
}
