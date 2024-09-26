import networkx as nx

def generate_random_graph(num_nodes, edge_prob, output_file):
    G = nx.erdos_renyi_graph(num_nodes, edge_prob)

    num_edges = G.number_of_edges()

    with open(output_file, "w") as f:
        f.write(f"p edge {num_nodes} {num_edges}\n")

        for u, v in G.edges():
            f.write(f"e {u + 1} {v + 1}\n")

generate_random_graph(1000, 0.005, "test.dimacs")