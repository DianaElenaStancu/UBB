//
// Created by Diana-Elena Stancu on 06/05/2022.
//

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
using namespace std;
int main(int argc, char**argv) {
    ifstream fin("1-in.txt");
    ofstream fout("a.out");
    deque <int> K;
    int N, M;

    fin >> M;
    for (int i = 1; i <= M; i++) {
        int x;
        fin >> x;
        K.push_back(x);
    }


    N = M + 1;
    vector <int> T(N,-1);
    for (int i = 1; i <= M; i++) {
        int x = K.front();
        int y;
        bool gasit;
        for (y = 0; y <= M; y++)
        {
            // daca y nu se gaseste in K ies
            gasit = false;
            for (auto it = K.begin(); it != K.end() && !gasit; it++)
            {
                int aux = *it;
                if (aux == y)
                {
                    gasit = true;
                    break;
                }
            }
            // y nu s a gasit , adaug muchia(x,y) si trec la urmatorul pas
            if (gasit == false)
            {
                T[y] = x;
                K.pop_front();
                K.push_back(y);
                break;
            }
        }

    }
    fout << T.size() << endl;
    for (const auto& x : T)
        fout << x << ' ';
    return 0;
}