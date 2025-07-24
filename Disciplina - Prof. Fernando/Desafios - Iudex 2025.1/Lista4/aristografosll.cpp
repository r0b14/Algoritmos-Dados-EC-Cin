#include <iostream>
#include <climits>

struct Aresta
{
  int origem;
  int destino;
  int peso;
  bool ativa;
};

struct NoAdj
{
  int destino;
  int peso;
  NoAdj *proximo;
};

struct NoHeap
{
  int vertice;
  int distancia;
};

// Funções de manipulação de Min-Heap para fila de prioridade do Dijkstra
void subirNoHeap(NoHeap heap[], int i)
{
  while (i > 0 && heap[(i - 1) / 2].distancia > heap[i].distancia)
  {
    NoHeap temp = heap[i];
    heap[i] = heap[(i - 1) / 2];
    heap[(i - 1) / 2] = temp;
    i = (i - 1) / 2;
  }
}

void descerNoHeap(NoHeap heap[], int tamanho, int i)
{
  int menor = i;
  int esquerda = 2 * i + 1;
  int direita = 2 * i + 2;

  if (esquerda < tamanho && heap[esquerda].distancia < heap[menor].distancia)
  {
    menor = esquerda;
  }
  if (direita < tamanho && heap[direita].distancia < heap[menor].distancia)
  {
    menor = direita;
  }

  if (menor != i)
  {
    NoHeap temp = heap[i];
    heap[i] = heap[menor];
    heap[menor] = temp;
    descerNoHeap(heap, tamanho, menor);
  }
}

NoHeap extrairMin(NoHeap heap[], int *tamanho)
{
  NoHeap min = heap[0];
  heap[0] = heap[*tamanho - 1];
  (*tamanho)--;
  descerNoHeap(heap, *tamanho, 0);
  return min;
}

// Função principal do Dijkstra
void dijkstra(int Q, NoAdj *adj[], int origem, int dist[])
{
  for (int i = 0; i < Q; ++i)
  {
    dist[i] = INT_MAX;
  }
  dist[origem] = 0;

  NoHeap minHeap[Q];
  int tamanhoHeap = Q;
  for (int i = 0; i < Q; ++i)
  {
    minHeap[i] = {i, (i == origem) ? 0 : INT_MAX};
  }

  tamanhoHeap = 1;
  minHeap[0] = {origem, 0};

  int posNoHeap[Q];
  for (int i = 0; i < Q; ++i)
    posNoHeap[i] = -1;
  posNoHeap[origem] = 0;

  while (tamanhoHeap > 0)
  {
    NoHeap noAtual = extrairMin(minHeap, &tamanhoHeap);
    int u = noAtual.vertice;

    NoAdj *vizinho = adj[u];
    while (vizinho != nullptr)
    {
      int v = vizinho->destino;
      int pesoUV = vizinho->peso;

      if (dist[u] != INT_MAX && dist[u] + pesoUV < dist[v])
      {
        dist[v] = dist[u] + pesoUV;

        minHeap[tamanhoHeap] = {v, dist[v]};
        subirNoHeap(minHeap, tamanhoHeap);
        tamanhoHeap++;
      }
      vizinho = vizinho->proximo;
    }
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int Q, R, N;
  std::cin >> Q >> R >> N;

  Aresta todasAsRuas[R];
  for (int i = 0; i < R; ++i)
  {
    std::cin >> todasAsRuas[i].origem >> todasAsRuas[i].destino >> todasAsRuas[i].peso;
    todasAsRuas[i].ativa = true;
  }

  for (int i = 0; i < N; ++i)
  {
    int tipo, A, B;
    std::cin >> tipo >> A >> B;

    if (tipo == 1)
    {
      for (int j = 0; j < R; ++j)
      {
        if (todasAsRuas[j].origem == A && todasAsRuas[j].destino == B)
        {
          todasAsRuas[j].ativa = false;
          break;
        }
      }
    }
    else
    {
      NoAdj *adj[Q];
      for (int k = 0; k < Q; ++k)
        adj[k] = nullptr;

      for (int j = 0; j < R; ++j)
      {
        if (todasAsRuas[j].ativa)
        {
          NoAdj *novoNo = new NoAdj{todasAsRuas[j].destino, todasAsRuas[j].peso, adj[todasAsRuas[j].origem]};
          adj[todasAsRuas[j].origem] = novoNo;
        }
      }

      int distancias[Q];
      dijkstra(Q, adj, A, distancias);

      if (distancias[B] == INT_MAX)
      {
        std::cout << -1 << std::endl;
      }
      else
      {
        std::cout << distancias[B] << std::endl;
      }

      for (int k = 0; k < Q; ++k)
      {
        NoAdj *atual = adj[k];
        while (atual != nullptr)
        {
          NoAdj *temp = atual;
          atual = atual->proximo;
          delete temp;
        }
      }
    }
  }

  return 0;
}