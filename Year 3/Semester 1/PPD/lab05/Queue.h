//
// Created by Diana-Elena Stancu on 17.12.2023.
//

#ifndef LAB5_PPD_QUEUE_H
#define LAB5_PPD_QUEUE_H
#include <mutex>
#include <queue>
using namespace std;
template <typename T>
class Queue {
private:
    static const int MAX = 50;
    queue<T> results;
    mutex mtx;
    condition_variable empty;
    condition_variable full;
    atomic<int> counter = 0;
    bool is_on = true;
public:
    void push(T item) {
        unique_lock<std::mutex> lock(mtx);
        while (results.size() == MAX) {
            full.wait(lock);
        }
        results.push(item);
        empty.notify_one();
    }

    bool pop(T& item) {
        unique_lock<std::mutex> lock(mtx);

        counter++;
        while(is_on && results.size() == 0) {
            empty.wait(lock);
        }
        counter--;

        if(!is_on && results.size() == 0)
            return false;

        item = results.front();
        results.pop();
        full.notify_one();
        return true;
    }

    void stop() {
        unique_lock<mutex> lock(mtx);
        is_on = false;
        lock.unlock();

        while(counter.load() != 0) {
            lock.lock();
            empty.notify_all();
            lock.unlock();
        }
    }

};
#endif //LAB5_PPD_QUEUE_H
