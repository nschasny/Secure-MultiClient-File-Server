#pragma once
#include <unordered_map>
#include <string>

class Authenticator {
private:
    std::unordered_map<std::string, std::string> userDatabase;

public:
    Authenticator() {
        // Preload some users (in practice, load from a secure database)
        userDatabase["user1"] = "password123";
        userDatabase["admin"] = "adminPass";
    }

    bool authenticate(const std::string& username, const std::string& password) {
        if (userDatabase.find(username) != userDatabase.end()) {
            return userDatabase[username] == password;
        }
        return false;
    }
};
