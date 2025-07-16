#include <iostream>
#include <climits> // Para usar INT_MAX, que representará o infinito

void subirNoHeap(NoHeap heap[], int i)
{
  while (i > 0 && heap[(i - 1) / 2].distancia > heap[i].distancia)
  {
    // Troca com o pai
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
    // Troca com o menor filho
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

// --- Fim das Funções do Min-Heap ---

// Função principal do Dijkstra
void dijkstra(int Q, NoAdj *adj[], int origem, int dist[])
{
  // Inicializa as distâncias como "infinito"
  for (int i = 0; i < Q; ++i)
  {
    dist[i] = INT_MAX;
  }
  dist[origem] = 0;

  // Fila de Prioridade
  NoHeap minHeap[Q];
  int tamanhoHeap = Q;
  for (int i = 0; i < Q; ++i)
  {
    minHeap[i] = {i, (i == origem) ? 0 : INT_MAX};
  }

   while (tamanhoHeap > 0)
  {
    NoHeap noAtual = extrairMin(minHeap, &tamanhoHeap);
    int u = noAtual.vertice;

    // Itera pelos vizinhos de 'u'
    NoAdj *vizinho = adj[u];
    while (vizinho != nullptr)
    {
      int v = vizinho->destino;
      int pesoUV = vizinho->peso;

      if (dist[u] != INT_MAX && dist[u] + pesoUV < dist[v])
      {
        dist[v] = dist[u] + pesoUV;

        // Atualiza a distância na fila de prioridade
        // Para simplificar, adicionamos o vértice novamente com a nova prioridade.
        // A versão correta usaria decrease-key.
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
  // Para acelerar a entrada/saída em C++
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int Q, R, N;
  std::cin >> Q >> R >> N;

  Aresta todasAsRuas[R];
  for (int i = 0; i < R; ++i)
  {
    std::cin >> todasAsRuas[i].origem >> todasAsRuas[i].destino >> todasAsRuas[i].peso;
    todasAsRuas[i].ativa = true; // Todas começam ativas
  }

  // Armazena os eventos para processar um por um
  // Vamos simplificar e processar em tempo real
  for (int i = 0; i < N; ++i)
  {
    int tipo, A, B;
    std::cin >> tipo >> A >> B;

    if (tipo == 1)
    { // Evento de alagamento
      // Encontra a rua e a desativa
      for (int j = 0; j < R; ++j)
      {
        if (todasAsRuas[j].origem == A && todasAsRuas[j].destino == B)
        {
          todasAsRuas[j].ativa = false;
          break; // Supondo que existe no máximo um caminho direto
        }
      }
    }
      // 2. Rodar Dijkstra
      int distancias[Q];
      dijkstra(Q, adj, A, distancias);

      // 3. Imprimir o resultado
      if (distancias[B] == INT_MAX)
      {
        std::cout << -1 << std::endl;
      }
      else
      {
        std::cout << distancias[B] << std::endl;
      }

      // 4. Limpar a memória da lista de adjacência
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