#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

struct Pessoa {
    std::string nome;
    int prioridade, num_cadastro;
    bool esta_sentado = false;
    int fileira = -1, assento_idx = -1;
    
    Pessoa(std::string n, int p, int c) : nome(n), prioridade(p), num_cadastro(c) {}
};

/*
 * Comparadores para filas de prioridade
 * MinHeap: menor prioridade no topo (para pessoas sentadas)
 * MaxHeap: maior prioridade no topo (para fila de espera)
 */
struct MinHeapComp {
    bool operator()(Pessoa* a, Pessoa* b) {
        if (a->prioridade != b->prioridade) return a->prioridade > b->prioridade;
        return a->num_cadastro < b->num_cadastro;
    }
};

struct MaxHeapComp {
    bool operator()(Pessoa* a, Pessoa* b) {
        if (a->prioridade != b->prioridade) return a->prioridade < b->prioridade;
        return a->num_cadastro > b->num_cadastro;
    }
};

bool temMaiorPrioridade(Pessoa* a, Pessoa* b) {
    if (a->prioridade != b->prioridade) return a->prioridade > b->prioridade;
    return a->num_cadastro < b->num_cadastro;
}

/*
 * Sistema Simplificado de Gerenciamento de Teatro
 * Usa containers STL para reduzir complexidade do código
 */
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int F, Q, N;
    std::cin >> F >> Q >> N;

    int capacidade_total = F * Q;
    int contador_cadastro = 0, assentos_ocupados = 0;

    std::unordered_map<std::string, Pessoa*> pessoas;
    std::priority_queue<Pessoa*, std::vector<Pessoa*>, MinHeapComp> sentados;
    std::priority_queue<Pessoa*, std::vector<Pessoa*>, MaxHeapComp> sem_assento;

    for (int k = 0; k < N; ++k) {
        std::string comando;
        std::cin >> comando;

        if (comando == "CAD") {
            std::string nome;
            int prioridade;
            std::cin >> nome >> prioridade;

            contador_cadastro++;
            Pessoa* nova_pessoa = new Pessoa(nome, prioridade, contador_cadastro);
            pessoas[nome + std::to_string(contador_cadastro)] = nova_pessoa;

            /*
             * Lógica de Alocação Simplificada
             * Verifica disponibilidade e prioridades para alocação de assentos
             */
            if (assentos_ocupados < capacidade_total) {
                nova_pessoa->esta_sentado = true;
                nova_pessoa->fileira = (assentos_ocupados / Q) + 1;
                nova_pessoa->assento_idx = (assentos_ocupados % Q);
                assentos_ocupados++;
                
                sentados.push(nova_pessoa);
                std::cout << nova_pessoa->nome << " (" << nova_pessoa->num_cadastro << ") foi alocado(a) na fileira " << nova_pessoa->fileira << std::endl;
            } else {
                Pessoa* min_prioridade = sentados.top();
                
                if (temMaiorPrioridade(nova_pessoa, min_prioridade)) {
                    sentados.pop();
                    
                    min_prioridade->esta_sentado = false;
                    sem_assento.push(min_prioridade);
                    
                    nova_pessoa->esta_sentado = true;
                    nova_pessoa->fileira = min_prioridade->fileira;
                    nova_pessoa->assento_idx = min_prioridade->assento_idx;
                    sentados.push(nova_pessoa);

                    std::cout << nova_pessoa->nome << " (" << nova_pessoa->num_cadastro << ") foi alocado(a) na fileira " << nova_pessoa->fileira << std::endl;
                } else {
                    nova_pessoa->esta_sentado = false;
                    sem_assento.push(nova_pessoa);
                    std::cout << nova_pessoa->nome << " (" << nova_pessoa->num_cadastro << ") nao foi alocado(a) em nenhuma fileira" << std::endl;
                }
            }
        } 
        else if (comando == "REM") {
            std::string nome;
            int num_c;
            std::cin >> nome >> num_c;

            auto it = pessoas.find(nome + std::to_string(num_c));
            if (it == pessoas.end()) {
                std::cout << "Inexistente" << std::endl;
            } else {
                Pessoa* p = it->second;
                
                /*
                 * Remoção com Reconstrução das Filas
                 * Abordagem simplificada que reconstrói as estruturas após remoção
                 */
                if (p->esta_sentado) {
                    std::vector<Pessoa*> temp_sentados;
                    while (!sentados.empty()) {
                        Pessoa* atual = sentados.top();
                        sentados.pop();
                        if (atual != p) temp_sentados.push_back(atual);
                    }
                    
                    for (Pessoa* pessoa : temp_sentados) {
                        sentados.push(pessoa);
                    }
                    
                    if (!sem_assento.empty()) {
                        Pessoa* sortudo = sem_assento.top();
                        sem_assento.pop();
                        sortudo->esta_sentado = true;
                        sortudo->fileira = p->fileira;
                        sortudo->assento_idx = p->assento_idx;
                        sentados.push(sortudo);
                    } else {
                        assentos_ocupados--;
                    }
                } else {
                    std::vector<Pessoa*> temp_sem_assento;
                    while (!sem_assento.empty()) {
                        Pessoa* atual = sem_assento.top();
                        sem_assento.pop();
                        if (atual != p) temp_sem_assento.push_back(atual);
                    }
                    
                    for (Pessoa* pessoa : temp_sem_assento) {
                        sem_assento.push(pessoa);
                    }
                }
                
                pessoas.erase(it);
                delete p;
                std::cout << "Removido(a)" << std::endl;
            }
        } 
        else if (comando == "VER") {
            std::string nome;
            int num_c;
            std::cin >> nome >> num_c;

            auto it = pessoas.find(nome + std::to_string(num_c));
            if (it == pessoas.end()) {
                std::cout << "Inexistente" << std::endl;
            } else {
                Pessoa* p = it->second;
                if (p->esta_sentado) {
                    std::cout << "Sentado(a) na fileira " << p->fileira << std::endl;
                } else {
                    std::cout << "Sem assento" << std::endl;
                }
            }
        }
    }

    for (auto& pair : pessoas) {
        delete pair.second;
    }

    return 0;
}
