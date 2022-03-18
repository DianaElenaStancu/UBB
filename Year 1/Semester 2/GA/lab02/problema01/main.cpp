//
// Created by Diana-Elena Stancu on 17/03/2022.
//
/*
    2. Sa se determine închiderea transitivă a unui graf orientat. (Închiderea tranzitivă poate fi reprezentată ca
    matricea care descrie, pentru fiecare vârf în parte, care sunt vârfurile accesibile din acest vârf. Matricea
    inchiderii tranzitive arată unde se poate ajunge din fiecare vârf.) ex. figura inchidere_tranzitiva.png -
    pentru graful de sus se construieste matricea de jos care arata inchiderea tranzitiva.
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
