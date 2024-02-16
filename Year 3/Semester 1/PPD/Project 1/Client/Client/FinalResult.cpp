#include "FinalResult.h"

#include <cstring>

FinalResult::FinalResult()
{
}

FinalResult::FinalResult(int concurentId, int concurentScore, int countryId)
{
    this->concurentId = concurentId;
    this->concurentScore = concurentScore;
    this->countryId = countryId;
}

bool FinalResult::operator<(const FinalResult& other) const
{
    if (concurentScore == other.concurentScore)
        return concurentId < other.concurentId;
    return concurentScore < other.concurentScore;
}

bool FinalResult::operator==(const FinalResult& other) const
{
    return concurentId == other.concurentId;
}

bool FinalResult::operator!=(const FinalResult& other) const
{
    return concurentId != other.concurentId;
}

int FinalResult::getScore()
{
    return concurentScore;
}

int FinalResult::getId()
{
    return concurentId;
}

int FinalResult::getCountryId()
{
    return countryId;
}

void FinalResult::setScore(int score)
{
    this->concurentScore = score;
}

void FinalResult::setId(int id)
{
    this->concurentId = id;
}

void FinalResult::setCountryId(int countryId)
{
    this->countryId = countryId;
}

FinalResult FinalResult::deserialize(char* source)
{
    int data[3];
    memcpy(data, source, sizeof(int) * 3);

    return FinalResult(data[0], data[1], data[2]);
}

void FinalResult::serialize(FinalResult source, char* dest)
{
    int data[3];
    data[0] = source.getId();
    data[1] = source.getScore();
    data[2] = source.getCountryId();

    memcpy(dest, data, sizeof(int) * 3);
}
