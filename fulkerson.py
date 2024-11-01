from collections import deque

def bfs(residual_graph, source, sink, parent):
    visited = [False] * len(residual_graph)
    queue = deque([source])
    visited[source] = True
    
    while queue:
        u = queue.popleft()
        
        for v, capacity in enumerate(residual_graph[u]):
            if not visited[v] and capacity > 0:  # If not visited and there's capacity
                queue.append(v)
                visited[v] = True
                parent[v] = u
                if v == sink:
                    return True
    return False

def ford_fulkerson(graph, source, sink):
    residual_graph = [list(row) for row in graph]
    parent = [-1] * len(graph)
    max_flow = 0
    
    while bfs(residual_graph, source, sink, parent):
        path_flow = float('Inf')
        s = sink
        
        while s != source:
            path_flow = min(path_flow, residual_graph[parent[s]][s])
            s = parent[s]
        
        max_flow += path_flow
        v = sink
        
        while v != source:
            u = parent[v]
            residual_graph[u][v] -= path_flow
            residual_graph[v][u] += path_flow
            v = parent[v]
    
    return max_flow

# Exemplo de uso
graph = [
    [0, 16, 13, 0, 0, 0],
    [0, 0, 10, 12, 0, 0],
    [0, 4, 0, 0, 14, 0],
    [0, 0, 9, 0, 0, 20],
    [0, 0, 0, 7, 0, 4],
    [0, 0, 0, 0, 0, 0]
]

source = 0
sink = 5

print("O fluxo máximo é: ", ford_fulkerson(graph, source, sink))

"""
Explicação do Código:

1.Função BFS: A função bfs busca um caminho aumentante na rede residual usando uma busca em largura (BFS).
2.Ford-Fulkerson: A função ford_fulkerson encontra o fluxo máximo aplicando a BFS repetidamente para encontrar caminhos aumentantes e atualizar a rede residual.
3.Inicialização da Rede Residual: A rede residual é inicializada como uma cópia do grafo original.
4.Cálculo do Fluxo Máximo: O fluxo máximo é calculado somando o fluxo ao longo de cada caminho aumentante encontrado.
"""