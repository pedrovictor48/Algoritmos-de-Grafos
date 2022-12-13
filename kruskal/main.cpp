#include <bits/stdc++.h>
#include <cstdio>
#include <future>

using namespace std;

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


// coisas do dsu:

void make_set(int elemento, vector<int> &pai, vector<int> &rank) {
    pai[elemento] = elemento;
    rank[elemento] = 0;
}

int find_set(int elemento, vector<int> &pai, vector<int> &rank) {
    if(pai[elemento] == elemento) return elemento;
    pai[elemento] = find_set(pai[elemento], pai, rank);
    return pai[elemento];
}

void union_sets(int set1, int set2, vector<int> &pai, vector<int> &rank) {
    // ter certeza que é raiz
    set1 = find_set(set1, pai, rank);
    set2 = find_set(set2, pai, rank);

    if(set1 != set2) {
        // unir sempre o menor no maior, entao:
        if(rank[set1] > rank[set2]) swap(set1, set2);
        pai[set1] = set2;

        if(rank[set1] == rank[set2]) rank[set2]++;
    }
}

// agora vou implementar uma struct que representa
// uma aresta para facilitar as coisas

struct Aresta {
    int u, v, peso;
    // com operador de menor para ser ordenavel:
    bool operator<(Aresta const& other) {
        return peso < other.peso;
    }
};

//funcao de comparacao para printar ordenado dps
bool comparacao(Aresta a, Aresta b) {
    if(a.u == b.u) return a.v < b.v;
    return a.u < b.u;
}

void print_arvore(vector<Aresta> tree) {
    sort(tree.begin(), tree.end(), comparacao);
    for(Aresta e : tree) cout << "(" << e.u << "," << e.v << ") ";
    cout << endl;
}

vector<Aresta> kruskal(int n, vector<Aresta> &arestas, int &custo) {
    vector<Aresta> tree;
    custo = 0;

    //todo vertice de 0 a n - 1 tera seu set inicialmente
    vector<int> pai(n), rank(n);
    for(int i = 0; i < n; i++) make_set(i, pai, rank);

    //primeiro, ordenar as arestas por peso
    sort(arestas.begin(), arestas.end());
    //depois, ir escolhendo, se u e v não estao no mesmo set
    for(Aresta e : arestas) {
        if(find_set(e.u, pai, rank) != find_set(e.v, pai, rank)) {
            //escolha essa aresta:
            tree.push_back(e);
            union_sets(e.u, e.v, pai, rank);
            custo += e.peso;
        }
    }
    return tree;
}

vector<Aresta> ler_arestas(string caminho_arquivo, int &n) {
    ifstream arquivo;
    arquivo.open(caminho_arquivo);
    int m; arquivo >> n >> m;
    vector<Aresta> arestas(m);
    
    for(int i = 0; i < m; i++) {
        int u, v, peso; arquivo >> u >> v >> peso;
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
    int custo = 0, n;
    vector<Aresta> arestas = ler_arestas(IN, n);
    
    vector<Aresta> tree = kruskal(n, arestas, custo);

    cout << "custo: " << custo << endl;

    if(SOL) print_arvore(tree);
}