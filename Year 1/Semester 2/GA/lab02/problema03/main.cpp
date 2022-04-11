//
// Created by Diana-Elena Stancu on 17/03/2022.
//
/*
    3. Să se scrie un program care găsește o soluție pentru unul din următoarele labirinturi: labirint_1.txt,
    labirint_2.txt, labirint_cuvinte.txt. Pentru labirintul 1 si 2 punctul de pornire este indicat de litera S
    și punctul de oprire este indicat de litera F, spre deosebire de labirintul 1 și 2, labirintul 3 nu are
    o soluție unică.
 */
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
using namespace std;
ifstream fin("labirint_2.txt");
pair <int, int> source, destination;
vector <string> matrix;
int width;
int n;

void read() {
    string linie;
    while(getline(fin, linie)) {
        width = linie.size();
        matrix.push_back(linie);
        ++n;
    }
}

void getSourceDestination() {
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix[i].size(); j++)
                if (matrix[i][j] == 'S') {
                source.first = i;
                source.second = j;
            } else if (matrix[i][j] == 'F') {
                destination.first = i;
                destination.second = j;
            }
    //cout << source.first << ' ' << source.second << endl;
    //cout << destination.first << ' ' << destination.second << endl;
}

bool isInMatrix(int i, int j, int n, int m) {
    return (i >= 0 && i < n && j >= 0 && j < m);
}

void constructPath() {
    queue <pair<int, int> > Q;
    Q.push(make_pair(source.first, source.second));

    int** viz = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        viz[i] = (int*) malloc(sizeof(int) * width);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < width; j++)
            viz[i][j] = 0;

    map < pair <int, int>, pair<int, int> > Inainte;
    viz[source.first][source.second] = 1;
/*
    map < int, int> M2;
    M2.insert( pair<int, int> (2, 3));*/

    pair <int, int> Zero{ 0,0 };
    Inainte.insert( make_pair(source,Zero) );
//    pair <int, int> p = Inainte[source];
    pair <int, int > Current;
    int dx[] = { 1, -1, 0 , 0 };
    int dy[] = { 0, 0, 1 , -1 };
    //          dreapta stanga jos sus
    int i_nou, j_nou;
    //Q.push(make_pair(source.first, source.second));
    while (!Q.empty()) {

        Current = Q.front();
        //cout << Current.first << ' ' << Current.second << endl;
        Q.pop();
        for (int d = 0; d < 4; d++) {
            i_nou = Current.first + dx[d];
            j_nou = Current.second + dy[d];
            if(isInMatrix(i_nou,j_nou, n, width)){ // daca e in matrice
                // daca n am mai trecut pe acolo  si este diferit de 1
                if (viz[i_nou][j_nou] == 0 && matrix[i_nou][j_nou] != '1')
                {
                    viz[i_nou][j_nou] = viz[Current.first][Current.second] + 1;
                    pair <int, int> p1 = make_pair(i_nou, j_nou);
                    Q.push(p1);
                    Inainte.insert(make_pair(p1, Current)); // pun aici perechi ca sa reconstruiesc drumul
                    if (matrix[i_nou][j_nou] == 'F')
                    {
                        cout << "AM AJUNS LA DESTINATIE\n";
                        break;
                    }
                }
                // daca am dat peste 'F' ma opresc si afisez recursiv
            }
        }
    }
    //constructPath(Inainte, Destination, viz, Matrix);
    cout << endl << endl;
    pair <int, int> Vecin{ Inainte[destination] };
    while (Inainte[Vecin] != Zero) {
        matrix[Vecin.first][Vecin.second] = 'X';
        Vecin = Inainte[Vecin];

    }
    cout << endl << endl;
    pair <int, int> vecin{ Inainte[destination] };
    while (Inainte[vecin] != Zero) {
        matrix[vecin.first][vecin.second] = 'X';
        vecin = Inainte[vecin];

    }

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
        free(viz[i]);
    free(viz);
}

int main() {
    read();
    getSourceDestination();
    constructPath();

    return 0;
}
