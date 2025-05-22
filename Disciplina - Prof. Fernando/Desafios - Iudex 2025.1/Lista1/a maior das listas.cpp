#include <iostream>
#include <string>

// Função para contar os elementos em uma string de lista formatada como "[a,b,c]"
int countElements(const std::string& listStr) {
    size_t firstBracket = listStr.find('[');
    size_t lastBracket = listStr.rfind(']');

    // Verifica se os colchetes foram encontrados e estão na ordem correta
    if (firstBracket == std::string::npos || lastBracket == std::string::npos || firstBracket >= lastBracket) {
        return 0; // Formato inválido ou não é uma lista como esperado
    }

    std::string content = listStr.substr(firstBracket + 1, lastBracket - firstBracket - 1);

    if (content.empty()) {
        return 0;
    }

    // Conta o número de vírgulas para determinar o número de elementos
    // Número de elementos = número de vírgulas + 1
    int commaCount = 0;
    for (char ch : content) {
        if (ch == ',') {
            commaCount++;
        }
    }
    return commaCount + 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string currentLine;
    std::string listWithMaxElements;
    int maxElementCount = -1;

    // Lê linha por linha da entrada padrão até o fim (EOF)
    while (std::getline(std::cin, currentLine)) {
        if (currentLine.empty()) {
            continue;
        }

        int currentElementsInLine = countElements(currentLine);

        // Se esta é a primeira lista processada ou se a lista atual
        
        if (maxElementCount == -1 || currentElementsInLine > maxElementCount) {
            maxElementCount = currentElementsInLine;
            listWithMaxElements = currentLine;
        }
    }

    if (maxElementCount != -1) {
        std::cout << listWithMaxElements << std::endl;
    }

    return 0;
}