#include <iostream>
#include <string>
#include <limits> 

struct Pokemon {
    std::string nome;
    int idade;
};

struct Node {
    Pokemon dados;    // dados do Pokémon
    Node* proximo;    // Ponteiro para o próximo nó
    Node* anterior;   // Ponteiro para o nó anterior

    // Construtor para facilitar a criação de um novo nó
    Node(Pokemon p) : dados(p), proximo(nullptr), anterior(nullptr) {}
};

/**
 * cria um novo tipo de dados
 * define que o que existe no type class seja acessado fora da class
 */
class ListaDuplamenteEncadeada {
public:
    Node* head; // Ponteiro para o primeiro nó da lista
    Node* tail; // Ponteiro para o último nó da lista

    // constrututor
    ListaDuplamenteEncadeada() : head(nullptr), tail(nullptr) {}

    // Destrutor: libera a memória de todos os nós ao destruir a lista
    ~ListaDuplamenteEncadeada() {
        Node* atual = head;
        Node* proximoNode = nullptr; // Variável para guardar o próximo antes de deletar o atual
        while (atual != nullptr) {
            proximoNode = atual->proximo;
            // std::cout << "Deletando no: " << atual->dados.nome << std::endl; // Para depuração
            delete atual;
            atual = proximoNode;
        }
        head = nullptr; // Garante que head e tail sejam nulos após a limpeza
        tail = nullptr;
    }

    // 1. Inserir um Pokémon
    void inserirPokemon(const Pokemon& p) {
        Node* novoNode = new Node(p);
        if (head == nullptr) { // Se a lista está vazia
            head = novoNode;
            tail = novoNode;
        } else { // Se a lista não está vazia, insere no final
            tail->proximo = novoNode;
            novoNode->anterior = tail;
            tail = novoNode;
        }
        std::cout << "Pokemon " << p.nome << " inserido com sucesso!\n";
    }

    // Função auxiliar para buscar um nó (usada internamente por procurar e remover)
    Node* buscarNode(const std::string& nome) const { // Marcar como const pois não altera a lista
        Node* atual = head;
        while (atual != nullptr) {
            if (atual->dados.nome == nome) {
                return atual;
            }
            atual = atual->proximo;
        }
        return nullptr;
    }

    // 2. Procurar um Pokémon pelo nome
    void procurarPokemon(const std::string& nome) const { // Marcar como const
        Node* encontrado = buscarNode(nome);
        if (encontrado != nullptr) {
            std::cout << "Pokemon encontrado: " << encontrado->dados.nome << ", Idade: " << encontrado->dados.idade << std::endl;
        } else {
            std::cout << "Pokemon " << nome << " nao encontrado.\n";
        }
    }

    // 3. Remover um Pokémon pelo nome
    void removerPokemon(const std::string& nome) {
        Node* nodeParaRemover = buscarNode(nome); // Usa a função auxiliar de busca

        if (nodeParaRemover == nullptr) {
            std::cout << "Pokemon " << nome << " nao encontrado para remocao.\n";
            return;
        }

        // Se o nó a ser removido é o head
        if (nodeParaRemover == head) {
            head = nodeParaRemover->proximo;
        }

        // Se o nó a ser removido é o tail
        if (nodeParaRemover == tail) {
            tail = nodeParaRemover->anterior;
        }

        // Ajusta o ponteiro 'proximo' do nó anterior (se existir)
        if (nodeParaRemover->anterior != nullptr) {
            nodeParaRemover->anterior->proximo = nodeParaRemover->proximo;
        }

        // Ajusta o ponteiro 'anterior' do nó seguinte (se existir)
        if (nodeParaRemover->proximo != nullptr) {
            nodeParaRemover->proximo->anterior = nodeParaRemover->anterior;
        }

        std::cout << "Pokemon " << nodeParaRemover->dados.nome << " removido com sucesso!\n";
        delete nodeParaRemover; // Libera a memória do nó removido
    }

    // 4. Imprimir todos os Pokémons cadastrados
    void imprimirTodos() const { // Marcar como const
        if (head == nullptr) {
            std::cout << "Nenhum Pokemon cadastrado.\n";
            return;
        }
        std::cout << "\n--- Lista de Pokemons ---\n";
        Node* atual = head;
        while (atual != nullptr) {
            std::cout << "Nome: " << atual->dados.nome << ", Idade: " << atual->dados.idade << std::endl;
            atual = atual->proximo;
        }
        std::cout << "-------------------------\n";
    }
};

// Função para limpar o buffer de entrada, especialmente após ler um número
void limparBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    ListaDuplamenteEncadeada pokedex;
    int opcao;
    std::string nomeEntrada; // Renomeado para evitar conflito com Pokemon.nome
    Pokemon novoPokemon;

    do {
        std::cout << "\n--- Menu Pokedex de Ash ---\n";
        std::cout << "1) Inserir Pokemon\n";
        std::cout << "2) Procurar Pokemon\n";
        std::cout << "3) Remover Pokemon\n";
        std::cout << "4) Imprimir todos os Pokemons\n";
        std::cout << "5) Sair do Programa\n";
        std::cout << "Escolha uma opcao: ";

        // Leitura e validação da opção
        while (!(std::cin >> opcao) || opcao < 1 || opcao > 5) {
            std::cout << "Opcao invalida. Por favor, digite um numero entre 1 e 5: ";
            std::cin.clear(); // Limpa flags de erro (ex: se o usuário digitou texto)
            limparBufferEntrada(); // Descarta a entrada inválida
        }
        limparBufferEntrada(); // Limpa o '\n' deixado pelo std::cin >> opcao

        switch (opcao) {
            case 1:
                std::cout << "Digite o nome do Pokemon: ";
                std::getline(std::cin, novoPokemon.nome);
                std::cout << "Digite a idade do Pokemon: ";
                while (!(std::cin >> novoPokemon.idade) || novoPokemon.idade < 0) {
                    std::cout << "Idade invalida. Digite um numero positivo: ";
                    std::cin.clear();
                    limparBufferEntrada();
                }
                limparBufferEntrada(); // Limpa o '\n' deixado pelo std::cin >> novoPokemon.idade
                pokedex.inserirPokemon(novoPokemon);
                break;
            case 2:
                std::cout << "Digite o nome do Pokemon a procurar: ";
                std::getline(std::cin, nomeEntrada);
                pokedex.procurarPokemon(nomeEntrada);
                break;
            case 3:
                std::cout << "Digite o nome do Pokemon a remover: ";
                std::getline(std::cin, nomeEntrada);
                pokedex.removerPokemon(nomeEntrada);
                break;
            case 4:
                pokedex.imprimirTodos();
                break;
            case 5:
                std::cout << "Saindo do programa. Ate mais, Ash!\n";
                break;
            // default não é mais necessário aqui devido à validação no loop while da opção
        }
    } while (opcao != 5);

    return 0;
} 