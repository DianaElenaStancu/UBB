#pragma once

class FinalResult
{
    int concurentId = -1;
    int concurentScore = -1;
    int countryId = -1;

public:
    static const int sizeOf = 3 * sizeof(int);

    FinalResult();

    FinalResult(int concurentId, int concurentScore, int countryId);

    bool operator<(const FinalResult& other) const;

    bool operator==(const FinalResult& other) const;

    bool operator!=(const FinalResult& other) const;

    int getScore();

    int getId();

    int getCountryId();

    void setScore(int score);

    void setId(int id);

    void setCountryId(int countryId);

    static FinalResult deserialize(char* source);

    static void serialize(FinalResult source, char* dest);
};


