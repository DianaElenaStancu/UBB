#pragma once
#include <vector>
#include <winsock2.h>
#include "RankingEntry.h"

const int BUFFER_SIZE = 100 * 5;

int receiveInt(SOCKET clientSocket);

void sendInt(SOCKET clientSocket, int value);

std::vector<RankingEntry> receiveRanking(SOCKET clientSocket);

std::string receiveString(SOCKET clientSocket);

void sendString(SOCKET clientSocket, std::string message);

std::string receiveFile(SOCKET clientSocket);

void sendFile(SOCKET clientSocket, std::string fileName);
