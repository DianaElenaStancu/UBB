//
// Created by Diana-Elena Stancu on 18.12.2023.
//

#ifndef LAB5_PPD_MY_BARRIER_H
#define LAB5_PPD_MY_BARRIER_H
#include<mutex>
class my_barrier
        {
        public:
            my_barrier(int count) : thread_count(count), counter(0), waiting(0) {}
            void wait() {
                //fence mechanism
                std::unique_lock<std::mutex> lk(m);
                ++counter;
                ++waiting;
                cv.wait(lk, [&]{return counter >= thread_count;});
                cv.notify_one();
                --waiting;
                if(waiting == 0) {
                    //reset barrier
                    counter = 0;
                }
                lk.unlock();
            }
            int counter;

        private:
            std::mutex m;
            std::condition_variable cv;
            int waiting;
            int thread_count;
        };
#endif //LAB5_PPD_MY_BARRIER_H
