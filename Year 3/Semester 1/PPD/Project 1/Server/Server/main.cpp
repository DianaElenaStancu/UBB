#include <string>
#include "Server.h"

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char **argv)
{
    int countryCount = std::stoi(argv[1]);
    int producersCount = std::stoi(argv[2]);
    int consumersCount = std::stoi(argv[3]);
    int deltaT = std::stoi(argv[4]);
    int sendFiles = std::stoi(argv[5]);

    // Create a stateful server with a thread pool of n readers threads
    Server server(producersCount, consumersCount, countryCount, deltaT, sendFiles);
    server.startListening();

    return 0;
}
