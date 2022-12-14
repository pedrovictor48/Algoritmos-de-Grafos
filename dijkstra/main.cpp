#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int INF = 1e6; // um numero grande que representa infinito (evitei INT_MAX por conta do overflow)

// implementacao dos arguementos
bool HELP, SOL;
int START, LAST;
string IN, OUT;

void flags_terminal(int argc, char ** argv) {
    HELP = SOL = false;
    IN = "grafo.txt";
    OUT = "";

    for(int i = 1; i < argc; i++) {
        //se o primeiro caractere é zero, ent é uma flag
        if(argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'h':
                    HELP = true;
                    break;
                case 'o':
                    OUT = string(argv[i + 1]);
                    break;
                case 'f':
                    IN = string(argv[i + 1]);
                    break;
                case 's':
                    SOL = true;
                    break;
                case 'i':
                    START = atoi(argv[i + 1]);
                    break;
                case 'l':
                    LAST = atoi(argv[i + 1]);
                    break;
            }
        }
        //se nao, é um valor para a flag i-1 que ja foi processado
    }
}

void help() {
    cout << "-h : mostra o help\n";
    cout << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n";
    cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada\n";
    cout << "-s : mostra a solução (em ordem crescente)\n";
    cout << "-i : vértice inicial (dependendo do algoritmo)\n";
    cout << "-l : vértice final (dependendo do algoritmo)\n";
    cout << "os valores padrões são 0 para o vértice inicial e final, grafo.txt para o grafo de entrada e saída no terminal\n";
}

void print_path(int u, vector<int> &path) {
    if(path[u] == u) {
        cout << u + 1;
        return;
    }
    print_path(path[u], path);
    cout << " -> " << u + 1;
}

void solucao(vector<int> &path, vector<int> &peso) {
    //no caso do dijkstra vou mostrar o caminho para cada vertice
    int n = path.size();
    for(int i = 0; i < n; i++) {
        if(i == START - 1) continue;
        cout << i + 1 << ": ";
        if(peso[i] < INF) {
            print_path(i, path);
            cout << " (" << peso[i] << ") \n";
        }
        else cout << "nao existe" << endl;
    }
}

void dijkstra(int origem, vector<vector<pair<int, int>>> &lista_adjacencia, vector<int> &peso, vector<int> &path) {
    int n = lista_adjacencia.size(); // numero de vertices, nós com rótulos 0-indexed
    peso = vector<int>(n, INF); // todos inicializados com INF exceto o origem:
    path = vector<int>(n, -1);
    peso[origem] = 0;
    path[origem] = origem;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, origem});

    while(!pq.empty()) {
        int vertice_atual = pq.top().second, peso_atual = pq.top().first;
        pq.pop();

        if(peso_atual > peso[vertice_atual]) {
            // nao vale a pena visitar, pois visitaremos adiante com menos peso
            continue;
        }

        // iterar vizinhos do nó atual
        for(pair<int, int> proximo : lista_adjacencia[vertice_atual]) {
            int proximo_vertice = proximo.first, peso_aresta = proximo.second;
            if(peso[vertice_atual] + peso_aresta < peso[proximo_vertice]) {
                // se achamos um peso total menor, atualize e adicione na fila
                path[proximo_vertice] = vertice_atual;
                peso[proximo_vertice] = peso[vertice_atual] + peso_aresta;
                pq.push({peso[proximo_vertice], proximo_vertice});
            }
        }
    }
}

vector<vector<pair<int, int>>> ler_grafo_simples(string caminho_arquivo) {
    ifstream arquivo;
    arquivo.open(caminho_arquivo);
    int n, m; arquivo >> n >> m;
    vector<vector<pair<int, int>>> lista_adjacencia(n);
    
    for(int i = 0; i < m; i++) {
        int u, v, peso; arquivo >> u >> v >> peso;
        // 1-indexed do usuario para 0-indexed do algoritmo
        lista_adjacencia[u - 1].push_back({v - 1, peso});
        lista_adjacencia[v - 1].push_back({u - 1, peso});
    }
    return lista_adjacencia;
}

int main(int argc, char ** argv) {
    flags_terminal(argc, argv);

    //isso aqui é se o usuário informar output file
    if(OUT != "") freopen(OUT.c_str(), "w", stdout);

    if(HELP) help();

    vector<vector<pair<int, int>>> adj = ler_grafo_simples(IN);
    vector<int> path, peso;

    dijkstra(START - 1, adj, peso, path);

    cout << peso[LAST - 1] << endl;

    if(SOL) solucao(path, peso);
}