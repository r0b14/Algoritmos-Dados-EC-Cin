/**
* Criando o Jogo de Adivinhação.
**/ 
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Tela de apresentação
    cout << "***********************" << endl;
    cout << "* Welcome to the game *" << endl;
    cout << "***********************" << endl << endl;

    int randomValue = 52, kick = 0;
    cout << "O valor da variável: "<< randomValue << endl;

    cout << "Digite o valor do chute: ";
    cin >> kick;

    // Comparação de valores entre variáveis

    //cout << "O valor chutado: " << kick << endl;
    while (randomValue != kick) {
        if (kick > randomValue) {
            cout << endl << "** O chute é maior que o random **" << endl;
            cout << "Digite o novo valor: ";
            cin >> kick;
        }
        else {
            cout << endl << "** O chute é menor que o random **" << endl;
            cout << "Digite o novo valor: ";
            cin >> kick;
        }

    }   
    cout << "Parabéns, você acertou o valor" << endl;

    return 0;
}