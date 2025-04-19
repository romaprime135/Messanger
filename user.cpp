#define _CRT_SECURE_NO_WARNINGS
#include "user.h"
#include <vector>
#include <fstream>
#include <string>

User::User(std::string UN, std::string PW, std::string Name) : username(UN), password(PW), name(Name) {};

std::string User::getUsername() const { return this->username; }
std::string User::getPassword() const { return this->password; }
std::string User::getName() const { return this->name; }

//Добавление пользователя
void saveUser(const User& user) {
    FILE* file = fopen("users.txt", "a");
    std::string line = user.getUsername() + ";" + user.getPassword() + ";" + user.getName() + "\n";
    fputs(line.c_str(), file);
    fclose(file);
}

//Получение пользователей
std::vector<User> loadUsers() {
    std::vector<User> users;
    FILE* file = fopen("users.txt", "r");
    if (!file) return users;

    char buffer[256];
    while (fgets(buffer, 256, file)) {
        std::string line(buffer);
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        if (pos1 != std::string::npos && pos2 != std::string::npos) {
            std::string username = line.substr(0, pos1);
            std::string password = line.substr(pos1 + 1, pos2 - pos1 - 1);
            std::string name = line.substr(pos2 + 1, line.size() - pos2 - 2);
            users.push_back(User(username, password, name));
        }
    }
    fclose(file);
    return users;
}

//Проверка существования пользователя
bool userExists(const std::string& username) {
    std::vector<User> users = loadUsers();
    for (const User& u : users) {
        if (u.getUsername() == username) {
            return true;
        }
    }
    return false;
}
