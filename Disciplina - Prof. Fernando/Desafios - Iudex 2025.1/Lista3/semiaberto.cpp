#include <iostream>
#include <string>

/*
 * Faz Enumeração dos estados possíveis de um jazigo.
 * Fundamental para o controle -> ocupação, remoção e a busca.
 */
enum EstadoJazigo { VAZIO, OCUPADO, REMOVIDO };

struct Jazigo {
    int chave = -1;
    EstadoJazigo estado = VAZIO;
};

/*
 * Representação do cemitério.
 * Gerencia a estrutura de dados e operações -> inserção, remoção e consulta.
 */
class Cemiterio {
private:
    Jazigo** andares;
    int M, L, corpos;

    /*
     * Função de hash.
     * Essencial para distribuir as chaves entre os andares.
     */
    int hash(int chave) const {
        return chave % M;
    }

    int encontrarPosicao(int andar_idx, int chave) {
        int esquerda = 0;
        int direita = L - 1;
        int pos = 0;

        int ocupados = 0;
        while(ocupados < L && andares[andar_idx][ocupados].estado == OCUPADO) {
            ocupados++;
        }
        direita = ocupados;

        while (esquerda < direita) {
            int meio = esquerda + (direita - esquerda) / 2;
            if (andares[andar_idx][meio].chave < chave) {
                esquerda = meio + 1;
            } else {
                direita = meio;
            }
        }
        return esquerda;
    }

    /*
     * Rehash: dobra o número de andares e reinserir todos os corpos.
     * Importante para garantir eficiência quando o cemitério está cheio.
     */
    void rehash() {
        Jazigo** andares_antigos = andares;
        int M_antigo = M;

        M = 2 * M + 1;
        corpos = 0;
        
        andares = new Jazigo*[M];
        for (int i = 0; i < M; ++i) {
            andares[i] = new Jazigo[L];
        }

        for (int i = 0; i < M_antigo; ++i) {
            for (int j = 0; j < L; ++j) {
                if (andares_antigos[i][j].estado == OCUPADO) {
                    int chave_atual = andares_antigos[i][j].chave;
                    int andar_inicial = hash(chave_atual);
                    int andar_destino = andar_inicial;

                    while(true) { // Loop para sondagem linear no novo array
                        int ocupados_no_andar = 0;
                        while(ocupados_no_andar < L && andares[andar_destino][ocupados_no_andar].estado == OCUPADO) {
                            ocupados_no_andar++;
                        }

                        if (ocupados_no_andar < L) {
                            int pos_insercao = encontrarPosicao(andar_destino, chave_atual);

                            for (int k = ocupados_no_andar; k > pos_insercao; --k) {
                                andares[andar_destino][k] = andares[andar_destino][k-1];
                            }

                            andares[andar_destino][pos_insercao].chave = chave_atual;
                            andares[andar_destino][pos_insercao].estado = OCUPADO;
                            corpos++;
                            break;
                        }
                        andar_destino = (andar_destino + 1) % M;
                    }
                }
            }
        }

        for (int i = 0; i < M_antigo; ++i) {
            delete[] andares_antigos[i];
        }
        delete[] andares_antigos;
    }

public:
    Cemiterio(int m, int l) : M(m), L(l), corpos(0) {
        andares = new Jazigo*[M];
        for (int i = 0; i < M; ++i) {
            andares[i] = new Jazigo[L];
        }
    }

    ~Cemiterio() {
        for (int i = 0; i < M; ++i) {
            delete[] andares[i];
        }
        delete[] andares;
    }

    /*
     * Adiciona um corpo ao cemitério.
     * Bloco central para inserção ordenada e tratamento de colisões.
     */
    void add(int chave) {
        if (corpos >= M * L) {
            rehash();
        }

        int andar_inicial = hash(chave);
        int andar_atual = andar_inicial;

        do {
            int ocupados_no_andar = 0;
            while(ocupados_no_andar < L && (andares[andar_atual][ocupados_no_andar].estado == OCUPADO || andares[andar_atual][ocupados_no_andar].estado == REMOVIDO)) {
                ocupados_no_andar++;
            }
            
            if (ocupados_no_andar < L) {
                int pos_insercao = encontrarPosicao(andar_atual, chave);
                
                for (int k = ocupados_no_andar; k > pos_insercao; --k) {
                    andares[andar_atual][k] = andares[andar_atual][k-1];
                }

                andares[andar_atual][pos_insercao].chave = chave;
                andares[andar_atual][pos_insercao].estado = OCUPADO;
                corpos++;
                
                std::cout << andar_atual << ":" << pos_insercao << std::endl;
                return;
            }
            
            andar_atual = (andar_atual + 1) % M;
        } while (andar_atual != andar_inicial);
    }
    
    /*
     * Remove um corpo do cemitério.
     * Importante para manter a integridade da estrutura e permitir reinserção.
     */
    void rem(int chave) {
        int andar_inicial = hash(chave);
        int andar_atual = andar_inicial;

        do {
            for (int j = 0; j < L; ++j) {
                if (andares[andar_atual][j].chave == chave && andares[andar_atual][j].estado == OCUPADO) {
                    andares[andar_atual][j].estado = REMOVIDO;
                    corpos--;
                    std::cout << andar_atual << ":" << j << std::endl;
                    return;
                }
                if (andares[andar_atual][j].estado == VAZIO) {
                    std::cout << "?:?" << std::endl;
                    return;
                }
            }
            andar_atual = (andar_atual + 1) % M;
        } while (andar_atual != andar_inicial);

        std::cout << "?:?" << std::endl;
    }

    /*
     * Consulta por um corpo no cemitério.
     * Essencial para busca eficiente e resposta rápida.
     */
    void qry(int chave) {
        int andar_inicial = hash(chave);
        int andar_atual = andar_inicial;

        do {
            for (int j = 0; j < L; ++j) {
                if (andares[andar_atual][j].chave == chave && andares[andar_atual][j].estado == OCUPADO) {
                    std::cout << andar_atual << ":" << j << std::endl;
                    return;
                }
                if (andares[andar_atual][j].estado == VAZIO) {
                    std::cout << "?:?" << std::endl;
                    return;
                }
            }
            andar_atual = (andar_atual + 1) % M;
        } while (andar_atual != andar_inicial);
        
        std::cout << "?:?" << std::endl;
    }
};

/*
 * Função principal.
 * Responsável por inicializar o cemitério e processar os comandos de entrada.
 */
int main() {
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