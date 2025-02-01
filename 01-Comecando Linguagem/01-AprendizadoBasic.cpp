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
    cout << "***********************" << endl;

    int value1 = 110, value2 = 220;
    cout << "O valor da variável: "<< value1 << endl;
    cout << "O valor da variável2 "<< value2 << " é referente a voltagem." << endl;

    // Sem usar a #<string>
    char name1[100] = "Robson Thiago";
    // Com o uso da #<string>
    auto name = "Robson";
    cout << "Nome do usuário: "<< name << endl;
    cout << "Nome e Sobrenome: "<< name1 << endl;

    double numbersize = 9999999999999999999999999999999999.999;

    cout << "Double= " << numbersize << endl;

    return 0;
}