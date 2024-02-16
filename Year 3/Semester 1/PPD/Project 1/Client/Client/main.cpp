#include <fstream>
#include <string>
#include <vector>

#include "Client.h"
#include "FinalResult.h"

const int PROBLEM_COUNT = 10;


std::vector<FinalResult> readResultsFromFile(int clientId)
{
    std::vector<FinalResult> results;

    for (int i = 0; i < PROBLEM_COUNT; i++)
    {
        std::ifstream fin(
            "C:/Files/University/An 3/Sem 1/PPD/producator_consumator/data/Rezultate" + std::to_string(clientId) + "_" +
            std::to_string(i) + ".txt");
        
        int concurentId, concurentScore;
        while (fin >> concurentId >> concurentScore)
        {
            FinalResult finalResult(concurentId, concurentScore, clientId);
            results.push_back(finalResult);
        }
    }
    
    return results;
}


int main(int argc, char** argv)
{
    int clientId = std::stoi(argv[1]);
    int deltaX = std::stoi(argv[2]);
    int sendFiles = std::stoi(argv[3]);

    std::vector<FinalResult> results = readResultsFromFile(clientId);

    Client client(clientId, deltaX, results, sendFiles);
    client.sendDataToServer();

    return 0;
}
