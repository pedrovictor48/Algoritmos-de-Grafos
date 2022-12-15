# Algoritmos-de-Grafos

* Aluno: Pedro Victor Alexandre Ferreira Santos  
* Professor: Rian Gabriel Pinheiro
* Teoria dos Grafos 2022.1 (Ciência Da Computação)

Implementação de 4 algoritmos de grafos para a segunda avaliação da disciplina de Teoria dos Grafos.
1. Dijkstra
2. Bellman-Ford
3. Kruskal (com DSU)
4. Floyd-Warshall

Para executar, basta dar um ```make``` no diretório do algoritmo e em seguida executar o binário com o nome dele com as flags desejadas.

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

O algoritmo de Bellman-Ford e o de Floyd-Warshall não implementam tratamento para casos com ciclos negativos, e todos os algoritmos lêem o arquivo de entrada como um gafo simples (não direcionados)
