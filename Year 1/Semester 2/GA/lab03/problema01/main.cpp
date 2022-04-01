//
// Created by Diana-Elena Stancu on 1/04/2022.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream fin("00-in.txt");
ofstream fout("00-out.txt");

//declarari
int n, m, start;
const int NMAX = 100005;
const int oo = 1<<30;
vector <pair <int, int>> G[NMAX];
int D[NMAX];
bool InCoada[NMAX];


struct compara {
    bool operator()(int x, int y)
    {
        return D[x] > D[y];
    }
};

priority_queue <int, vector <int> , compara> Coada;

void Citeste() {
    fin >> n >> m >> start;
    for (int i = 1; i <= m; i++) {
        int x, y, c;
        fin >> x >> y >> c;
        G[x].push_back(make_pair(y, c));
    }
}

void Dijkstra(int start) {
    //initializez distantele cu INF
    for (int i = 0; i < n; i++)
        D[i] = oo;

    //distanta de la nodul de start la el insusi este 0
    D[start] = 0;

    //adaugam nodul de start in coada si il marcam in vectorul InCoada
    Coada.push(start);
    InCoada[start] = true;

    while(!Coada.empty()) {
        //preluam ultimul nod din coada
        int nodCurent = Coada.top();
        Coada.pop();

        InCoada[nodCurent] = false;
        for (int i = 0; i < G[nodCurent].size(); i++) {
            int vecin = G[nodCurent][i].first;
            int cost = G[nodCurent][i].second;
            //daca am gasit un drum cu un cost mai mic decat cel actual atunci
            //actualizam noul cost si adaugam in coada vecinul
            if (D[nodCurent] + cost < D[vecin]) {
                D[vecin] = D[nodCurent] + cost;
                if (!InCoada[vecin]) {
                    Coada.push(vecin);
                    InCoada[vecin] = true;
                }
            }
        }
    }
}

void Afiseaza() {
    for (int i = 0; i < n; i++) {
        if (D[i] != oo)
            fout << D[i] << ' ';
        else
            fout << "INF ";
    }
}

int main() {
    Citeste();
    Dijkstra(start);
    Afiseaza();

    fin.close();
    fout.close();
}
