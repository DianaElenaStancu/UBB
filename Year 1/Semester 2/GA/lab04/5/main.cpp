//
// Created by Diana-Elena Stancu on 06/05/2022.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("1-in.txt");
ofstream fout("a.out");
class Muchie {
public:
    int x, y, w;
    Muchie(int x, int y, int w) :x{ x }, y{ y }, w{ w }{};
    bool operator<(const Muchie& ot) { return this->w < ot.w; };

};

vector < Muchie > Graph;

bool cmp(Muchie m, Muchie n) {
    return m.w < n.w;
}

int V, E;
void citire() {
    fin >> V >> E;
    for (int i = 1; i <= E; i++) {
        int x, y, w;
        fin >> x >> y >> w;
        Muchie m(x, y, w);
        Graph.push_back(m);
    }
    sort(Graph.begin(), Graph.end(), cmp);
}
int find_root(int i, vector<int> roots) {
    int rad = i;
    while (roots[rad] != rad) {
        rad = roots[rad];
    }
    return rad;
}
void Kruskal() {
    vector <int> size;
    vector <int> roots;
    int CostTotal=0;
    vector <Muchie> APM;
    for (int i = 0; i < V; i++) {
        size.push_back(1);
        roots.push_back(i);
    }
    for (int i = 0; i < Graph.size(); i++) {
        int p = find_root(Graph[i].x, roots);
        int q = find_root(Graph[i].y, roots);
        if ( p != q )
        {
            Muchie m(Graph[i].x, Graph[i].y, Graph[i].w);
            APM.push_back(m);
            CostTotal += Graph[i].w;
            if (size[p] < size[q]) {
                roots[p] = q;
                size[q] += size[p];
            }
            else {
                roots[q] = p;
                size[p] += size[q];
            }
        }
    }
    fout << CostTotal << '\n';
    fout << V - 1 << '\n';
    for (const auto& m : APM) {
        fout << m.x << ' ' << m.y << '\n';
    }
}
int main(int argc, char ** argv) {
    //fin.open(argv[1], "1-in.txt");
    //fout.open(argv[2], "a.out");
    citire();
    Kruskal();
    fin.close();
    fout.close();
}

