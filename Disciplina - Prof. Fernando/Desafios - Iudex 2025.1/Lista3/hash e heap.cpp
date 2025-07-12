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
 * Sistema de Gerenciamento de Teatro
 * Utiliza hash map e priority queues para otimizar operações
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
             * Lógica Central de Alocação de Assentos
             * 1. Assentos livres: alocação direta
             * 2. Teatro cheio: comparação de prioridades para "desbanco"
             * 3. Sem conseguir assento: inserção na fila de espera
             */
            if (assentos_ocupados < capacidade_total) {
                nova_pessoa->esta_sentado = true;
                nova_pessoa->fileira = (assentos_ocupados / Q) + 1;
                nova_pessoa->assento_idx = (assentos_ocupados % Q);
                assentos_ocupados++;
                
                sentados.inserir(nova_pessoa);
                std::cout << nova_pessoa->nome << "(" << nova_pessoa->num_cadastro << ") foi alocado(a) na fileira " << nova_pessoa->fileira << std::endl;
            } else {
                Pessoa* min_prioridade_sentado = sentados.verTopo();
                
                if (compararParaMaxHeap(nova_pessoa, min_prioridade_sentado)) {
                    Pessoa* pessoa_removida = sentados.extrairTopo();
                    
                    pessoa_removida->esta_sentado = false;
                    sem_assento.inserir(pessoa_removida);
                    
                    nova_pessoa->esta_sentado = true;
                    nova_pessoa->fileira = pessoa_removida->fileira;
                    nova_pessoa->assento_idx = pessoa_removida->assento_idx;
                    sentados.inserir(nova_pessoa);

                    std::cout << nova_pessoa->nome << "(" << nova_pessoa->num_cadastro << ") foi alocado(a) na fileira " << nova_pessoa->fileira << std::endl;
                } else {
                    nova_pessoa->esta_sentado = false;
                    sem_assento.inserir(nova_pessoa);
                    std::cout << nova_pessoa->nome << "(" << nova_pessoa->num_cadastro << ") nao foi alocado(a) em nenhuma fileira" << std::endl;
                }
            }
        } else if (comando == "REM") {
            std::string nome;
            int num_c;
            std::cin >> nome >> num_c;

            Pessoa* p = tabela_hash.buscar(nome, num_c);
            if (p == nullptr) {
                std::cout << "Inexistente" << std::endl;
            } else {
                if (p->esta_sentado) {
                    sentados.removerElemento(p);
                    
                    if (sem_assento.getTamanho() > 0) {
                        Pessoa* sortudo = sem_assento.extrairTopo();
                        sortudo->esta_sentado = true;
                        sortudo->fileira = p->fileira;
                        sortudo->assento_idx = p->assento_idx;
                        sentados.inserir(sortudo);
                    } else {
                        assentos_ocupados--;
                    }
                } else {
                    sem_assento.removerElemento(p);
                }
                tabela_hash.remover(nome, num_c);
                delete p;
                std::cout << "Removido(a)" << std::endl;
            }
        } else if (comando == "VER") {
            std::string nome;
            int num_c;
            std::cin >> nome >> num_c;

            Pessoa* p = tabela_hash.buscar(nome, num_c);
            if (p == nullptr) {
                std::cout << "Inexistente" << std::endl;
            } else {
                if (p->esta_sentado) {
                    std::cout << "Sentado(a) na fileira " << p->fileira << std::endl;
                } else {
                    std::cout << "Sem assento" << std::endl;
                }
            }
        }
    }

    /*
     * Limpeza Final de Memória
     * Libera todos os objetos Pessoa que não foram removidos explicitamente
     */
    int contador_limpeza = 0;
    Pessoa** todos_ponteiros = new Pessoa*[max_pessoas]();
    tabela_hash.coletarTodosOsPonteiros(todos_ponteiros, contador_limpeza);
    for(int i=0; i<contador_limpeza; ++i) {
        bool ainda_existe = (tabela_hash.buscar(todos_ponteiros[i]->nome, todos_ponteiros[i]->num_cadastro) != nullptr);
        if(ainda_existe) {
             delete todos_ponteiros[i];
        }
    }
    delete[] todos_ponteiros;


    return 0;
}