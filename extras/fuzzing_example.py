import networkx as nx
import matplotlib.pyplot as plt

def create_fuzzing_graph():
    # Criação do grafo
    G = nx.DiGraph()

    # Adicionando nós (componentes do fuzzer)
    G.add_node("Input Generator")
    G.add_node("Executor")
    G.add_node("Monitor")
    G.add_node("Logger")

    # Adicionando arestas (fluxo de dados)
    G.add_edge("Input Generator", "Executor", label="Generates input data")
    G.add_edge("Executor", "Monitor", label="Executes input data")
    G.add_edge("Monitor", "Logger", label="Detects and logs anomalies")
    G.add_edge("Executor", "Logger", label="Logs execution data")

    return G

def draw_fuzzing_graph(G):
    pos = nx.spring_layout(G)  # Layout do grafo

    # Desenhando os nós
    nx.draw_networkx_nodes(G, pos, node_size=2000, node_color='lightblue')

    # Desenhando as arestas
    nx.draw_networkx_edges(G, pos, edgelist=G.edges(), edge_color='gray', arrows=True)

    # Adicionando rótulos aos nós
    nx.draw_networkx_labels(G, pos, font_size=12, font_family="sans-serif")

    # Adicionando rótulos às arestas
    edge_labels = nx.get_edge_attributes(G, 'label')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=10)

    plt.title("Fuzzing Data Flow Graph")
    plt.show()

if __name__ == "__main__":
    G = create_fuzzing_graph()
    draw_fuzzing_graph(G)
