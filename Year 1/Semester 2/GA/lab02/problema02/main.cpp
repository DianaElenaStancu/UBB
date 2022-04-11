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
using namespace std;
ifstream fin("graf.txt");

bool G[101][101];
int n;

void read() {
    fin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fin >> G[i][j];
}

void RF() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (G[i][j] == 0)
                    G[i][j] = (G[i][k] && G[k][j]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << G[i][j] << ' ';
        cout << endl;
    }
}

int main() {
    read();
    RF();
    return 0;
}
