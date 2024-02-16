#include "NetworkUtils.h"

#include <fstream>
#include <iostream>

int receiveInt(SOCKET clientSocket)
{
    char buffer[sizeof(int)];
    recv(clientSocket, buffer, sizeof(int), 0);
    
    int dest;
    memcpy(&dest, buffer, sizeof(int));
    return dest;
}

void sendInt(SOCKET clientSocket, int value)
{
    char buffer[sizeof(int)];
    memcpy(buffer, &value, sizeof(int));
    send(clientSocket, buffer, sizeof(int), 0);
}

std::vector<RankingEntry> receiveRanking(SOCKET clientSocket)
{
    int rankingSize = receiveInt(clientSocket);
    
    char rankingData[BUFFER_SIZE * RankingEntry::sizeOf];
    recv(clientSocket, rankingData, rankingSize * RankingEntry::sizeOf, 0);
            
    std::vector<RankingEntry> rankings;
    int dataIndex = 0;
    for (int j = 0; j < rankingSize; j++)
    {
        RankingEntry ranking = RankingEntry::deserialize(rankingData + dataIndex);
        rankings.push_back(ranking);
        dataIndex += RankingEntry::sizeOf;
    }
    
    return rankings;
}

void sendRanking(SOCKET clientSocket, std::vector<RankingEntry> rankings)
{
    char rankingData[BUFFER_SIZE * RankingEntry::sizeOf];

    int lastPosInData = 0;
    for(auto ranking: rankings)
    {
        RankingEntry::serialize(ranking, rankingData + lastPosInData);
        lastPosInData += RankingEntry::sizeOf;
    }

    sendInt(clientSocket, (int)rankings.size());
    send(clientSocket, rankingData, (int)rankings.size() * RankingEntry::sizeOf, 0);
}

std::string receiveString(SOCKET clientSocket)
{
    int stringLength = receiveInt(clientSocket);
    char message[BUFFER_SIZE];

    recv(clientSocket, message, stringLength, 0);
    message[stringLength] = '\0';
    return std::string(message);
}

void sendString(SOCKET clientSocket, std::string message)
{
    int messageLength = message.size();
    sendInt(clientSocket, messageLength);
    send(clientSocket, message.c_str(), messageLength, 0);
}

std::string receiveFile(SOCKET clientSocket)
{
    std::string fileName = receiveString(clientSocket);
    int blocksCount = receiveInt(clientSocket);

    char buffer[BUFFER_SIZE];
    std::ofstream fout("C:/Files/University/An 3/Sem 1/PPD/Project 1/Server/Server/"+fileName, std::ios::binary); // why binary
    
    for(int i=0; i<blocksCount; i++)
    {
        int blockSize = receiveInt(clientSocket);
        recv(clientSocket, buffer, blockSize, 0);

        fout.write(buffer, blockSize);
    }
    fout.close();
    return fileName;
}

void sendFile(SOCKET clientSocket, std::string fileName)
{
    sendString(clientSocket, fileName);

    std::ifstream fin(fileName, std::ios::binary | std::ios::ate);
    int fileSize = fin.tellg();
    fin.close();
    
    int blocksCount = fileSize / BUFFER_SIZE + (fileSize % BUFFER_SIZE ? 1 : 0);
    sendInt(clientSocket, blocksCount);
    
    char buffer[BUFFER_SIZE];
    std::ifstream fin2("C:/Files/University/An 3/Sem 1/PPD/producator_consumator/data/"+fileName, std::ios::binary);
    
    for(int i=0; i<blocksCount; i++)
    {
        int blockSize = BUFFER_SIZE;
        if (i == blocksCount - 1 && fileSize % BUFFER_SIZE != 0)
        {
            blockSize = fileSize % BUFFER_SIZE;
        }
        sendInt(clientSocket, blockSize);
        
        fin2.read(buffer, blockSize);
        send(clientSocket, buffer, blockSize, 0);
    }
    fin2.close();
}