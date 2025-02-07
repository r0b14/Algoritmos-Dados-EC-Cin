#include <iostream>
#include <stdlib.h>

using namespace std;

/**
 * 1. Fiz alguns testes para poder verificar se de fato o alfabeto estava sendo reconhecido de forma inteiro.
 * 
 */

// Função auxiliar para imprimir o vetor
void printArray(char arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main () {

  // Ordenando o alfabeto conforme 
  char vector_letter[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

  char sequence[] = {'R','M','Q','F','P','W','Z','Y','K','A','S','I','O','H','B','J','L','V','U'};

  int tam = sizeof(sequence) / sizeof(sequence[0]);

  // Contadores para estatísticas
  int comparacoes = 0;
  int trocas = 0;
  int iteracoes = 0;

  cout << "Vetor inicial: ";
  printArray(sequence, tam);
  cout << endl;

  // Aplicando o bubblesort no vetor sequence
  for (int i = 0; i < tam-1; i++) {
    iteracoes++;
    //cout << "\nIteração " << iteracoes << ":\n";
    for (int j = tam-1; j > i; j--) {
      comparacoes++;
      if (sequence[j] < sequence[j-1]) {
        swap(sequence[j], sequence[j-1]);
        trocas++;
      }
    }
    
    cout << "Iteração " << iteracoes << ": ";
    printArray(sequence, tam);
  }

  cout << "\nVetor ordenado: ";
  printArray(sequence, tam);
  cout << "Número total de comparações: " << comparacoes << endl;
  cout << "Número total de trocas: " << trocas << endl;
  cout << "Número total de iterações: " << iteracoes << endl;

  return 0;
}