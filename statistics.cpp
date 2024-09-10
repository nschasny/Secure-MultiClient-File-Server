#pragma once
#include <atomic>
#include <mutex>
#include <iostream>

class ServerStatistics {
private:
    std::atomic<int> filesServed;
    std::atomic<int> clientsConnected;
    std::atomic<int> totalBytesTransferred;
    std::mutex statsMutex;

public:
    ServerStatistics() : filesServed(0), clientsConnected(0), totalBytesTransferred(0) {}

    void incrementFilesServed() {
        filesServed++;
    }

    void incrementClientsConnected() {
        clientsConnected++;
    }

    void incrementBytesTransferred(int bytes) {
        totalBytesTransferred += bytes;
    }

    void logStats() {
        std::lock_guard<std::mutex> lock(statsMutex);
        std::cout << "Clients Connected: " << clientsConnected.load() << "\n"
                  << "Files Served: " << filesServed.load() << "\n"
                  << "Total Bytes Transferred: " << totalBytesTransferred.load() << " bytes" << std::endl;
    }
};
