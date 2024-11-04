#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
#include <string.h>

using namespace std;

#define V 6 // Número de vértices no gráfico

// Função auxiliar que retorna verdadeiro se houver um caminho da origem 's' para o sumidouro 't' na rede residual. Também preenche pai[] para armazenar o caminho
bool bfs(int grafoRes[V][V], int s, int t, int pai[]) {
    // Cria um array visitado e marca todos os vértices como não visitados
    bool visitado[V];
    memset(visitado, 0, sizeof(visitado));

    // Cria uma fila, insere o nó de origem e marca-o como visitado
    queue<int> q;
    q.push(s);
    visitado[s] = true;
    pai[s] = -1;

    //Loop BFS Padrão
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visitado[v] == false && grafoRes[u][v] > 0) {
                // Se encontramos um caminho para o sumidouro, podemos retornar verdadeiro
                if (v == t) {
                    pai[v] = u;
                    return true;
                }
                q.push(v);
                pai[v] = u;
                visitado[v] = true;
            }
        }
    }

    // Não conseguimos encontrar um caminho de origem para o sumidouro
    return false;
}

// Retorna o fluxo máximo de s para t no gráfico dado
int fordFulkerson(int grafo[V][V], int s, int t) {
    int u, v;

    // Cria um gráfico residual e preenche o gráfico residual com capacidades dadas no gráfico original, pois no gráfico residual grafoRes[i][j] indica a capacidade residual do aresta de i para j (se houver um aresta)
    int grafoRes[V][V]; // Gráfico residual onde grafoRes[i][j] indica capacidade residual do aresta de i para j
    for (u = 0; u < V; u++) {
        for (v = 0; v < V; v++) {
            grafoRes[u][v] = grafo[u][v];
        }
    }

    int pai[V]; // Array para armazenar o caminho

    int fTotal = 0; // Não há fluxo inicialmente

    // Aumenta o fluxo enquanto houver um caminho da origem para o sumidouro
    while (bfs(grafoRes, s, t, pai)) {
        // Encontra a capacidade residual mínima do caminho aumentante preenchido pela BFS
        int fluxo = INT_MAX;
        for (v = t; v != s; v = pai[v]) {
            u = pai[v];
            fluxo = min(fluxo, grafoRes[u][v]);
        }

        // Atualiza as capacidades residuais dos arestas e os reversos ao longo do caminho
        for (v = t; v != s; v = pai[v]) {
            u = pai[v];
            grafoRes[u][v] -= fluxo;
            grafoRes[v][u] += fluxo;
        }

        // Adiciona o fluxo do caminho ao fluxo total
        fTotal += fluxo;
    }

    // Retorna o fluxo total
    return fTotal;
}

// Exemplo de uso do algoritmo
int main() {
    // Grafo de exemplo
    int grafo[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    // Fonte é o vértice 0 e sumidouro é o vértice 5
    cout << "O fluxo máximo é: " << fordFulkerson(grafo, 0, 5) << endl;

    return 0;
}
