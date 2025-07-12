#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;              // ID do dispositivo
    long long wei;        // soma dos bytes transmitidos por este dispositivo
    long long subtreeSum; // soma total dos 'wei' em toda a subárvore
    long long rnLeft;     // soma dos 'wei' na subárvore esquerda
    int height;           // altura para balanceamento AVL

    Node* left;
    Node* right;

    Node(int k, long long w)
        : key(k), wei(w), subtreeSum(w), rnLeft(0),
          height(0), left(nullptr), right(nullptr) {}
};

// Função auxiliar para obter a altura de um nó ou -1 se nulo
inline int getHeight(Node* node) {
    return (node == nullptr) ? -1 : node->height;
}

// Retorna a soma da subárvore ou 0 se nulo
inline long long getSubtreeSum(Node* node) {
    return (node == nullptr) ? 0LL : node->subtreeSum;
}

// Recalcula height, subtreeSum, rnLeft
void updateNode(Node* node) {
    if (!node) return;

    // recalcular a altura
    int hl = getHeight(node->left);
    int hr = getHeight(node->right);
    node->height = max(hl, hr) + 1;

    // recalcular subtreeSum
    long long sumLeft  = getSubtreeSum(node->left);
    long long sumRight = getSubtreeSum(node->right);
    node->subtreeSum = node->wei + sumLeft + sumRight;

    // recalcular rnLeft = soma da subárvore esquerda
    node->rnLeft = sumLeft;
}

// Retorna fator de balanceamento (altura esquerda - altura direita)
int getBalance(Node* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Rotação simples para a direita
Node* rotateRight(Node* y) {
    Node* x = y->left;     // x é filho esquerdo de y
    Node* T2 = x->right;   // subárvore direita de x

    // Executa rotação
    x->right = y;
    y->left = T2;

    // Atualiza os dados dos nós que mudaram
    updateNode(y);
    updateNode(x);

    // x passa a ser a nova raiz do "subtree"
    return x;
}

// Rotação simples para a esquerda
Node* rotateLeft(Node* x) {
    Node* y = x->right;   // y é filho direito de x
    Node* T2 = y->left;   // subárvore esquerda de y

    // Executa rotação
    y->left = x;
    x->right = T2;

    // Atualiza os dados dos nós que mudaram
    updateNode(x);
    updateNode(y);

    // y passa a ser a nova raiz do "subtree"
    return y;
}

// Insere ou atualiza (se key já existir) na AVL
// Retorna o nó raiz (que pode ter mudado após rotações)
// addedBytes recebe quanto foi efetivamente adicionado ao wei total
Node* insertAVL(Node* root, int key, long long wei, long long* addedBytes) {
    if (root == nullptr) {
        // Criar novo nó
        *addedBytes = wei; // todo o wei é novo
        return new Node(key, wei);
    }

    if (key < root->key) {
        root->left = insertAVL(root->left, key, wei, addedBytes);
    }
    else if (key > root->key) {
        root->right = insertAVL(root->right, key, wei, addedBytes);
    }
    else {
        // key == root->key -> atualiza o 'wei' deste dispositivo
        root->wei += wei;
        *addedBytes = wei; // mesmo que já exista, adicionamos 'wei' ao total
    }

    // Recalcula altura e sums
    updateNode(root);

    // Verifica desbalanceamento
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key) {
        return rotateRight(root);
    }
    // Right Right Case
    if (balance < -1 && key > root->right->key) {
        return rotateLeft(root);
    }
    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    // Se não entrou em nenhum case de rotação, retorna o nó atual
    return root;
}

// Retorna a profundidade do nó com id = X (ou -1 se não existir)
int getDepth(Node* root, int X) {
    int depth = 0;
    Node* cur = root;

    while (cur != nullptr) {
        if (X == cur->key) {
            return depth;
        }
        else if (X < cur->key) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
        depth++;
    }
    return -1; // não encontrado
}

// Retorna o wei do nó com id = X (ou 0 se não existir)
long long getWEI(Node* root, int X) {
    Node* cur = root;
    while (cur != nullptr) {
        if (X == cur->key) {
            return cur->wei;
        }
        else if (X < cur->key) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return 0LL; // não encontrado
}

// Retorna a soma de 'wei' para todos os nós com ID < X
long long getRank(Node* root, int X) {
    long long sum = 0;
    Node* cur = root;

    while (cur != nullptr) {
        if (X <= cur->key) {
            // Não podemos somar o nó atual, pois cur->key >= X
            cur = cur->left;
        } else {
            // X > cur->key
            // Tudo na subárvore esquerda de 'cur' + o próprio 'cur' tem ID < X
            sum += cur->wei;
            sum += getSubtreeSum(cur->left); // soma do lado esquerdo
            cur = cur->right;
        }
    }
    return sum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node* root = nullptr;            // raiz da AVL
    long long totalBytes = 0;        // soma global de bytes transmitidos

    while (true) {
        string cmd;
        cin >> cmd;
        if (!cin) break;  // se acabar a entrada de forma abrupta

        if (cmd == "END") {
            break; // encerra
        }
        else if (cmd == "ADD") {
            long long W;
            int X;
            cin >> X >> W;

            long long added = 0;
            root = insertAVL(root, X, W, &added);
            // incrementa total global
            totalBytes += added;

            // imprimir total global
            cout << totalBytes << "\n";
        }
        else if (cmd == "WEI") {
            int X;
            cin >> X;
            long long w = getWEI(root, X);
            int depth = (w == 0) ? -1 : getDepth(root, X);

            // se não existe, w==0 mas poderia coincidir com X=0 e w=0? 
            // mas o enunciado diz: "se não existe, 0 -1". 
            // Então diferenciamos profundidade: se depth<0 => não existe
            if (depth < 0) {
                cout << "0 -1\n";
            } else {
                cout << w << " " << depth << "\n";
            }
        }
        else if (cmd == "RNK") {
            int X;
            cin >> X;
            long long rankVal = getRank(root, X);
            cout << rankVal << "\n";
        }
        else {
            // comando desconhecido, poderia tratar erro
            cerr << "Comando invalido: " << cmd << "\n";
            // ou apenas continuar
        }
    }

    return 0;
}
