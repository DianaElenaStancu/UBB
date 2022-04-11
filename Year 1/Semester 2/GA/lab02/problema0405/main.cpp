//
// Created by Diana-Elena Stancu on 17/03/2022.
//
/*
4. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de algoritmul BFS și distanța față de vârful sursă
 (arborele descoperit).

5. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de apelul recursiv al procedurii DFS_VISIT(G, u)
 (apadurea descoperită de DFS).

 */
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
ifstream fin("graph.txt");
int n;
int oo = 1<<30;
vector <int> G[150];
int source;
void read() {
    fin >> n;
    int x, y;
    while(fin >> x >> y) {
        G[x].push_back(y);
    }
    cout << "Nodul sursa: ";
    cin >> source;
}

void BFS(int s)
{
    cout << "Ordinea descoperirii nodurilor de catre algoritmul BFS: " << s << ' ';
    vector <char> color;
    vector <int> dist;
    for (int i = 0; i <= n; i++) {
        color.push_back('a');
        dist.push_back(oo);
    }
    color[s] = 'g';
    dist[s] = 0;
    queue <int> Q;
    Q.push(s);
    while(!Q.empty()) {
        int nodCurrent = Q.front();
        Q.pop();
        for (auto x: G[nodCurrent]) {
            if (color[x] == 'a') {
                color[x] = 'g';
                cout << x << ' ';
                dist[x]  = dist[nodCurrent] + 1;
                Q.push(x);
            }
        }
        color[nodCurrent] = 'n';
    }
    cout << "\nDistantele fata de nodul sursa " << s << " sunt: " << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        if (dist[i] == oo)
             cout << "-" << endl;
        else
            cout << dist[i] << endl;
    }
}
void DFS_VISIT(vector <pair <int, char>>& Attr, vector <pair<int,int>>& Time, int s, int& time) {
    cout << s << ' ';
    time++;
    Time[s].first = time;
    Attr[s].second = 'g';
    for (auto x: G[s]) {
        if (Attr[x].second == 'a') {
            Attr[x].first = s;
            DFS_VISIT(Attr, Time, x, time);
        }
    }
    Attr[s].second = 'n';
    time++;
    Time[s].second = time;
}

void DFS(int source, vector <pair <int, char>>& Attr, vector <pair<int,int>>& Time) {
    cout << "Ordinea descoperirii nodurilor de catre algoritmul DFS: ";
    for (int i = 0; i <=  n; i++) {
        Attr.push_back(make_pair(-1, 'a'));
        Time.push_back(make_pair(0, 0));
    }
    int time = 0;
    for (int i = 1; i <= n; i++) {
        if (Attr[i].second == 'a') {
            DFS_VISIT(Attr, Time, i, time);
        }
    }
}


int main() {
    vector <pair <int, char>> Attr; vector <pair<int,int>> Time;
    read();
    BFS(source);
    DFS(source, Attr, Time);
    return 0;
}
