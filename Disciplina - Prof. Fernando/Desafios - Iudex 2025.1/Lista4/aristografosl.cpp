#include <iostream>
#include <algorithm> // Para usar std::min

using namespace std;

// Constantes baseadas nos limites do problema
const int MAX_Q = 300;
const int INFINITO = 1e9; // Representa ausência de caminho

// Matriz para guardar as distâncias mínimas entre todas as quadras
int distancias[MAX_Q][MAX_Q];

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int Q, R, N;
  cin >> Q >> R >> N;

  // Inicializa a matriz de distâncias
  for (int i = 0; i < Q; i++)
  {
    for (int j = 0; j < Q; j++)
    {
      distancias[i][j] = (i == j) ? 0 : INFINITO;
    }
  }

  // Lê as ruas iniciais e atualiza a matriz de distâncias
  for (int i = 0; i < R; i++)
  {
    int A, B, M;
    cin >> A >> B >> M;
    distancias[A][B] = min(distancias[A][B], M);
  }

  // Algoritmo de Floyd-Warshall para calcular as menores distâncias
  for (int k = 0; k < Q; k++)
  {
    for (int i = 0; i < Q; i++)
    {
      for (int j = 0; j < Q; j++)
      {
        if (distancias[i][k] != INFINITO && distancias[k][j] != INFINITO)
        {
          distancias[i][j] = min(distancias[i][j], distancias[i][k] + distancias[k][j]);
        }
      }
    }
  }

  // Processa os eventos
  for (int ev = 0; ev < N; ev++)
  {
    int tipo;
    cin >> tipo;

    if (tipo == 1)
    { // Adiciona uma nova rua
      int U, V, M;
      cin >> U >> V >> M;

      if (M < distancias[U][V])
      {
        distancias[U][V] = M;

        for (int i = 0; i < Q; i++)
        {
          for (int j = 0; j < Q; j++)
          {
            if (distancias[i][U] != INFINITO && distancias[V][j] != INFINITO)
            {
              long long novo_custo = (long long)distancias[i][U] + M + distancias[V][j];
              if (novo_custo < distancias[i][j])
              {
                distancias[i][j] = novo_custo;
              }
            }
          }
        }
      }
    }
    else
    { // Consulta a menor distância entre dois pontos
      int A, B;
      cin >> A >> B;

      cout << (distancias[A][B] == INFINITO ? -1 : distancias[A][B]) << "\n";
    }
  }

  return 0;
}