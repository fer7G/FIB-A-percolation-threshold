import networkx as nx
import matplotlib.pyplot as plt

fileName = "test.dimacs"

def generate_random_graph(num_nodes, edge_prob):
    G = nx.erdos_renyi_graph(num_nodes, edge_prob)
    return G

def generate_malla(x, y):
    G = nx.grid_2d_graph(x, y)
    return G

def draw_graph_malla(G):
    pos = dict((n, n) for n in G.nodes())  # Posiciones de los nodos en la cuadrícula
    nx.draw(G, pos=pos, with_labels=True, node_size=500, node_color="lightblue")
    plt.show()

def draw_graph_erdos_renyi(G):
    plt.figure(figsize=(8, 8))  # Ajustar el tamaño de la figura
    nx.draw(G, with_labels=True, node_color="skyblue", node_size=700, edge_color="gray", font_weight='bold')
    plt.show()

def write_graph_to_file(output_file, G, num_nodes):
    # Crear un mapeo de tuplas (en el caso de una malla) a enteros
    mapping = {node: idx + 1 for idx, node in enumerate(G.nodes())}
    G = nx.relabel_nodes(G, mapping)  # Relabel nodes to integers

    with open(output_file, "w") as f:
        f.write(f"p edge {num_nodes} {G.number_of_edges()}\n")

        for u, v in G.edges():
            f.write(f"e {u} {v}\n")


tipo = input("Introduce un tipo de grafo, malla o erdos-renyi: ")

if tipo == "malla":
    n, m = map(int, input("Introduce la altura y anchura de la malla (separados por un espacio): ").split())
    graph = generate_malla(n, m)
    draw_graph_malla(graph)
    write_graph_to_file(fileName, graph, graph.number_of_nodes())

else:
    n = int(input("Introduce el número de nodos: "))
    p = float(input("Introduce la probabilidad de las aristas: "))
    graph = generate_random_graph(n, p)
    draw_graph_erdos_renyi(graph)
    write_graph_to_file(fileName, graph, graph.number_of_nodes())