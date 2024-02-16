#pragma once
#include "Lab5/CustomSyncedList.h"
#include "Lab5/FinalResult.h"
#include "RankingEntry.h"
#include "Lab5/SyncedQueue.h"


class RankingManager
{
public:
    void insertNewScore(FinalResult finalResult);
    std::vector<RankingEntry> getRankingBasedOnCountries();
    std::vector<RankingEntry> getRankingBasedOnConcurents();
    void producerFinished();
    RankingManager(int producersCount, int consumersCount, int deltaT);
    ~RankingManager();
private:
    int consumersCount, deltaT;
    SyncedQueue<FinalResult> queue;
    CustomSyncedList rankingList;
    std::vector<std::thread> consumers;
    std::vector<RankingEntry> cachedRanking;
    std::chrono::time_point<std::chrono::steady_clock> lastRankingCall;
};


