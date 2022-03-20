//
// Created by Diana-Elena Stancu on 17/03/2022.
//
/*
    1. Implementați algoritmul lui Moore pentru un graf orientat neponderat (algoritm bazat pe Breath-first search,
    vezi cursul 2). Datele sunt citite din fisierul graf.txt. Primul rând din graf.txt conține numărul vârfurilor,
    iar următoarele rânduri conțin muchiile grafului. Programul trebuie să afiseze lanțul cel mai scurt dintr-un vârf
    (vârful sursa poate fi citit de la tastatura).
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define oo 1 << 30
using namespace std;
ifstream fin("graf.txt");

vector <int> Graph[100];
queue <int> Q;
int Parents[100];
int Dist[100];
int n, Source, Destination;

void read() {
    cout << "Nodurile sursa si destinatie: ";
    cin >> Source >> Destination;
    int x, y;
    fin >> n;
    while (fin >> x >> y) {
        Graph[x].push_back(y);//graf orientat
    }
/*    for (int i = 1; i <= n; i++) {
        for (auto x: Graph[i])
            cout << x << ' ';
        cout << endl;
    }*/
}

void Moore(int Source) {
    for (int i = 1; i <= n; i++) {
        Parents[i] = -1;
        Dist[i] = oo;
    }
    Dist[Source] = 0;
    Parents[Source] = 0;
    Q.push(Source);
    while (!Q.empty()) {
        int nodCurrent = Q.front();
        //cout << nodCurrent << endl;
        Q.pop();
        for (auto x : Graph[nodCurrent]) {
            if (Dist[x] == oo) {
                Dist[x] = Dist[nodCurrent] + 1;
                Parents[x] = nodCurrent;
                Q.push(x);
            }
        }
    }
/*    for (int i = 1; i <= n; i++)
        if (Dist[i] != oo) cout << i << ": " << Dist[i] << '\n';*/
}
void getParents(int nod) {
    if (Parents[nod] == 0) {
        cout << nod << ' ';
        return;
    }
    getParents(Parents[nod]);
    cout << nod << ' ';
}

void Path(int Source, int Destination) {
    int nod = Destination;
    if (Dist[nod] == oo) {
        cout << "Nu se poate ajunge la nodul dat.";
        return;
    }
    getParents(Destination);
}

int main() {
    read();
    Moore(Source);
    Path(Source, Destination);
    return 0;
}
