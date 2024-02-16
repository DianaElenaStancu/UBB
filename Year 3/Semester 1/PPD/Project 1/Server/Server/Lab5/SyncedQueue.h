//
// Created by Andrei Bejan on 12/19/2023.
//

#ifndef LAB5_SYNCEDQUEUE_H
#define LAB5_SYNCEDQUEUE_H

#include <queue>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <atomic>
#include <functional>

#include "RankingManager.h"

template<typename T>
class SyncedQueue {
private:
    const static int MAX_SIZE = 50;
    std::queue<T> rawQueue;
    std::condition_variable cvFull, cvEmpty;
    std::mutex mutexWait;
    int producersCount;

public:
    SyncedQueue(int producersCount) {
        this->producersCount = producersCount;
    }

    void consumeUntilFinished(std::function<void(T)> consume);

    void push(T newElement);

    void producerFinished();
};


template<typename T>
void SyncedQueue<T>::consumeUntilFinished(std::function<void(T)> consume) {
    while (true) {
        std::unique_lock<std::mutex> lockMutexWait(mutexWait);
        while (rawQueue.empty()) {
            if (producersCount == 0) {
//                cout<<"worker a murit\n";
                return;
            }
//            cout<<"worker a intrat in wait\n";
            cvEmpty.wait(lockMutexWait);
//            cout<<"worker a iesit din wait\n";
        }
        T currentElement = rawQueue.front();
        rawQueue.pop();
//        cout<<"il notific pe producer\n";
        cvFull.notify_one();
//        cout<<"l-am notific pe producer\n";
        lockMutexWait.unlock();
        consume(currentElement);
    }
}

template<typename T>
void SyncedQueue<T>::push(T newElement) {
    std::unique_lock<std::mutex> lockMutexWait(mutexWait);
    while (rawQueue.size() == MAX_SIZE) {
//        cout<<"producer a intrat in wait\n";
        cvFull.wait(lockMutexWait);
//        cout<<"producer a iesit din wait\n";
    }

    rawQueue.push(newElement);
//    cout<<"il notific pe consumer\n";
    cvEmpty.notify_one();
//    cout<<"l-am notific pe consumer\n";
}

template<typename T>
void SyncedQueue<T>::producerFinished() {
    std::unique_lock<std::mutex> lockMutexWait(mutexWait);
    producersCount--;
    if (producersCount == 0) {
//        cout<<"notific sa moara\n";
        cvEmpty.notify_all();
//        cout<<"am notificat!\n";
    }
}

#endif //LAB5_SYNCEDQUEUE_H
