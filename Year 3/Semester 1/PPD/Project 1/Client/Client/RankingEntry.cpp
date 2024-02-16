#include "RankingEntry.h"

#include <iostream>

RankingEntry::RankingEntry(int id, int score)
{
    this->id = id;
    this->score = score;
}

bool RankingEntry::operator<(const RankingEntry& other) const
{
    if (score == other.score)
        return id < other.id;
    return score < other.score;
}

bool RankingEntry::operator==(const RankingEntry& other) const
{
    return id == other.id;
}

bool RankingEntry::operator!=(const RankingEntry& other) const
{
    return id != other.id;
}

int RankingEntry::getScore()
{
    return score;
}

int RankingEntry::getId()
{
    return id;
}

void RankingEntry::setScore(int score)
{
    this->score = score;
}

void RankingEntry::setId(int id)
{
    this->id = id;
}

RankingEntry RankingEntry::deserialize(char* source)
{
    int data[2];
    memcpy(data, source, sizeof(int) * 2);

    return RankingEntry(data[0], data[1]);
}

void RankingEntry::serialize(RankingEntry source, char* dest)
{
    int data[2];
    data[0] = source.getId();
    data[1] = source.getScore();

    memcpy(dest, data, sizeof(int) * 2);
}

void RankingEntry::printRankings(std::vector<RankingEntry> rankings, std::string title)
{
    std::cout << title << "\n(id | score)\n";
    for (auto ranking : rankings)
    {
        std::cout << ranking.getId() << " " << ranking.getScore() << "\n";
    }
}
