# Algoritmos-de-Grafos
Implementação de 4 algoritmos de grafos para a segunda avaliação da disciplina de Teoria dos Grafos.

As flags do terminal estão implementadas, os arquivos dos grafos serão como a primeira sugestão da lista, 1-indexed:
```
6 8
1 2 5
1 3 4
1 4 2
1 6 6
2 4 1
2 5 7
3 5 6
4 6 1
```
Nos algoritmos de Dijkstra e Bellman-Ford, caso o parâmetro ```-l``` não seja informado, o output será a distância mínima para todo vértice do grafo. Além disso, caso o parâmetro ```-s``` seja passado, também serão informados os vértices que compôem o caminho mínimo.

No algoritmo de Kruskal, o parâmetro ```-s``` printa as arestas da árvore em ordem crescente, caso não seja passado, somente o custo da árvore será printado.

O algoritmo de Bellman-Ford não implementa tratamento para ciclos negativos, e todos os algoritmos lêem o arquivo de entrada como um gafo simples(não direcionados)
