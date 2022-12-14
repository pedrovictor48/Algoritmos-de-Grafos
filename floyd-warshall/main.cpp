#include <bits/stdc++.h>

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
    START = -1;

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
    cout << "os valores padrões são 0 para o vértice inicial, grafo.txt para o grafo de entrada e saída no terminal\n";
}

void floyd(int n, vector<vector<int>> &matriz_adj) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matriz_adj[i][k] < INF && matriz_adj[k][j] < INF)
                    matriz_adj[i][j] = min(matriz_adj[i][j], matriz_adj[i][k] + matriz_adj[k][j]); 
            }
        }
    }
}

void solucao(int n, vector<vector<int>> &matriz_adj) {
    for(int i = 0; i < n; i++) {
        cout << "iniciando do vértice " << i + 1 << ": ";
        for(int j = 0; j < n; j++) {
            cout << j + 1 << ":" << matriz_adj[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> ler_matriz(string caminho_arquivo, int &n) {
    ifstream arquivo;
    arquivo.open(caminho_arquivo);
    int m; arquivo >> n >> m;
    vector<vector<int>> matriz_adj(n, vector<int>(n, INF));

    //enchendo matriz_adj[i][i] de 0
    for(int i = 0; i < n; i++) matriz_adj[i][i] = 0;
    
    for(int i = 0; i < m; i++) {
        int u, v, peso; arquivo >> u >> v >> peso;
        u--, v--;
        // 1-indexed do usuario para 0-indexed do algoritmo
        matriz_adj[u][v] = matriz_adj[v][u] = peso;
    }
    return matriz_adj;
}

int main(int argc, char **argv) {
    flags_terminal(argc, argv);

    //isso aqui é se o usuário informar output file
    if(OUT != "") freopen(OUT.c_str(), "w", stdout);

    if(HELP) help();
    int n;
    vector<vector<int>> matriz_adj = ler_matriz(IN, n);

    floyd(n, matriz_adj);

    if(START != -1) {
        if (LAST == -1) {
            for(int i = 0; i < n; i++) {
                cout << i + 1 << ":" << matriz_adj[START - 1][i] << " ";
            }
            cout << endl;
        }
        else cout << matriz_adj[START - 1][LAST - 1] << endl;

        if(SOL) solucao(n, matriz_adj);
    }
    else solucao(n, matriz_adj);

}