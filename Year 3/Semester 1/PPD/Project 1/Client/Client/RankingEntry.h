#pragma once
#include <cstring>
#include <string>
#include <vector>

class RankingEntry
{
    int id = -1;
    int score = -1;

public:
    static const int sizeOf = 2 * sizeof(int);

    RankingEntry() = default;

    RankingEntry(int id, int score);

    bool operator<(const RankingEntry& other) const;

    bool operator==(const RankingEntry& other) const;

    bool operator!=(const RankingEntry& other) const;

    int getScore();

    int getId();

    void setScore(int score);

    void setId(int id);

    static RankingEntry deserialize(char* source);

    static void serialize(RankingEntry source, char* dest);

    static void printRankings(std::vector<RankingEntry> rankings, std::string title);
};
