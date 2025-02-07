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

    // Shell Sort
    for (int outff = tam/2; outff > 0; outff /= 2) {
        cout << "\nTemp atual: " << outff << endl;
        for (int i = outff; i < tam; i++) {
            char temp = letters[i];
            int j;
            for (j = i; j >= outff && letters[j - outff] > temp; j -= outff) {
                letters[j] = letters[j - outff];
                comparacoes++;
                substituicoes++;
                iteracoes++;
            }
            letters[j] = temp;
            substituicoes++;
            // Imprime o estado atual do vetor após cada iteração do outff
            cout << "Estado atual: ";
            printArray(letters, tam);
        }
    }
    cout << "\nVetor ordenado: ";
    printArray(letters, tam);
    
    cout << "\nEstatísticas do Shell Sort:" << endl;
    cout << "Número de comparações: " << comparacoes << endl;
    cout << "Número de substituições: " << substituicoes << endl;
    cout << "Número de iterações: " << iteracoes << endl;

    return 0;
}