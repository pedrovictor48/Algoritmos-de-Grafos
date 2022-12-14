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
    LAST = -1;

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

struct Aresta {
    int u, v, peso;
    // com operador de menor para ser ordenavel:
};

void bellman(int origem, int n, vector<Aresta> &arestas, vector<int> &peso, vector<int> &path) {
    peso = vector<int>(n, INF);
    path = vector<int>(n, -1);
    peso[origem] = 0;
    path[origem] = origem;
    for(int i = 0; i < n - 1; i++) {
        for(Aresta e : arestas) {
            if(peso[e.u] < INF) {
                if(peso[e.v] > peso[e.u] + e.peso) {
                    peso[e.v] = peso[e.u] + e.peso;
                    path[e.v] = e.u;
                }
            }
        }
    }
}

vector<Aresta> ler_arestas(string caminho_arquivo, int &n) {
    ifstream arquivo;
    arquivo.open(caminho_arquivo);
    int m; arquivo >> n >> m;
    vector<Aresta> arestas(m);
    
    for(int i = 0; i < m; i++) {
        int u, v, peso; arquivo >> u >> v >> peso;
        u--, v--;
        arestas[i].u = u;
        arestas[i].v = v;
        arestas[i].peso = peso;
    }
    return arestas;
}

int main(int argc, char ** argv) {
    flags_terminal(argc, argv);

    //isso aqui é se o usuário informar output file
    if(OUT != "") freopen(OUT.c_str(), "w", stdout);

    if(HELP) help();
    int n;
    vector<Aresta> arestas = ler_arestas(IN, n);
    vector<int> path, peso;

    bellman(START - 1, n, arestas, peso, path);

    if(LAST == -1) {
        //printa tudo
        for(int i = 0; i < peso.size(); i++) {
            cout << i + 1 << ": " << peso[i] << " ";
        }
        cout << endl;
    }
    else cout << peso[LAST - 1] << endl;

    if(SOL) solucao(path, peso);
}