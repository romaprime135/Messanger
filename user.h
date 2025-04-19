#pragma once
#include <string>
#include <vector>

class User {
    std::string username;
    std::string password;
    std::string name;

public:
    User(std::string UN, std::string PW, std::string Name);
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getName() const;
};

void saveUser(const User& user);
std::vector<User> loadUsers();
bool userExists(const std::string& username);
