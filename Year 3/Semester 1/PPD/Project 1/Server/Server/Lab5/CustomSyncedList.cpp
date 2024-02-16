//
// Created by Andrei Bejan on 12/19/2023.
//

#include "CustomSyncedList.h"

void CustomSyncedList::desqualify(int id) {
    std::unique_lock<std::mutex> lockPerId(mutexPerId[id]);
    if(id == -1)
        std::cout<<"oh nonono";
    if(!isDesqualified[id]) {
        isDesqualified[id] = true;
        linkedList.remove(id);
    }
}

void CustomSyncedList::addScore(FinalResult score) {
    int id = score.getId();
    std::unique_lock<std::mutex> lockPerId(mutexPerId[id]);
    if(!isDesqualified[id]) {
        linkedList.update(score);
    }
}