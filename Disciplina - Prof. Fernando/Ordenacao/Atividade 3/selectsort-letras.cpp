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

    for (int i = 0; i < tam; i++) {
        iteracoes++;
        int least = i;
        for (int j = i + 1; j < tam; j++) {
            comparacoes++;
            if (letters[j] < letters[least]) {
                least = j;
            }
        }
        if (least != i) {
            swap(letters[i], letters[least]);
            substituicoes++;
        }

        cout << "Iteração " << iteracoes << ": ";
        printArray(letters, tam);
    }

    cout << "\nVetor ordenado final: ";
    printArray(letters, tam);

    cout << "\nContagens:" << endl;
    cout << "Número de comparações: " << comparacoes << endl;
    cout << "Número de substituições: " << substituicoes << endl;
    cout << "Número de iterações: " << iteracoes << endl;

    return 0;
}