#include <stdio.h>

#define MAX_ROUTES 100000

typedef struct {
    int origem;
    int destino;
    int custo;
} Rota;

static int aeroportoPai[1000000];
static int nivelAeroporto[1000000];
static Rota rotas[MAX_ROUTES];

static void mesclar(Rota *arr, int esquerda, int meio, int direita) {
    int tam1 = meio - esquerda + 1;
    int tam2 = direita - meio;
    
    Rota esquerdaArr[tam1], direitaArr[tam2];
    
    for (int i = 0; i < tam1; i++) {
        esquerdaArr[i] = arr[esquerda + i];
    }
    for (int j = 0; j < tam2; j++) {
        direitaArr[j] = arr[meio + 1 + j];
    }
    
    int i = 0, j = 0, k = esquerda;
    
    while (i < tam1 && j < tam2) {
        if (esquerdaArr[i].custo <= direitaArr[j].custo) {
            arr[k] = esquerdaArr[i];
            i++;
        } else {
            arr[k] = direitaArr[j];
            j++;
        }
        k++;
    }
    
    while (i < tam1) {
        arr[k] = esquerdaArr[i];
        i++;
        k++;
    }
    
    while (j < tam2) {
        arr[k] = direitaArr[j];
        j++;
        k++;
    }
}

static void ordenarRotas(Rota *arr, int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = (esquerda + direita) / 2;
        ordenarRotas(arr, esquerda, meio);
        ordenarRotas(arr, meio + 1, direita);
        mesclar(arr, esquerda, meio, direita);
    }
}

int main() {
    int numAeroportos, numRotas;
    scanf("%d %d", &numAeroportos, &numRotas);
    
    for (int i = 0; i < numRotas; i++) {
        scanf("%d %d %d", &rotas[i].origem, &rotas[i].destino, &rotas[i].custo);
    }
    
    ordenarRotas(rotas, 0, numRotas - 1);
    
    for (int i = 0; i < numAeroportos; i++) {
        aeroportoPai[i] = i;
        nivelAeroporto[i] = 0;
    }

    auto encontrarAeroporto = [&](int x) {
        while (aeroportoPai[x] != x) {
            aeroportoPai[x] = aeroportoPai[aeroportoPai[x]];
            x = aeroportoPai[x];
        }
        return x;
    };

    auto unirAeroportos = [&](int x, int y) {
        int raizX = encontrarAeroporto(x);
        int raizY = encontrarAeroporto(y);
        if (raizX != raizY) {
            if (nivelAeroporto[raizX] < nivelAeroporto[raizY]) {
                aeroportoPai[raizX] = raizY;
            } else if (nivelAeroporto[raizX] > nivelAeroporto[raizY]) {
                aeroportoPai[raizY] = raizX;
            } else {
                aeroportoPai[raizY] = raizX;
                nivelAeroporto[raizX]++;
            }
        }
    };
    
    long long custoTotal = 0;
    
    for (int i = 0; i < numRotas; i++) {
        int origem = rotas[i].origem;
        int destino = rotas[i].destino;
        int custo = rotas[i].custo;
        
        if (encontrarAeroporto(origem) != encontrarAeroporto(destino)) {
            unirAeroportos(origem, destino);
            custoTotal += custo;
        }
    }
    
    printf("%lld\n", custoTotal);
    
    return 0;
}
