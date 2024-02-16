#include "Client.h"

#include <iostream>
#include <ws2tcpip.h>
#include "RankingEntry.h"
#include "NetworkUtils.h"

#pragma comment(lib, "ws2_32.lib")


void Client::sendDataToServer()
{
    sendInt(clientSocket, clientId);
    if (sendFiles)
    {
        sendInt(clientSocket, PROBLEM_COUNT);

        for (int i = 0; i < PROBLEM_COUNT; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(deltaX));
            
            std::string fileName = "Rezultate" + std::to_string(clientId) + "_" + std::to_string(i) + ".txt";
            sendFile(clientSocket, fileName);
            std::cout<<"Am trimis file-ul " << i << " cu rezultate\n";

            std::vector<RankingEntry> partialCountriesRanking = receiveRanking(clientSocket);
            std::cout<<"Am primit rankingul partial pe tari \n";
            RankingEntry::printRankings(partialCountriesRanking, "Partial countries rankings received:");
        }
    } else
    {
        int blocksCount = (int)results.size() / BLOCK_SIZE + (results.size() % BLOCK_SIZE != 0 ? 1 : 0);
    
        sendInt(clientSocket, blocksCount);
        std::cout<<"Am trimis clientId " << clientId << " si blocksCount " << blocksCount<<"\n";

        for (int i = 0; i < blocksCount; i++)
        {
            this->sendResultsBlock(i);
            std::cout<<"Am trimis blockul " << i << " de rezultate\n";

            std::vector<RankingEntry> partialCountriesRanking = receiveRanking(clientSocket);
            std::cout<<"Am primit rankingul partial pe tari \n";
            RankingEntry::printRankings(partialCountriesRanking, "Partial countries rankings received:");
        }
    }

    std::cout<<"Astept pt rezultatele finale\n";
    // get final rankings for concurents
    std::vector<RankingEntry> finalConcurentsRankings = receiveRanking(clientSocket);
    std::cout<<"Am primit rankingul final pe concurenti \n";
    RankingEntry::printRankings(finalConcurentsRankings, "Final concurents rankings:");

    // get final rankings for countries
    std::vector<RankingEntry> finalCountriesRankings = receiveRanking(clientSocket);
    std::cout<<"Am primit rankingul final pe tari \n";
    RankingEntry::printRankings(finalCountriesRankings, "Final countries rankings:");

}

void Client::sendResultsBlock(int blockNum)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(deltaX));

    int startIndex = blockNum * BLOCK_SIZE;
    int endIndex = min(startIndex + BLOCK_SIZE, results.size());
    std::vector<FinalResult> resultsSubset(results.begin() + startIndex, results.begin() + endIndex);

    char data[BLOCK_SIZE * FinalResult::sizeOf];
    int lastPosInData = 0;
    for (auto result : resultsSubset)
    {
        FinalResult::serialize(result, data + lastPosInData);
        lastPosInData += FinalResult::sizeOf;
    }

    sendInt(clientSocket, (int)resultsSubset.size());
    send(clientSocket, data, (int)resultsSubset.size() * FinalResult::sizeOf, 0);
}

Client::Client(int clientId, int deltaX, std::vector<FinalResult> results, bool sendFiles): clientId(clientId), deltaX(deltaX),
                                                                            results(results), sendFiles(sendFiles)
{
    initializeClient();
}

Client::~Client()
{
    closesocket(clientSocket);
    WSACleanup();
}

void Client::initializeClient()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Error initializing Winsock." << std::endl;
        exit(EXIT_FAILURE);
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cerr << "Error creating client socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;

    if (InetPton(AF_INET, L"127.0.0.1", &(serverAddr.sin_addr)) != 1)
    {
        std::cerr << "Error converting IP address." << std::endl;
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_port = htons(PORT);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Error connecting to server." << std::endl;
        exit(EXIT_FAILURE);
    }
}
