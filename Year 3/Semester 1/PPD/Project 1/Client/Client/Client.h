// client.cpp
#pragma once

#include <winsock2.h>
#include "ThreadPool.h"
#include "FinalResult.h"
#include "RankingEntry.h"

class Client
{
public:
    Client(int clientId, int deltaX, std::vector<FinalResult> results, bool sendFiles);
    void sendDataToServer();
    ~Client();

private:
    void initializeClient();
    void sendResultsBlock(int blockNum);

    SOCKET clientSocket;
    int clientId;
    int deltaX;
    std::vector<FinalResult> results;
    bool sendFiles;
    static const int PORT = 8080;
    static const int BLOCK_SIZE = 20;
    static const int PROBLEM_COUNT = 10;
};
