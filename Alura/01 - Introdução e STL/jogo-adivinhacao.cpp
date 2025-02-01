#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

int main() {

  // Em ambos os caso que queremos quebrar linha podemos usar ou o \n ou endl
  cout << "***********************************\n";
  cout << "*Bem-vindos ao jogo da adivinhação*" << endl;
  cout << "***********************************" << endl;

  int number_secret = 55, number_user = 0, counter = 1;
  int point = 1000;
  bool acertou = false;

  // Coletando os dados - primeira rodada
  cout << "Digite o número secreto: ";
  cin >> number_user;
  
  if (number_user < 1000) {
    while (!acertou) {
      if (number_user > number_secret) {
        cout << "O número digitado é maior que o número secreto.\n";
        cout << "Tentativa " << counter << endl;
        cout << "Digite um número menor: ";
        cin >> number_user;

        point -= fabs((number_user - number_secret) / 2);
        counter++;
      } else if (number_user < number_secret) {
        cout << "O número digitado é menor que o número secreto.\n";
        cout << "Tentativa " << counter << endl;
        cout << "Digite um número maior: ";
        cin >> number_user;

        point -= fabs((number_user - number_secret) / 2);
        counter++;
      }
      if (number_user == number_secret) {
        cout << "Parabéns! Você acertou o número em " << counter << " tentativa.\n"
            << "A sua pontuação: " << point;
        acertou = true;
      }
    }
  } else {
      cout << "Digite um número menor que 1000.\n";
    }
    //cout << "Parabéns! Você acertou o número em " << counter << " tentativa.\n"
    //     << "A sua pontuação: " << point;
  return 0;
}