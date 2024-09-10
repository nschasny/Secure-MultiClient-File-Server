#pragma once
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <iostream>

class ConfigLoader {
private:
    std::unordered_map<std::string, std::string> configMap;

public:
    bool loadConfig(const std::string& filename) {
        std::ifstream configFile(filename);
        if (!configFile.is_open()) {
            std::cerr << "Unable to open configuration file!" << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(configFile, line)) {
            if (line[0] == '#' || line.empty()) {
                continue; // Skip comments or empty lines
            }

            std::istringstream lineStream(line);
            std::string key, value;
            if (std::getline(lineStream, key, '=') && std::getline(lineStream, value)) {
                configMap[key] = value;
            }
        }

        configFile.close();
        return true;
    }

    std::string getValue(const std::string& key) {
        if (configMap.find(key) != configMap.end()) {
            return configMap[key];
        }
        return "";
    }
};
