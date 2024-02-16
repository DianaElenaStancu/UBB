//
// Created by Andrei Bejan on 12/19/2023.
//

#ifndef LAB5_CUSTOMSYNCEDLIST_H
#define LAB5_CUSTOMSYNCEDLIST_H

#include <mutex>
#include "FinalResult.h"
#include "SyncedLinkedList.h"

#include <vector>


class CustomSyncedList {
private:
    const static int NMAX = 500;
    bool isDesqualified[NMAX];
    std::mutex mutexPerId[NMAX];
    SyncedLinkedList linkedList;
public:
    void addScore(FinalResult score);
    void desqualify(int id);

    void refresh() {
        linkedList.refresh();
        for(int i=0; i<NMAX; i++) {
            isDesqualified[i] = 0;
        }
    }

    std::vector<FinalResult> getSortedList() {
        std::vector<FinalResult> results = linkedList.getAll();
        for(int i=0; i<results.size(); i++) {
            for(int j=i+1; j<results.size(); j++) {
                if(results[i] < results[j])
                    std::swap(results[i], results[j]);
            }
        }
        return results;
    }

    std::vector<FinalResult> getUnsortedList()
    {
        return linkedList.getAll();
    }
};

#endif //LAB5_CUSTOMSYNCEDLIST_H
