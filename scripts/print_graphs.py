import networkx as nx
import random
import matplotlib.pyplot as plt

def read_dimacs_col(path):
    G = nx.Graph()

    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()

            if not line or line.startswith("c"):
                continue

            parts = line.split()

            if parts[0] == "p":
                n = int(parts[2])
                G.add_nodes_from(range(1, n + 1))

            elif parts[0] == "e":
                u = int(parts[1])
                v = int(parts[2])
                G.add_edge(u, v)

    return G

def create_color_list(n_nodes):
    colors = []

    for _ in range(n_nodes):
        colors.append(random.randint(0, 8))
    
    return colors

def grid_positions(n_rows, n_cols):
    pos = {}
    node = 1
    for r in range(n_rows):
        for c in range(n_cols):
            pos[node] = (c, -r)
            node += 1
    return pos

def draw_graph(path):
    G = read_dimacs_col(path)
    pos = nx.kamada_kawai_layout(G)
    # pos = nx.spring_layout(G)
    
    sqrt = len(G.nodes) ** 0.5
    sqrt = int(sqrt) 
    pos = grid_positions(6, 6)
    

    color = create_color_list(len(G.nodes))

    plt.figure(figsize=(10, 10))
    nx.draw_networkx_edges(G, pos, edge_color="gray", alpha=0.25, width=0.8)
    nx.draw_networkx_nodes(G, pos, node_color=color, node_size=90)
    
    plt.axis("off")
    plt.tight_layout()
    plt.show()

draw_graph("instances/queen6_6.col.txt")