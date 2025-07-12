#include <iostream>
#include <string>

// Usamos um enum para deixar o código mais legível ao representar o estado de um jazigo.
enum EstadoJazigo { VAZIO, OCUPADO, REMOVIDO };

// Estrutura para representar um único jazigo.
struct Jazigo {
    int chave;          // Número do seguro social do indivíduo
    EstadoJazigo estado; // Estado atual do jazigo

    // Construtor para inicializar um jazigo como VAZIO.
    Jazigo() {
        chave = -1; // -1 indica que não há chave válida
        estado = VAZIO;
    }
};

class Cemiterio {
private:
    Jazigo** andares; // Ponteiro para um array de ponteiros (nossa matriz M x L)
    int M;            // Número de andares
    int L;            // Número de jazigos por andar
    int corpos;       // Contador de corpos atualmente no cemitério

    // Função de hash principal
    int hash(int chave) {
        return chave % M;
    }

    // Função para reconstruir a tabela (rehash) quando ela fica cheia.
    void rehash() {
        int M_antigo = M;
        Jazigo** andares_antigos = andares;

        // Dobramos o tamanho e garantimos que seja ímpar, conforme a regra 2M+1
        M = (2 * M) + 1;
        corpos = 0; // Resetamos a contagem pois vamos reinserir todos
        
        // Alocamos a nova estrutura de andares
        andares = new Jazigo*[M];
        for (int i = 0; i < M; ++i) {
            andares[i] = new Jazigo[L];
        }

        // Percorremos a tabela antiga e reinserimos os corpos na nova
        for (int i = 0; i < M_antigo; ++i) {
            for (int j = 0; j < L; ++j) {
                if (andares_antigos[i][j].estado == OCUPADO) {
                    add(andares_antigos[i][j].chave);
                }
            }
        }

        // Liberamos a memória da tabela antiga
        for (int i = 0; i < M_antigo; ++i) {
            delete[] andares_antigos[i];
        }
        delete[] andares_antigos;
    }

public:
    // Construtor do Cemiterio
    Cemiterio(int m, int l) {
        M = m;
        L = l;
        corpos = 0;
        
        // Alocação dinâmica da matriz que representa os andares e jazigos
        andares = new Jazigo*[M];
        for (int i = 0; i < M; ++i) {
            andares[i] = new Jazigo[L];
        }
    }

    // Destrutor para liberar a memória alocada dinamicamente
    ~Cemiterio() {
        for (int i = 0; i < M; ++i) {
            delete[] andares[i];
        }
        delete[] andares;
    }

    // Adiciona um corpo
    void add(int chave) {
        // Se o cemitério está cheio, faz o rehash
        if (corpos >= M * L) {
            rehash();
        }

        int andar_inicial = hash(chave);
        int andar_atual = andar_inicial;

        do {
            // Verifica se o andar tem espaço
            if (andares[andar_atual][L - 1].estado == VAZIO || 
                (andares[andar_atual][L - 1].estado == OCUPADO && chave < andares[andar_atual][L - 1].chave)) {
                
                int pos_insercao = 0;
                // Encontra a posição correta para manter a ordem crescente
                while (pos_insercao < L && andares[andar_atual][pos_insercao].estado == OCUPADO && andares[andar_atual][pos_insercao].chave < chave) {
                    pos_insercao++;
                }

                // Se a posição já está ocupada, precisamos deslocar os elementos
                if(pos_insercao < L && (andares[andar_atual][pos_insercao].estado == OCUPADO || andares[andar_atual][pos_insercao].estado == REMOVIDO)) {
                    for (int k = L - 1; k > pos_insercao; --k) {
                        andares[andar_atual][k] = andares[andar_atual][k - 1];
                    }
                }

                // Insere o novo corpo
                andares[andar_atual][pos_insercao].chave = chave;
                andares[andar_atual][pos_insercao].estado = OCUPADO;
                corpos++;
                
                std::cout << andar_atual << ":" << pos_insercao << std::endl;
                return;
            }
            
            // Sondagem linear: vai para o próximo andar
            andar_atual = (andar_atual + 1) % M;

        } while (andar_atual != andar_inicial); // Para se der a volta completa
    }

    // Remove um corpo
    void rem(int chave) {
        int andar_inicial = hash(chave);
        int andar_atual = andar_inicial;

        do {
            for (int j = 0; j < L; ++j) {
                // Se encontramos a chave e ela está ocupada
                if (andares[andar_atual][j].chave == chave && andares[andar_atual][j].estado == OCUPADO) {
                    andares[andar_atual][j].estado = REMOVIDO; // Marca como removido (lazy deletion)
                    corpos--;
                    std::cout << andar_atual << ":" << j << std::endl;
                    return;
                }
                // Se encontramos um jazigo vazio, a chave não está na tabela (pois a inserção preenche sequencialmente)
                if (andares[andar_atual][j].estado == VAZIO) {
                    std::cout << "?:?" << std::endl;
                    return;
                }
            }
            andar_atual = (andar_atual + 1) % M;
        } while (andar_atual != andar_inicial);

        std::cout << "?:?" << std::endl; // Não encontrou após percorrer tudo
    }

    // Consulta um corpo
    void qry(int chave) {
        int andar_inicial = hash(chave);
        int andar_atual = andar_inicial;

        do {
            for (int j = 0; j < L; ++j) {
                // Se encontramos a chave e ela está ocupada
                if (andares[andar_atual][j].chave == chave && andares[andar_atual][j].estado == OCUPADO) {
                    std::cout << andar_atual << ":" << j << std::endl;
                    return;
                }
                // Condição de parada: se o jazigo está vazio, a busca para.
                if (andares[andar_atual][j].estado == VAZIO && andares[andar_atual][j].chave < chave) {
                    std::cout << "?:?" << std::endl;
                    return;
                }
            }
            andar_atual = (andar_atual + 1) % M;
        } while (andar_atual != andar_inicial);
        
        std::cout << "?:?" << std::endl; // Não encontrou após percorrer tudo
    }
};

int main() {
    // Otimização para leitura de dados, algo que você pode usar nos desafios do Iudex
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int M, L;
    std::cin >> M >> L;

    Cemiterio cemiterio(M, L);

    std::string comando;
    int chave;

    while (std::cin >> comando && comando != "END") {
        std::cin >> chave;
        if (comando == "ADD") {
            cemiterio.add(chave);
        } else if (comando == "REM") {
            cemiterio.rem(chave);
        } else if (comando == "QRY") {
            cemiterio.qry(chave);
        }
    }

    return 0;
}