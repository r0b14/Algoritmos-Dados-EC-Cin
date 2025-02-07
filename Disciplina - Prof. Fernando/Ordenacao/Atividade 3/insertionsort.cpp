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
    
    // Contadores para estatísticas
    int comparacoes = 0;
    int substituicoes = 0;
    int iteracoes = 0;
    
    cout << "Vetor original: ";
    printArray(letters, tam);
    cout << "\nProcesso de ordenação:\n";
    
    // Algoritmo Insertion Sort
    for (int i = 1; i < tam; i++) {
        char chave = letters[i];
        int j = i - 1;
        iteracoes++;
        // Move elementos maiores que a chave para uma posição à frente
        while (j >= 0 && letters[j] > chave) {
            comparacoes++;
            letters[j + 1] = letters[j];
            substituicoes++;
            j--;
        }
        // Uma comparação adicional que falhou e quebrou o while
        if (j >= 0) {
            comparacoes++;
        }
        letters[j + 1] = chave;
        if (j + 1 != i) {
            substituicoes++;
        }
        cout << "Iteração " << i << ": ";
        printArray(letters, tam);
    }
    
    cout << "\nVetor ordenado final: ";
    printArray(letters, tam);
    
    cout << "\nEstatísticas:";
    cout << "\nNúmero de iterações: " << iteracoes;
    cout << "\nNúmero de comparações: " << comparacoes;
    cout << "\nNúmero de substituições: " << substituicoes << endl;
    
    return 0;
}