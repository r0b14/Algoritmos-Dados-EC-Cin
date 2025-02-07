#include <iostream>

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

    // Contadores
    int comparacoes = 0;
    int substituicoes = 0;
    int iteracoes = 0;

    cout << "Vetor original: ";
    printArray(letters, tam);
    cout << endl;

    // Implementação do MergeSort
    // Definir o tamanho dos subarrays
    for (int size = 1; size < tam; size = size * 2) {
        iteracoes++;
        // Percorrer o array principal
        for (int leftStart = 0; leftStart < tam - 1; leftStart += 2 * size) {
            // Definir os índices para o merge
            int mid = min(leftStart + size - 1, tam - 1);
            int rightEnd = min(leftStart + 2 * size - 1, tam - 1);
            // Processo de merge
            int left = leftStart;
            int right = mid + 1;
            
            // Array temporário para armazenar o resultado do merge
            char temp[tam];
            int tempIndex = leftStart;
            
            // Merge dos dois subarrays
            while (left <= mid && right <= rightEnd) {
                comparacoes++;
                if (letters[left] <= letters[right]) {
                    temp[tempIndex] = letters[left];
                    left++;
                } else {
                    temp[tempIndex] = letters[right];
                    right++;
                }
                substituicoes++;
                tempIndex++;
            }
            
            while (left <= mid) {
                temp[tempIndex] = letters[left];
                left++;
                tempIndex++;
                substituicoes++;
            }
            while (right <= rightEnd) {
                temp[tempIndex] = letters[right];
                right++;
                tempIndex++;
                substituicoes++;
            }
            for (int i = leftStart; i <= rightEnd; i++) {
                letters[i] = temp[i];
            }
        }
        // Imprimir estado atual após cada iteração
        cout << "Estado após iteração " << iteracoes << ": ";
        printArray(letters, tam);
    }
    
    cout << "\nVetor ordenado final: ";
    printArray(letters, tam);
    
    cout << "\nEstatísticas:" << endl;
    cout << "Número de comparações: " << comparacoes << endl;
    cout << "Número de substituições: " << substituicoes << endl;
    cout << "Número de iterações: " << iteracoes << endl;
    
    return 0;
}