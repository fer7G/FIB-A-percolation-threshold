import networkx as nx
import matplotlib.pyplot as plt
import random
import math
from netket.graph import Kagome


def generate_kagome_graph(x, y):
    G = Kagome(extent=[x, y])
    print(f"Kagome graph created with {G.n_nodes} nodes.")
    return G.to_networkx()


def generate_malla(x, y):
    G = nx.grid_2d_graph(x, y)
    return G


def generate_random_geometric_graph(num_nodes):
    O1 = 1  # Start with O1 = 1

    is_connected = False  # Initialize the connectivity flag
    ln = math.log(num_nodes)
    pi = math.pi * num_nodes
    while not is_connected:
        # Calculate critical radius r using the formula
        r = math.sqrt((ln + O1) / (pi))

        # Generate random positions for the nodes
        pos = {i: (random.gauss(0, 2), random.gauss(0, 2)) for i in range(num_nodes)}
        G = nx.random_geometric_graph(num_nodes, r, pos=pos)  # Generate the graph

        # Check if the graph is connected
        is_connected = nx.is_connected(G)

        if not is_connected:
            O1 = O1 * 2  # Square O1 to increase the radius more quickly if not connected

    return G


def write_graph_to_file(output_file, G, num_nodes):
    # Map nodes to integers
    mapping = {node: idx + 1 for idx, node in enumerate(G.nodes())}
    G = nx.relabel_nodes(G, mapping)  # Relabel nodes to integers

    with open(output_file, "w") as f:
        f.write(f"p edge {num_nodes} {G.number_of_edges()}\n")
        for u, v in G.edges():
            f.write(f"e {u} {v}\n")


def save_graph_as_png(graph, output_image):
    pos = nx.spring_layout(graph)  # Use spring layout for a visually appealing layout
    plt.figure(figsize=(8, 8))
    nx.draw(graph, pos, with_labels=True, node_size=300, node_color="lightblue", font_size=10, font_weight="bold")
    plt.savefig(output_image)
    plt.close()


def generate_graph(tipo, params, fileName, guardar, guardar_png):
    """
    Generate a graph based on the given parameters and save it if specified.
    
    Args:
    - tipo (str): Type of graph ("m" for malla, "k" for kagome, "g" for geometric).
    - params (tuple): Parameters needed to generate the graph.
    - fileName (str): The base file name to save the graph.
    - guardar (bool): Whether to save the graph to a file.
    - guardar_png (bool): Whether to save the graph as a PNG image.
    """

    if tipo == "m":
        n, m = params
        graph = generate_malla(n, m)
        if guardar:
            write_graph_to_file(fileName, graph, graph.number_of_nodes())
        if guardar_png:
            save_graph_as_png(graph, fileName + ".png")

    elif tipo == "k":
        n, m = params
        graph = generate_kagome_graph(n, m)
        if guardar:
            write_graph_to_file(fileName, graph, graph.number_of_nodes())
        if guardar_png:
            save_graph_as_png(graph, fileName + ".png")

    elif tipo == "g":
        n = params[0]
        graph = generate_random_geometric_graph(n)
        if guardar:
            write_graph_to_file(fileName, graph, graph.number_of_nodes())
        if guardar_png:
            save_graph_as_png(graph, fileName + ".png")
    
    return graph


# Main interaction encapsulated in a function
def main():
    tipo = input("Introduce un tipo de grafo, malla(m), kagome(k) o geométrico(g): ")
    guardar = input("¿Desea guardar el grafo generado? (y/n): ").lower() == 'y'
    guardar_png = input("¿Desea guardar el grafo como PNG? (y/n): ").lower() == 'y'
    fileName = input("Introduce el nombre del archivo de salida: ")

    if tipo == "m":
        n, m = map(int, input("Introduce la altura y anchura de la malla (separados por un espacio): ").split())
        generate_graph(tipo, (n, m), fileName, guardar, guardar_png)

    elif tipo == "k":
        n, m = map(int, input("Introduce la altura y anchura de la malla Kagome (separados por un espacio): ").split())
        generate_graph(tipo, (n, m), fileName, guardar, guardar_png)

    elif tipo == "g":
        n = int(input("Introduce el número de nodos: "))
        generate_graph(tipo, (n,), fileName, guardar, guardar_png)


if __name__ == "__main__":
    main()