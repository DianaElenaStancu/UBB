#include "RankingManager.h"

#include <map>

void RankingManager::insertNewScore(FinalResult finalResult)
{
    queue.push(finalResult);
}

std::vector<RankingEntry> RankingManager::getRankingBasedOnCountries()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    double elapsedTimeMs = std::chrono::duration<double, std::milli>(currentTime - lastRankingCall).count();
    
    if(!cachedRanking.empty() && elapsedTimeMs < (double)deltaT)
        return cachedRanking;
    
    std::vector<FinalResult> partialResults = rankingList.getUnsortedList();

    std::map<int, FinalResult> mapFromCountryToScore;
    for(auto el:partialResults)
    {
        if(mapFromCountryToScore.find(el.getCountryId())!=mapFromCountryToScore.end())
        {
            mapFromCountryToScore[el.getCountryId()].setScore(mapFromCountryToScore[el.getCountryId()].getScore() + el.getScore());
        }
        else
        {
            mapFromCountryToScore[el.getCountryId()] = el;
        }
    }

    std::vector<RankingEntry> rankings;
    for(auto el : mapFromCountryToScore)
    {
        rankings.push_back({el.first, el.second.getScore()});
    }

    for(int i=0; i<rankings.size(); i++)
    {
        for(int j=i+1; j<rankings.size(); j++)
        {
            if(rankings[i] < rankings[j])
                std::swap(rankings[i], rankings[j]);
        }
    }
    lastRankingCall = std::chrono::high_resolution_clock::now();
    cachedRanking = rankings;

    return rankings;
}

std::vector<RankingEntry> RankingManager::getRankingBasedOnConcurents()
{
    std::vector<FinalResult> partialResults = rankingList.getSortedList();
    std::vector<RankingEntry> rankings;
    for(auto el : partialResults)
    {
        rankings.push_back({el.getId(), el.getScore()});
    }

    return rankings;
}

void RankingManager::producerFinished()
{
    queue.producerFinished();
}

RankingManager::RankingManager(int producersCount, int consumersCount, int deltaT) : consumersCount(consumersCount), deltaT(deltaT), queue(producersCount), rankingList(), lastRankingCall(std::chrono::high_resolution_clock::now())
{
    for (int i = 0; i < consumersCount; i++) {
        auto consume = [this](FinalResult finalResult)
        {
            if (finalResult.getScore() == -1) {
                rankingList.desqualify(finalResult.getId());
            } else {
                rankingList.addScore(finalResult);
            }
        };
        auto worker = [this, consume](){queue.consumeUntilFinished(consume);};
        consumers.emplace_back(worker);
    }
}

RankingManager::~RankingManager()
{
    for (int i = 0; i < consumersCount; i++) {
        consumers[i].join();
    }
}



