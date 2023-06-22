#include <iostream>
#include <string>

class No {
public:
    int jogada;
    No* tentativa;

    No(int jogada) {
        this->jogada = jogada;
        this->tentativa = nullptr;
    }
};

class Petris1 {
public:
    No* head = nullptr;


    void inserirNo(Petris1* pilha, int jogada) {
        No* no = new No(jogada);
        int chamarRemover = 0;
        if (this->head == nullptr) {
            this->head = no;
        }
        else {
            if (head->jogada == jogada) {
                chamarRemover = 1;
            }
            no->tentativa = head;
            head = no;
        }
        if (chamarRemover == 1) {
            removerNo(pilha);
            removerNo(pilha);
            chamarRemover = 0;
        }
    }

    void removerNo(Petris1* pilha) {
        No* atual = pilha->head;
        if (pilha->head == nullptr) {
            std::cout << "A lista esta vazia." << std::endl;
        }
        else {
            pilha->head = atual->tentativa;
        }
    }

    void printar(Petris1* pilha) {
        No* aux = pilha->head;
        while (aux != nullptr) {
            std::cout << aux->jogada << std::endl;
            aux = aux->tentativa;
        }
    }

    int QuantDePedrasRestantes() {
        int contador = 0;
        No* aux = this->head;
        if (aux != nullptr) {
            while (aux != nullptr) {
                contador++;
                aux = aux->tentativa;
            }
        }
        else {
            contador = 0;
        }
        return contador;
    }

    int pedraDoTopo() {
        No* aux = this->head;
        No* pedraSobra = this->head;
        int pedraDoTopo;
        if (aux != nullptr) {
            pedraDoTopo = pedraSobra->jogada;
        }
        else {
            pedraDoTopo = -1;
        }
        return pedraDoTopo;
    }
};

int main() {
    std::string pedraS;
    int jogada = 0, p;
    Petris1* jogo = new Petris1();

    std::cin >> p;
    int* restoDePedras = new int[p];
    int* pedraDoTopo = new int[p];

    for (int cont = 0; cont < p; cont++) {
        jogo = new Petris1();
        while (true) {
            std::cin >> pedraS;
            if (pedraS == "END") {
                pedraDoTopo[cont] = jogo->pedraDoTopo();
                restoDePedras[cont] = jogo->QuantDePedrasRestantes();
                break;
            }
            else {
                jogada = std::stoi(pedraS);
                jogo->inserirNo(jogo, jogada);
            }
        }
    }

    for (int cont = 0; cont < p; cont++) {
        std::cout << "caso " << cont << ": " << restoDePedras[cont] << " " << pedraDoTopo[cont] << std::endl;
    }

    delete[] restoDePedras;
    delete[] pedraDoTopo;
    delete jogo;

    return 0;
}
