#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

  // Em ambos os caso que queremos quebrar linha podemos usar ou o \n ou endl
  cout << "***********************************\n";
  cout << "*Bem-vindos ao jogo da adivinhação*" << endl;
  cout << "***********************************" << endl;

  int number_secret = 55, number_user = 0;
  int counter = 1;
  cout << "Digite o número secreto: ";
  cin >> number_user;

  while (number_user != number_secret) {
    counter++;
    if (number_user > number_secret) {
      cout << "O número digitado é maior que o número secreto.\n";
      cout << "Tentativa " << counter << endl;
      cout << "Digite um número menor: ";
      cin >> number_user;
    } else {
      cout << "O número digitado é menor que o número secreto.\n";
      cout << "Tentativa " << counter << endl;
      cout << "Digite um número maior: ";
      cin >> number_user;
    }
  } 
  cout << "Parabéns! Você acertou o número em \n"
  << counter << " tentativa.";

  return 0;
}