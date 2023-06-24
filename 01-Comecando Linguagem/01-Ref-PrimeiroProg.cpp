/**
* Criando o Jogo de Adivinhação.
**/ 
#include <iostream>
#include <string>
using namespace std;

// Refatorando o Código
int main() {
    // Tela de apresentação
    cout << "***********************" << endl;
    cout << "* Welcome to the game *" << endl;
    cout << "***********************" << endl << endl;

    const int Num_Secret = 50;

    int tentativas = 0;
    bool nao_acerto = true;
    float pontos = 1000.0;

    while (nao_acerto) {
        tentativas++;
        int kick;
       
        cout << " " << tentativas << "° Tentativa" << endl;
        cout << "Digite o valor do chute: ";
        cin >> kick;
        
        double calculadorPontuacao = abs(kick - Num_Secret)/2;
        pontos = pontos - calculadorPontuacao;
        
        if (kick > Num_Secret) {
            cout << endl << "** O chute é maior que o random **" << endl;
        }
        else if (kick < Num_Secret) {
            cout << endl << "** O chute é menor que o random **" << endl;
        }
        else if (kick == Num_Secret) {
            nao_acerto = false;
            cout << endl << "Parabéns, você acertou o valor" << endl;
            cout << "Sua pontuação Final = "<< pontos << endl;
        }
    }

    return 0;
}