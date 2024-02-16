//
// Created by Diana-Elena Stancu on 21.11.2023.
//

#ifndef LAB4_GEN_H
#define LAB4_GEN_H
#include <fstream>
#include <random>
using namespace std;

// 100 de participanti
// 10 probleme
// 5 tari (concursuri)
// fisier de forma RezultateCi_Pj
void generate () {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(-1,100);
    for (int ti = 1; ti <= 5; ti++) {
        for (int pi = 1; pi <= 10; pi++) {
            string fisier = "../data/RezultateC" + to_string(ti) + "_P" + to_string(pi)  + ".txt";
            ofstream fout(fisier);
            for (int ci = 1; ci <= 100; ci++) {
                int punctaj = distribution(gen);
                fout << ci << " " << punctaj << endl;
            }
            fout.close();
        }
    }
}

#endif //LAB4_GEN_H
