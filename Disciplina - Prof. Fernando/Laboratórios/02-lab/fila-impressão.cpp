#include <iostream>
#include <string>
#include <limits>


struct filaimpressão
{
  std::string nome;
};

struct No {
    filaimpressão dados;    // dados do aluno
    No* proximo;    // Ponteiro para o próximo nó
    No* anterior;   // Ponteiro para o nó anterior

    // Construtor para facilitar a criação de um novo nó
    No(filaimpressão p) : dados(p), proximo(nullptr), anterior(nullptr) {}
};

class FilaDuplamenteEncadeada {
public:
    No* head; // Ponteiro para o primeiro nó da lista
    No* tail; // Ponteiro para o último nó da lista

    // constrututor
    FilaDuplamenteEncadeada() : head(nullptr), tail(nullptr) {}

    // Destrutor: libera a memória de todos os nós ao destruir a lista
    ~FilaDuplamenteEncadeada() {
        No* atual = head;
        No* proximoNo = nullptr; // Variável para guardar o próximo antes de deletar o atual
        while (atual != nullptr) {
            proximoNo = atual -> proximo;
            // std::cout << "Deletando no: " << atual->dados.nome << std::endl; // Para depuração
            delete atual;
            atual = proximoNo;
        }
        head = nullptr; // Garante que head e tail sejam nulos após a limpeza
        tail = nullptr;
    }

    // 1. Inserir um Pokémon
    void inserirAluno(const filaimpressão& p) {
        No* novo = new No(p);
        if (head == nullptr) { // Se a lista está vazia
            head = novo;
            tail = novo;
        } else { // Se a lista não está vazia, insere no final
            tail->proximo = novo;
            novo->anterior = tail;
            tail = novo;
        }
        std::cout << "Aluno " << p.nome << " inserido na fila com sucesso!\n";
    }

    // Função auxiliar para buscar um nó (usada internamente por procurar e remover)
    No* buscarNo(const std::string& nome) const { // Marcar como const pois não altera a lista
        No* atual = head;
        while (atual != nullptr) {
            // Se encontrar o nó com o nome desejado
            if (atual->dados.nome == nome) {
                return atual;
            }
            atual = atual->proximo;
        }
        return nullptr;
    }

    // 2. Procurar um aluno pelo nome
    void procurarAluno(const std::string& nome) const {
        No* encontrado = buscarNo(nome);
        if (encontrado != nullptr) {
            std::cout << "Aluno encontrado: " << encontrado->dados.nome << std::endl;
        } else {
            std::cout << "Aluno " << nome << " nao encontrado.\n";
        }
    }

    // 3. Remover um Aluno pelo nome
    void removerAluno(const std::string& nome) {
        No* noParaRemover = buscarNo(nome); // Usa a função auxiliar de busca

        if (noParaRemover == nullptr) {
            std::cout << "Aluno " << nome << " nao encontrado para remocao.\n";
            return;
        }

        // Se o nó a ser removido é o head(primeiro)
        if (noParaRemover == head) {
            head = noParaRemover->proximo;
        }

        // Se o nó a ser removido é o tail(ultimo)
        if (noParaRemover == tail) {
            tail = noParaRemover->anterior;
        }

        // Ajusta o ponteiro 'proximo' do nó anterior (se existir)
        if (noParaRemover->anterior != nullptr) {
            noParaRemover->anterior->proximo = noParaRemover->proximo;
        }

        // Ajusta o ponteiro 'anterior' do nó seguinte (se existir)
        if (noParaRemover->proximo != nullptr) {
            noParaRemover->proximo->anterior = noParaRemover->anterior;
        }

        std::cout << "Aluno " << noParaRemover->dados.nome << " removido com sucesso!\n";
        delete noParaRemover; // Libera a memória do nó removido
    }

    // 4. Imprimir todos os Alunos cadastrados na fila
    void imprimirTodos() const { 
        if (head == nullptr) {
            std::cout << "Nenhum Aluno cadastrado.\n";
            return;
        }
        std::cout << "\n--- Lista de Alunos ---\n";
        No* atual = head;
        while (atual != nullptr) {
            std::cout << "Nome: " << atual->dados.nome << std::endl;
            atual = atual->proximo;
        }
        std::cout << "-------------------------\n";
    }
};

void limparBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main () {
    FilaDuplamenteEncadeada impressao;
    int opcao;
    std::string nomeEntrada; // Renomeado para evitar conflito com aluno.nome
    filaimpressão novoAluno;

    do {
        std::cout << "\n--- Menu impressao da Area II---\n";
        std::cout << "1) Inserir aluno\n";
        std::cout << "2) Procurar aluno\n";
        std::cout << "3) Remover aluno\n";
        std::cout << "4) Imprimir todos os alunos\n";
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
                std::cout << "Digite o nome do aluno: ";
                std::getline(std::cin, novoAluno.nome);
                impressao.inserirAluno(novoAluno);
                break;
            case 2:
                std::cout << "Digite o nome do aluno a procurar: ";
                std::getline(std::cin, nomeEntrada);
                impressao.procurarAluno(nomeEntrada);
                break;
            case 3:
                std::cout << "Digite o nome do aluno a remover: ";
                std::getline(std::cin, nomeEntrada);
                impressao.removerAluno(nomeEntrada);
                break;
            case 4:
                impressao.imprimirTodos();
                break;
            case 5:
                std::cout << "Saindo do programa. Ate mais, Ash!\n";
                break;
        }
    } while (opcao != 5);

    return 0;
}