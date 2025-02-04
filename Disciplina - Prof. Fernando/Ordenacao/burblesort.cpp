#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {

  /* Estudo de ordenação de um vetor */
  int data[] = { 12, 20, 5, 8, 9}, tam;
  tam = sizeof(data) / sizeof(data[0]); // sabe qual o tamanho do array. 20/4 = 5 [elementos] 

    cout << "Antes da Ordenação. \n"
         << "Elementos: ";
  for (int i = 0; i < tam; i++)
  {
    cout << " " << data[i];
  }

  for (int i = 0; i < tam-1; i++) {
    for (int j = tam-1 ; j > i; j--) {
      if (data[j] < data[j-1]) {
        swap(data[j], data[j-1]);
      }
    }
  }

  cout << "\nOrdenado. \n"
         << "Elementos: ";
  for (int i = 0; i < tam; i++)
  {
    cout << " " << data[i];
  }
  return 0;
}