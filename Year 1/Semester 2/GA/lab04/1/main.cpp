//
// Created by Diana-Elena Stancu on 06/05/2022.
//


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("1-in.txt");
ofstream fout("a.out");
int N;
vector <int> T;
int root;
void citire() {
    fin >> N;
    for (int i = 0; i < N; i++)
    {
        int x;
        fin >> x;
        T.push_back(x);
        if (x == -1)
            root = i;
    }
}
bool eFrunza(int nod, vector <int> T, vector <bool> viz) {
    for (size_t j = 0; j < T.size(); j++)
        if (T[j] == nod && viz[j] == false) // nod are copil pe j
            return false;
    return true;

}

vector<int> codarePrufer() {
    vector <int> K;
    vector <bool> viz(N, false);
    int NrNodes = N;
    while (NrNodes > 1) {
        for (int i = 0; i < N; i++) {
            if (i != root && eFrunza(i, T, viz) && viz[i] == false) { // daca as baga un priority_queue(N^2 ->NlogN)
                //cout << T[i] << ' ';
                K.push_back(T[i]); // predecesorul lui i = Tatal lui i
                // elimin nodul i; marchez ca vizitat
                viz[i] = true;
                NrNodes--;
                break;
            }
        }
    }
    return K;
}
int main(int argc, char** argv) {
    //fin.open(argv[1], ios::in);
    //fout.open(argv[2], ios::out);
    citire();
    vector<int> K = codarePrufer();
    fout << K.size() << '\n';
    for (auto x : K)
        fout << x << ' ';
    fin.close();
    fout.close();
}
