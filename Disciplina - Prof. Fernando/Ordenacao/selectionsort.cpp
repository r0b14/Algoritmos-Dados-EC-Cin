#include <iostream>
# include <stdlib.h>

using namespace std;

int main() {
  int numbers[] = {5,2,3,8,1}, least;
  int tam = sizeof(numbers)/sizeof(numbers[0]); // tamanho do vetor

  for (int i = 0; i < tam; i++) {
    least = i;
    for (int j = i+1; j < tam; j++){
      if (numbers[j] < numbers[least]){
        least = j;
      }
      swap(numbers[i], numbers[least]); // Troca de posições
    }
    cout << numbers[i] << " ";
  }
}