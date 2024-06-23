from graphviz import Digraph

dot = Digraph()

# Adicionando nós
dot.node('a', 'a')
dot.node('b', 'b')
dot.node('x', 'x = a + 1')
dot.node('y', 'y = x + b')
dot.node('z', 'z = y * 2')

# Adicionando arestas
dot.edge('a', 'x')
dot.edge('b', 'y')
dot.edge('x', 'y')
dot.edge('y', 'z')

# Renderizando o grafo
dot.render('dynamic_slicing_example', format='png')
