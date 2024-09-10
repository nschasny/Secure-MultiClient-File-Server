#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <mutex>

class Logger {
private:
    std::ofstream logFile;
    std::mutex logMutex;

    std::string getTimestamp() {
        time_t now = time(0);
        tm* localtm = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", localtm);
        return std::string(buffer);
    }

public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::out | std::ios::app);
        if (!logFile) {
            std::cerr << "Error opening log file!" << std::endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> guard(logMutex);
        logFile << getTimestamp() << " " << message << std::endl;
    }
};