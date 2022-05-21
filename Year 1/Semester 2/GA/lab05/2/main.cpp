//
// Created by Diana-Elena Stancu on 20/05/2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#define VMAX 1005
using namespace std;
ifstream fin;
ofstream fout;

int V, E;
int Graph[1000][1000];
int GraphRez[1000][1000];
vector <int>  H(VMAX, 0);
vector <int> Exces(VMAX, 0);
int Source, Sink;
void citire() {

    fin >> V >> E;
    int x, y, c;
    while (fin >> x >> y >> c) {
        Graph[x][y] = c;
        GraphRez[x][y] = c;
    }
    Source = 0;
    Sink = V - 1;
}
void printExces() {
    cout << "\nExces\n";
    for (int i = 0; i < V; i++)
        cout << Exces[i] << ' ';
}
void printHeight() {
    cout << "\nH\n";
    for (int i = 0; i < V; i++)
        cout << H[i] << ' ';

}
void printGf() {
    cout << "\nGF\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            cout << GraphRez[i][j] << ' ';
        cout << endl;
    }
}
void init() {
    H[Source] = V;
    for (int i = 0; i < V; i++) {
        if (Graph[Source][i] != 0) {
            Exces[Source] -= Graph[Source][i];
            Exces[i] = Graph[Source][i];
            GraphRez[i][Source] = Graph[Source][i];
            Graph[Source][i] = 0;
        }
    }

}
void Pump(int u, int v) {

    int dFlow = min(Exces[u], GraphRez[u][v]);
    GraphRez[u][v] -= dFlow;
    GraphRez[v][u] += dFlow;
    Exces[u] -= dFlow;
    Exces[v] += dFlow;

}
void Inalt(int u) {
    int minH = 1 << 30;
    for (int v = 0; v < V; v++) {
        if (GraphRez[u][v] > 0)
            minH = min(minH, H[v]);
    }
    H[u] = 1 + minH;
}
pair <int, int> GivePumpV() {
    for (int u = 1; u < V - 1; u++) {
        if (Exces[u] > 0) {
            for (int v = 0; v < V; v++) {
                if (GraphRez[u][v] > 0 && H[u] == H[v] + 1)
                    return make_pair(u, v);
            }
        }
    }
    return make_pair(-1, -1);
}
int InaltareNod() {
    for (int u = 1; u < V - 1; u++) {
        if (Exces[u] > 0) {
            bool up = true;
            for (int v = 0; v < V && up; v++) {
                if (GraphRez[u][v] > 0)
                    if (H[u] > H[v])
                    {
                        up = false;

                    }
            }
            if (up == true) {
                return u;
            }
        }
    }
    return -1;
}
int main(int argc, char** argv)
{
    fin.open("1-in.txt");
    fout.open("out.txt");
    citire();
    init();
    pair<int, int> pump;
    while (true) {
        //  printExces(); printHeight(); printGf();
        pump = GivePumpV();
        if (pump.first != -1 && pump.second != -1)
        {
            Pump(pump.first, pump.second);
            continue;
        }
        int nodInalt = InaltareNod();
        if (nodInalt != -1)
        {
            Inalt(nodInalt);
            continue;
        }
        break;
    }
    printGf();
    fout << Exces[Sink];
}
