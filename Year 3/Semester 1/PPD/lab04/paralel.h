//
// Created by Diana-Elena Stancu on 05.12.2023.
//

#ifndef LAB4_PPD_PARALEL_H
#define LAB4_PPD_PARALEL_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <assert.h>
#include "SimpleLinkedList.h"
using namespace std;

mutex mutex_q, mutex_freaders, mutex_all, mutex_list, mutex_black_list;
queue <pair<int, int>> results;
int freaders_count, all_count;


void reader(int start, int end, vector<string>& in_f, SimpleLinkedList& list, int threads_count) {
    for (int i = start; i < end; i++) {
        int id, score;
        ifstream fin(in_f[i]);
        while(fin >> id >> score) {
            mutex_q.lock();
            results.push(make_pair(id, score));
            mutex_q.unlock();
        }
        fin.close();
    }

    mutex_freaders.lock();
    freaders_count++;
    mutex_freaders.unlock();

    mutex_all.lock();
    all_count++;
    mutex_all.unlock();

    if (start == 0) {//first reader
        bool cond = true;
        while(cond) {
            mutex_all.lock();
            if (all_count == threads_count){
                cond = false;
            }
            mutex_all.unlock();
        }

        ofstream fout("../Clasament.txt");
        fout << list;
        fout.close();

        //check answers
        ifstream fin_ans("../Clasament.txt");
        ifstream fin_truth("../truth");
        int id1, score1, id2, score2;
        while(fin_ans >> id1 >> score1 && fin_truth >> id2 >> score2) {
            assert(id1 == id2);
            assert(score1 == score2);
        }

    }
}

void writer(int readers_count, SimpleLinkedList& list, SimpleLinkedList& black_list) {
    bool cond = true;
    while (cond) {
        pair<int, int> result;
        mutex_q.lock();
        bool empty = results.empty();
        if(!empty) {
            result = results.front();
            results.pop();
        }
        mutex_q.unlock();

        if (!empty) {
            if (result.second != -1) {
                mutex_black_list.lock();
                Node* found = black_list.find(result.first);
                mutex_black_list.unlock();
                if (found == nullptr) {
                    mutex_list.lock();
                    list.add(result.first, result.second);
                    mutex_list.unlock();
                }
            } else {
                mutex_list.lock();
                list.remove(result.first);
                mutex_list.unlock();
                mutex_black_list.lock();
                black_list.add(result.first);
                mutex_black_list.unlock();
            }
        }

        mutex_freaders.lock();
        if (freaders_count == readers_count && empty) {
            cond = false;
        }
        mutex_freaders.unlock();
    }

    mutex_all.lock();
    all_count++;
    mutex_all.unlock();
}

void paralel(int readers_count, int writers_count) {
    auto start_time = std::chrono::high_resolution_clock::now();

    int t = 5, p = 10;

    SimpleLinkedList list = SimpleLinkedList();
    SimpleLinkedList black_list = SimpleLinkedList();
    vector<string> in_f = input_files(t, p);


    vector<thread> readers;
    int cat = in_f.size() / readers_count;
    int rest = in_f.size() % readers_count;
    int start = 0, end = 0;
    for (int i = 0; i < readers_count; i++) {
        end += cat;
        if (rest > 0) {
            ++end;
            --rest;
        }
        readers.emplace_back(reader, start, end, ref(in_f), ref(list), readers_count + writers_count);
        start = end;
    }

    vector<thread> writers;
    for (int i = 0; i < writers_count; i++) {
        writers.emplace_back(writer, readers_count, ref(list), ref(black_list));
    }


    for (int i = 0; i < readers_count; i++) {
        readers[i].join();
    }

    for (int i = 0; i < writers_count; i++) {
        writers[i].join();
    }


    ofstream fout("../Clasament.txt");
    fout << list;
    fout.close();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    cout << "Execution Time: " << duration.count() << " milliseconds" << '\n' << std::flush;
}

#endif //LAB4_PPD_PARALEL_H
