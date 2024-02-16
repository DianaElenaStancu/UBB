//
// Created by Diana-Elena Stancu on 16.12.2023.
//

// thread 1: 1 100
// thread 2: 1 -1
//if (score != -1) {                      // thread 1
//    if (black_list.find(id) == false) { // 1.
//        list.update(id, score);         // 4.
//    }
//} else {                                 // thread 2
//    black_list.add(id);                 // 2.
//    list.remove(id);                    // 3.
//}


#ifndef LAB5_PPD_PARALEL_H
#define LAB5_PPD_PARALEL_H
#include "SimpleLinkedList.h"
#include "Queue.h"
#include <queue>
#include <assert.h>
#include <map>
#include "my_barrier.h"
#define MAX 50

mutex mutex_q;
Queue <pair<int, int>> results;


void checkAnswers(){
    //check answers
    ifstream fin_ans("../Clasament.txt");
    ifstream fin_truth("../truth");
    int id1, score1, id2, score2;
    while(fin_ans >> id1 >> score1 && fin_truth >> id2 >> score2) {
        assert(id1 == id2);
        assert(score1 == score2);
    }
}

void reader(int start, int end, vector<string>& in_f, SimpleLinkedList& list, my_barrier& b, my_barrier& br) {
    for (int i = start; i < end; i++) {
        int id, score;
        ifstream fin(in_f[i]);
        while(fin >> id >> score) {
            //mutex_q.lock();
            results.push(make_pair(id, score));
            //mutex_q.unlock();
        }
        fin.close();
    }

    br.wait();

    if(start == 0) {
        results.stop();
    }

    b.wait();

    if(start == 0) {
        ofstream fout("../Clasament.txt");
        list.sort();
        fout << list;
        fout.close();

        checkAnswers();
    }
}

void writer(SimpleLinkedList& list, my_barrier& b) {
    pair<int, int> result;
    while(results.pop(result)) {
        list.update(result.first, result.second);
    }
    b.wait();
}

void paralel(int readers_count, int writers_count) {
    auto start_time = std::chrono::high_resolution_clock::now();

    int t = 5, p = 10;

    SimpleLinkedList list = SimpleLinkedList();
    vector<string> in_f = input_files(t, p);
    my_barrier b(writers_count + readers_count);
    my_barrier br(readers_count);



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
        readers.emplace_back(reader, start, end, ref(in_f), ref(list), ref(b), ref(br));
        start = end;
    }

    vector<thread> writers;
    for (int i = 0; i < writers_count; i++) {
        writers.emplace_back(writer, ref(list), ref(b));
    }

    for (int i = 0; i < readers_count; i++) {
        readers[i].join();
    }

    for (int i = 0; i < writers_count; i++) {
        writers[i].join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    cout << "Execution Time: " << duration.count() << " milliseconds" << '\n' << std::flush;
}

void secvential() {
    auto start = std::chrono::high_resolution_clock::now();

    int t = 5, p = 10;

    SimpleLinkedList list = SimpleLinkedList();
    vector<string> in_f = input_files(t, p);
    for (auto& file: in_f) {
        ifstream fin(file);
        int id, score;
        while(fin >> id >> score) {
            list.update(id, score);
        }

        fin.close();
    }
    list.sort();

    ofstream fout("../Clasament.txt");
    fout << list;
    fout.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Execution Time: " << duration.count() << " milliseconds" << '\n' << std::flush;
}

#endif //LAB5_PPD_PARALEL_H
