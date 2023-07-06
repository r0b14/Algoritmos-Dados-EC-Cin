## InsertionSort

### Descrevendo Algoritmo

Este algoritmo ordenada os elementos de forma crescente *(ñ-decrescente)*. *A [n0<n1<n2...<n-1]*

**1.** É preciso usar 2 iteradores, onde 1° *(i)* fica responsável por percorrer todo o vetor e o 2° *(j)* fica responsável por selecionar o elemento chave e inserir no vetor em ordenação.

```c
void insertionSort(int arr[], int n) {
    int i, chave, j;
    for (i = 1; i < n; i++) { // iterador 1
        chave = arr[i];
        j = i - 1; // iterador 2
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j]; // clonando o valor para a sua próx posição
            j = j - 1;
        }
        arr[j + 1] = chave; // inserindo elemento chave na posição ordenada
    }
}
```
**2.** A operação de ordenação vai ter sempre um elemento chave, que vai ficar responsável como o elemento que vai ser a "base" da comparação com os outros elementos.

**3.** Os elementos que estão sendo ordenados sempre serão clonados para a sua próxima posição *[j+1]*. 

    1- 5 8 1 2 4
    2- 5 8 8 2 4 (chave = 1) (8 clonado)
    3- 5 5 8 2 4 (chave = 1) (5 clonado)
    4- 1 5 8 2 4 (ordenado 1)