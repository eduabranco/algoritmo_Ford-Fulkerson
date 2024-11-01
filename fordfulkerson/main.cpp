#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;

#define V 6 // Número de vértices no gráfico

/* Função auxiliar que retorna verdadeiro se houver um caminho da origem 's' 
para o sumidouro 't' na rede residual. Também preenche parent[] para armazenar o caminho */
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    // Cria um array visitado e marca todos os vértices como não visitados
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // Cria uma fila, insere o nó de origem e marca-o como visitado
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                // Se encontramos um caminho para o sumidouro, podemos retornar verdadeiro
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // Não conseguimos encontrar um caminho de origem para o sumidouro
    return false;
}

// Retorna o fluxo máximo de s para t no gráfico dado
int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v;

    // Cria um gráfico residual e preenche o gráfico residual com capacidades
    // dadas no gráfico original, pois no gráfico residual rGraph[i][j] indica a capacidade
    // residual do aresta de i para j (se houver um aresta)
    int rGraph[V][V]; // Gráfico residual onde rGraph[i][j] indica capacidade residual do aresta de i para j
    for (u = 0; u < V; u++) {
        for (v = 0; v < V; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }

    int parent[V]; // Array para armazenar o caminho

    int max_flow = 0; // Não há fluxo inicialmente

    // Aumenta o fluxo enquanto houver um caminho da origem para o sumidouro
    while (bfs(rGraph, s, t, parent)) {
        // Encontra a capacidade residual mínima do caminho aumentante preenchido pela BFS
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Atualiza as capacidades residuais dos arestas e os reversos ao longo do caminho
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Adiciona o fluxo do caminho ao fluxo total
        max_flow += path_flow;
    }

    // Retorna o fluxo total
    return max_flow;
}

// Exemplo de uso do algoritmo
int main() {
    // Grafo de exemplo
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    // Fonte é o vértice 0 e sumidouro é o vértice 5
    cout << "O fluxo máximo é: " << fordFulkerson(graph, 0, 5) << endl;

    return 0;
}
