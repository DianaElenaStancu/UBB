//
// Created by Diana-Elena Stancu on 04.12.2023.
//

#ifndef LAB4_PPD_SECV_H
#define LAB4_PPD_SECV_H
#include <ostream>
#include <fstream>
#include <iostream>
#include "SimpleLinkedList.h"
using namespace std;

void secvential() {
    auto start = std::chrono::high_resolution_clock::now();

    int t = 5, p = 10;

    SimpleLinkedList list = SimpleLinkedList();
    SimpleLinkedList black_list = SimpleLinkedList();
    vector<string> in_f = input_files(t, p);
    for (auto& file: in_f) {
        ifstream fin(file);
        int id, score;
        while(fin >> id >> score) {
            if (score != -1) {
                if (black_list.find(id) != nullptr) {
                    continue;
                }
                list.add(id, score);
            } else {
                list.remove(id);
                black_list.add(id);
            }
        }

        fin.close();
    }

    ofstream fout("../Clasament.txt");
    fout << list;
    fout.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Execution Time: " << duration.count() << " milliseconds" << '\n' << std::flush;
}
#endif //LAB4_PPD_SECV_H
