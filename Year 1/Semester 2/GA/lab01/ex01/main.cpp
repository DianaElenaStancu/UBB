#include <iostream>
#include <fstream>
#include <vector>
#define MAX 101
#define INF 100001
using namespace std;
ifstream fin("in.txt");
/*
  1) Conversie lista de muchii a grafului neorientat => matrice de adiacenta
    Conversie matrice de adiacenta => matrice de incidenta

  2) Fie un graf reprezentat sub o anumita forma (graful este citit dintr-un fisier). Sa se rezolve:
    1. sa se determine nodurile izolate dintr-un graf.
    2. sa se determine daca graful este regular.
    3. sa se determine daca graful este conex.
    4. sa se determine matricea distantelor.

*/
int n;
int adjMatrix[MAX][MAX], incMatrix[MAX][MAX], grad[MAX], distMatrix[MAX][MAX], visited[MAX];

void readGraphFromFile() {
    int i, j, x, y;
    fin >> n;
    while(fin >> x >> y){
        ++grad[x];
        ++grad[y];
        adjMatrix[x][y] = adjMatrix[y][x] = 1;
    }

    cout << "File -> Matrice de adiacenta\n";
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            cout << adjMatrix[i][j] << ' ';
        cout << endl;
    }
    cout << "-------------------\n";
}

void convertAdjMatrixToIncMatrix() {
    int muchie = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            if (adjMatrix[i][j] == 1) {
                muchie++;
                incMatrix[i][muchie] = 1;
                incMatrix[j][muchie] = 1;
            }
        }

    cout << "Matrice de adiacenta -> Matrice de incidenta  " << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= muchie; j++)
            cout << incMatrix[i][j] << ' ';
        cout << endl;
    }
    cout << "-------------------\n";
}
void outputIsolatedNodes() {
    cout << "1) Nodurile izolate sunt: ";
    int i; bool exist = false;
    for (i = 1; i <= n; i++) {
        if (grad[i] == 0) {
            exist = true;
            cout << i << ' ';
        }
    }
    if (!exist)
        cout << "nu exista";
    cout << "\n-------------------\n";
}
bool isRegularGraph() {
    int i;
    for (i = 1; i < n; i++) {
        if (grad[i] != grad[i + 1])
            return false;
    }
    return true;
}

void createDistanceMatrix() {
    int i, j, k;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
        {
            if(i == j)
                distMatrix[i][j] = 0;
            else if(adjMatrix[i][j] != 1)
                distMatrix[i][j] = INF;
            else distMatrix[i][j] = 1;
        }

    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                if (distMatrix[i][k] != INF && distMatrix[k][j] != INF)
                    if (distMatrix[i][j] > distMatrix[i][k] + distMatrix[k][j])
                        distMatrix[i][j] = distMatrix[i][k] + distMatrix[k][j];

    cout << "4) Matricea distantelor este: " << '\n';
    for (i = 1; i <= n; i ++)
    {
        for (j = 1; j <= n; j++)
            if (distMatrix[i][j] == INF)
                cout << "INF" << ' ';
            else
                cout << distMatrix[i][j] << ' ';
        cout << '\n';
    }
}
void DFS(int x)
{
    int i;
    visited[x] = 1;
    for (i = 1; i <= n; i++)
        if(adjMatrix[x][i] && visited[i] == 0)
            DFS(i);
}
bool isConex() {
    DFS(1);
    for(int i = 1; i <= n; i++)
        if(visited[i] == 0)
            return 0;
    return 1;
}
using namespace std;
int main() {
    cout << "EX1\n";
    readGraphFromFile();
    convertAdjMatrixToIncMatrix();


    cout << "EX2\n";
    outputIsolatedNodes();
    if (isRegularGraph())
        cout << "2) Graful este regular";
    else
        cout << "2) Graful NU este regular";
    cout << "\n-------------------\n";

    if (isConex())
        cout << "3) Graful este conex";
    else
        cout << "3) Graful NU este conex";

    cout << "\n-------------------\n";

    createDistanceMatrix();
    return 0;
}
