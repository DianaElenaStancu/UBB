#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#define VMAX 1005
using namespace std;
ifstream fin;
ofstream fout;
int V, E;
int Source, Sink;
int G[VMAX][VMAX];
int Gf[VMAX][VMAX];
vector <int>  parent;
void citire() {
    fin >> V >> E;
    int x, y, cp;
    while (fin >> x >> y >> cp)
    {
        G[x][y] = cp;
        Gf[x][y] = cp;
    }
    Source = 0;
    Sink = V - 1;
}
bool isPath() {
    vector <bool> viz(V);
    for (int i = 0; i < V; i++)
        parent.push_back(-1);
    queue  <int> Q;
    Q.push(Source);
    viz[Source] = true;
    while (!Q.empty()) {
        int nod_curent = Q.front();
        Q.pop();
        for (int i = 0; i < V; i++) {
            if (Gf[nod_curent][i] > 0 && !viz[i]) {
                viz[i] = true;
                Q.push(i);
                parent[i] = nod_curent;
                if (i == Sink)
                    return true;
            }
        }
    }
    return false;
}
int Ford_Fulkerson() {
    /* Initializare flux cu 0
    * cat timp exista o cale reziduala in graful rezidual Gf
    *	creste fluxul f de pe  path
    * return f;
    */
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            Gf[i][j] = G[i][j];  // graful rezidual e identic cu cel initial
    int max_flow = 0;
    // capacitatea rezdiuala cf = CapMuchie(u,v) - flow, u,v e Edges
    //       flow , v,u  e edges
    //							0 else
    while (isPath())
    {
        // merg pe vecinii pana la sink si gasesc un min_flow
        // in graful rezidual - daca am muchia u, v ->  Gf[u,v] -= min_flow   + Gf[v,u] += min_flow ( am pus flow pe backEdge)
        // max_flow += min_flow
        int nod = Sink;
        int min_flow = 1 << 30;
        while (parent[nod] != -1) {
            min_flow = min(Gf[parent[nod]][nod], min_flow);
            nod = parent[nod];
        }
        nod = Sink;
        while (nod != Source) {
            Gf[parent[nod]][nod] -= min_flow;
            Gf[nod][parent[nod]] += min_flow;
            nod = parent[nod];
        }
        max_flow += min_flow;

    }
    return max_flow;
}
int main(int argc, char** argv)
{
    fin.open(argv[1]);
    fout.open(argv[2]);
    citire();
    int max_flow = Ford_Fulkerson();
    fout << max_flow;
    return 0;
}
