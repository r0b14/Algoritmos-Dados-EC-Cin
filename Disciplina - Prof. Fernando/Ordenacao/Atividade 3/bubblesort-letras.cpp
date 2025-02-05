#include <iostream>
#include <stdlib.h>

using namespace std;

/**
 * 1. Fiz alguns testes para poder verificar se de fato o alfabeto estava sendo reconhecido de forma inteiro.
 * 
 */
int main () {

  // Ordenando o alfabeto conforme 
  char vector_letter[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

  char sequence[] = {'R','M','Q','F','P','W','Z','Y','K','A','S','I','O','H','B','J','L','V','U'};

  int tam = sizeof(sequence) / sizeof(sequence[0]);

  // Aplicando o bubblesort no vetor sequence

  // (i = começo )
  for (int i = 0; i < tam-1; i++) {
    for (int j = tam-1 ; j > i; j--) {
      if (sequence[j] < sequence[j-1]) {
        swap(sequence[j], sequence[j-1]);
      }
    }
    cout << sequence[i] << " ";
  }

  /**
    // Mostrando apenas letras em posições pares
    for (int i = 0; i < 26; i++) {
      if (i % 2 == 0) {  // Verifica se o índice é par
        cout << vector_letter[i] << " ";
      }
    }

    cout << endl;  // Adiciona uma quebra de linha no final
   */
}