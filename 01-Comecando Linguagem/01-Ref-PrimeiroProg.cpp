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

    int randomValue = 52, kick;
    int contador = 1;
    float pontuacao = 1000.0;

    // cout << "O valor da variável: "<< randomValue << endl;
    // Comparação de valores entre variáveis

    cout << "Write " << kick << " kick: "<< endl;
    cin >> kick;

    while (randomValue != kick) {
        contador++;
        cout << " " << contador << "° Tentativa" << endl;
        cout << "Digite o valor do chute: ";
        cin >> kick;
        
        if (kick > randomValue) {
            cout << endl << "** O chute é maior que o random **" << endl;
        }
        else if (kick < randomValue) {
            cout << endl << "** O chute é menor que o random **" << endl;
        }
    }   
    cout << "Parabéns, você acertou o valor" << endl;

    return 0;
}