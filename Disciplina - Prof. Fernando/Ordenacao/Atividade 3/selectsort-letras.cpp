#include <iostream>

using namespace std;

int main() {
  
  char letters[] = {'R','M','Q','F','P','W','Z','Y','K','A','S','I','O','H','B','J','L','V','U'};
  int tam = sizeof(letters) / sizeof(letters[0]); // Qual o comprimento mãximo do nosso vetor. [19]

  for (int i=0; i < tam; i++) {
    int least = i; // é a variável que armazena o local onde fica localizado o menor elemento encontrado.
    for (int j=i+1; j < tam; j++){
      if (letters[j] < letters[least]){
        least = j;
      }
    }
    swap(letters[i], letters[least]); // troca do menor elemento encontrada com o elemento da posição i.
    cout << letters[i] << " ";
  }

  return 0;
}