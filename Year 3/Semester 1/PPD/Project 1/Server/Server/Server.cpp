#include "Server.h"

#include <cassert>
#include <fstream>
#include <future>
#include <iostream>

#include "NetworkUtils.h"
#include "Lab5/FinalResult.h"

void Server::handleClient(SOCKET clientSocket)
{
    clients.push_back(clientSocket);

    int clientId = receiveInt(clientSocket);

    if (sendFiles)
    {
        int filesCount = receiveInt(clientSocket);
        std::cout << "Clientul " << clientId << " va trimite " << filesCount << " files\n";

        for (int i = 0; i < filesCount; i++)
        {
            std::string fileName = receiveFile(clientSocket);
            std::vector<FinalResult> results = this->readResultsFromFile(fileName, clientId);

            for (auto result : results)
            {
                rankingManager.insertNewScore(result);
            }
            std::cout << "Am primit fisierul " << i << " de la clientul " << clientId << "\n";
            std::future<std::vector<RankingEntry>> future = std::async(std::launch::async,
                                                                       &RankingManager::getRankingBasedOnCountries,
                                                                       &rankingManager);

            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            std::vector<RankingEntry> rankings = future.get();
            sendRanking(clientSocket, rankings);
            std::cout << "Am trimis rankingul partial pe tari catre clientul " << clientId << "\n";
        }
    }
    else
    {
        int blocksCount = receiveInt(clientSocket);
        std::cout << "Clientul " << clientId << " v-a trimite " << blocksCount << " blockuri\n";

        for (int i = 0; i < blocksCount; i++)
        {
            std::vector<FinalResult> results = this->receiveResultsBlock(clientSocket);

            for (auto result : results)
            {
                rankingManager.insertNewScore(result);
            }
            std::cout << "Am primit blockul " << i << " de la clientul " << clientId << "\n";
            std::future<std::vector<RankingEntry>> future = std::async(std::launch::async,
                                                                       &RankingManager::getRankingBasedOnCountries,
                                                                       &rankingManager);

            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            std::vector<RankingEntry> rankings = future.get();
            sendRanking(clientSocket, rankings);
            std::cout << "Am trimis rankingul partial pe tari catre clientul " << clientId << "\n";
        }
    }

    rankingManager.producerFinished();

    std::unique_lock<std::mutex> lock(completedClientsMutex);
    completedClients++;
    if (completedClients == expectedClients)
        waitForRankings.notify_one();
}

std::vector<FinalResult> Server::receiveResultsBlock(SOCKET clientSocket)
{
    int blockSize = receiveInt(clientSocket);
    char data[BLOCK_SIZE * FinalResult::sizeOf];
    recv(clientSocket, data, blockSize * FinalResult::sizeOf, 0);

    std::vector<FinalResult> results;
    int dataIndex = 0;
    for (int i = 0; i < blockSize; i++)
    {
        FinalResult result = FinalResult::deserialize(data + dataIndex);
        results.push_back(result);
        dataIndex += FinalResult::sizeOf;
    }

    return results;
}

Server::Server(int threadPoolSize, int consumersCount, int expectedNumOfClients, int deltaT, int sendFiles):
    rankingManager(expectedNumOfClients, consumersCount, deltaT), expectedClients(expectedNumOfClients),
    completedClients(0), threadPool(threadPoolSize), sendFiles(sendFiles)
{
    initializeServer();
}

void Server::startListening()
{
    for (int i = 0; i < expectedClients; i++)
    {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET)
        {
            std::cerr << "Error accepting client connection." << std::endl;
            continue;
        }
        threadPool.enqueue([this, clientSocket]
        {
            handleClient(clientSocket);
        });
    }

    std::unique_lock<std::mutex> lock(completedClientsMutex);
    if (completedClients < expectedClients)
    {
        waitForRankings.wait(lock);
    }

    std::vector<RankingEntry> finalConcurentsRanking = rankingManager.getRankingBasedOnConcurents();
    std::vector<RankingEntry> finalCountriesRanking = rankingManager.getRankingBasedOnCountries();

    std::ofstream foutConcurents("C:/Files/University/An 3/Sem 1/PPD/Project 1/Server/Server/ConcurentsRanking.txt");
    std::ofstream foutCountry("C:/Files/University/An 3/Sem 1/PPD/Project 1/Server/Server/CountryRanking.txt");

    std::cout << "Scriu rezultatele finale in fisiere\n";
    // write results to file
    for (auto entry : finalConcurentsRanking)
    {
        foutConcurents << entry.getId() << " " << entry.getScore() << "\n";
    }
    foutConcurents.close();

    for (auto entry : finalCountriesRanking)
    {
        foutCountry << entry.getId() << " " << entry.getScore() << "\n";
    }
    foutCountry.close();

    // compare with groundtruth

    std::cout << "Compar rezultatele obtinute cu groundtruth\n";
    std::ifstream finOutput("C:/Files/University/An 3/Sem 1/PPD/Project 1/Server/Server/ConcurentsRanking.txt");
    std::ifstream finGroundTruth(
        "C:/Files/University/An 3/Sem 1/PPD/producator_consumator/data/RezultateGroundTruth.txt");

    int x, y;
    while (finOutput >> x && finGroundTruth >> y)
    {
        assert(x == y);
    }
    if (finOutput >> x || finGroundTruth >> y)
        assert(false);

    finGroundTruth.close();
    finOutput.close();

    std::cout << "Trimit rankingul final pe concurenti & pe tari tuturor clientilor\n";
    for (auto clientSocket : clients)
    {
        sendRanking(clientSocket, finalConcurentsRanking);
        sendRanking(clientSocket, finalCountriesRanking);
        closesocket(clientSocket);
    }
}

Server::~Server()
{
    closesocket(serverSocket);
    WSACleanup();
}

void Server::initializeServer()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Error initializing Winsock." << std::endl;
        exit(EXIT_FAILURE);
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cerr << "Error creating server socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Error binding server socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, BACKLOG) == SOCKET_ERROR)
    {
        std::cerr << "Error listening on server socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;
}

std::vector<FinalResult> Server::readResultsFromFile(std::string fileName, int clientId)
{
    std::vector<FinalResult> results;
    std::ifstream fin(
        "C:/Files/University/An 3/Sem 1/PPD/Project 1/Server/Server/" + fileName);

    int concurentId, concurentScore;
    while (fin >> concurentId >> concurentScore)
    {
        FinalResult finalResult(concurentId, concurentScore, clientId);
        results.push_back(finalResult);
    }

    return results;
}
