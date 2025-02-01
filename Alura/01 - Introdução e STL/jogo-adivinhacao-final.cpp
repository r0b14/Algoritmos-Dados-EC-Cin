#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

  // Em ambos os caso que queremos quebrar linha podemos usar ou o \n ou endl
  cout << "***********************************\n";
  cout << "*Bem-vindos ao jogo da adivinhação*" << endl;
  cout << "***********************************" << endl;

  // Inicializa o gerador de números aleatórios
  srand(time(0));
  // Gera um número aleatório entre 1 e 1000
  const int numberSecret = rand() % 1000 + 1;
  
  int tentativa;
  int numeroTentativas = 0;
  bool naoAcertou = true;

  cout << "\nPense em um número entre 1 e 1000" << endl;

  while(naoAcertou) {
    numeroTentativas++;
    
    cout << "Tentativa " << numeroTentativas << ": ";
    cin >> tentativa;

    if(tentativa == numberSecret) {
      cout << "Parabéns! Você acertou o número em " << numeroTentativas << " tentativas!" << endl;
      naoAcertou = false;
    }
    else if(tentativa > numberSecret) {
      cout << "O número secreto é MENOR!" << endl;
    }
    else {
      cout << "O número secreto é MAIOR!" << endl;
    }
  }

  cout << "\nFim do jogo!" << endl;
  return 0;
}