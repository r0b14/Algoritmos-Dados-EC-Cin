#include <iostream>
#include <stdlib.h>

using namespace std;

// Função auxiliar para imprimir o vetor
void printArray(char arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {

     char letters[] = {'R','M','Q','F','P','W','Z','Y','K','A','S','I','O','H','B','J','L','V','U'};
 
     int tam = sizeof(letters) / sizeof(letters[0]);
     // Contadores para estatísticas

     cout << "Vetor original: ";
     printArray(letters, tam);
     // Algoritmo Insertion Sort
     for (int i = 1; i < tam; i++) {
        int j;
         char chave = letters[i];
         for (j = i; j > 0 && chave < letters[j-1]; j--) {
             letters[j] = letters[j-1];
         }
         letters[j] = chave;
     }

    // int numbers[] = {5,2,3,8,1};
    // int tam = sizeof(numbers)/sizeof(numbers[0]);

    // cout << "Vetor original: " << endl;
    // printArray(numbers, tam);

    // for (int i = 1; i < tam; i++) {
    //     int tmp = numbers[i];
    //     int j;
    //     for (j = i; j > 0 && tmp < numbers[j-1]; j--) {
    //         numbers[j] = numbers[j-1];
    //     }
    //     numbers[j] = tmp;
    //     cout << "Passo " << i << ": ";
    //     printArray(numbers, tam);
    // }
    // printArray(numbers, tam);
    
    cout << "\nVetor ordenado final: ";
    printArray(letters, tam);
    return 0;
}