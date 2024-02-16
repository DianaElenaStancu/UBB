#pragma once

#include <mutex>
#include <unordered_map>
#include <winsock2.h>
#include "RankingManager.h"
#include "ThreadPool.h"
#include "Lab5/FinalResult.h"

class Server
{
public:
    Server(int threadPoolSize, int consumersCount, int expectedNumOfClients, int deltaT, int sendFiles);
    void startListening();
    ~Server();
    
private:
    void initializeServer();
    std::vector<FinalResult> readResultsFromFile(std::string fileName, int clientId);
    void handleClient(SOCKET clientSocket);
    std::vector<FinalResult> receiveResultsBlock(SOCKET clientSocket);

    static const int PORT = 8080;
    static const int BACKLOG = 10;
    static const int BLOCK_SIZE = 20;
    static const int FILE_BLOCK_SIZE = 1000;
    static const int BUFFER_SIZE = 1024;

    SOCKET serverSocket;
    std::mutex completedClientsMutex;
    std::condition_variable waitForRankings;
    std::vector<SOCKET> clients;
    RankingManager rankingManager;
    int expectedClients;
    int completedClients;
    ThreadPool threadPool;
    bool sendFiles;
};
