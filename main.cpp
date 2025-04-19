#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include "user.h"
#include "message.h"


//Регистрация
void registerUser() {
    system("cls");
    std::string username, password, name;
    std::cout << "Введите логин: ";
    getline(std::cin, username);
    std::cout << "Введите пароль: ";
    getline(std::cin, password);
    std::cout << "Введите имя: ";
    getline(std::cin, name);

    if (userExists(username) || username == "ALL") {
        std::cout << "Логин занят!\n";
        std::cout << "Для продолжения нажмите на END" << std::endl;
        while (!GetAsyncKeyState(VK_END)) {}
        return;
    }

    User newUser(username, password, name);
    saveUser(newUser);
    std::cout << "Регистрация успешна!\n";
}

//Вход
User* loginUser() {
    system("cls");
    std::string username, password;
    std::cout << "Введите логин: ";
    getline(std::cin, username);
    std::cout << "Введите пароль: ";
    getline(std::cin, password);

    std::vector<User> users = loadUsers();
    for (User& u : users) {
        if (u.getUsername() == username && u.getPassword() == password) {
            return new User(u.getUsername(), u.getPassword(), u.getName());
        }
    }
    system("cls");
    std::cout << "Неверный логин или пароль!\n";
    std::cout << "Для продолжения нажмите на END" << std::endl;
    while (!GetAsyncKeyState(VK_END)) {}
    return nullptr;
}

//Публичное сообщение
void sendToAll(User* user) {
    system("cls");
    std::string text, tag;
    std::cout << "Введите сообщение: ";
    getline(std::cin, text);
    std::cout << "Укажите важность вашего сообщения (Low, Medium, High): ";
    getline(std::cin, tag);
    if (tag != "Low" && tag != "Medium" && tag != "High")
    {
        system("cls");
        std::cout << "Неверный приоритет сообщения\n";
        std::cout << "Для продолжения нажмите на END" << std::endl;
        while (!GetAsyncKeyState(VK_END)) {}
        return;
    }
    addMessage("messages.txt", message("ALL", user->getUsername(), text, tag));
    std::cout << "Сообщение отправлено всем!\n";
}

//Приватное сообщение
void sendPrivate(User* user) {
    system("cls");
    std::string getter, text, tag;
    std::cout << "Введите логин получателя: ";
    getline(std::cin, getter);
    std::cout << "Введите сообщение: ";
    getline(std::cin, text);
    std::cout << "Укажите важность вашего сообщения (Low, Medium, High): ";
    getline(std::cin, tag);
    if (tag != "Low" && tag != "Medium" && tag != "High")
    {
        system("cls");
        std::cout << "Неверный приоритет сообщения\n";
        std::cout << "Для продолжения нажмите на END" << std::endl;
        while (!GetAsyncKeyState(VK_END)) {}
        return;
    }
    addMessage("messages.txt", message(getter, user->getUsername(), text, tag));
    std::cout << "Сообщение отправлено!\n";
}

//Показ сообщений пользователя
void viewMessages(User* user) {
    system("cls");
    std::vector<message> messages = getMessage("messages.txt");
    std::cout << "--- Сообщения ---\n";
    std::cout << "Low priority" << std::endl;
    for (const message& msg : messages) {
        if ((msg.getGetter() == user->getUsername() || (msg.getGetter() == "ALL" || msg.getSender() != user->getUsername())) && msg.getTag() == "Low") {
            std::cout << "От: " << msg.getSender() << "\nТекст: " << msg.getText() << "\n\n";
        }
    }
    std::cout << "Medium priority" << std::endl;
    for (const message& msg : messages) {
        if ((msg.getGetter() == user->getUsername() || (msg.getGetter() == "ALL" || msg.getSender() != user->getUsername())) && msg.getTag() == "Medium") {
            std::cout << "От: " << msg.getSender() << "\nТекст: " << msg.getText() << "\n\n";
        }
    }
    std::cout << "High priority" << std::endl;
    for (const message& msg : messages) {
        if ((msg.getGetter() == user->getUsername() || (msg.getGetter() == "ALL" || msg.getSender() != user->getUsername())) && msg.getTag() == "High") {
            std::cout << "От: " << msg.getSender() << "\nТекст: " << msg.getText() << "\n\n";
        }
    }
    std::cout << "Для продолжения нажмите на END" << std::endl;
    while (!GetAsyncKeyState(VK_END)){}
}

//Выбор действия
void chatMenu(User* user) {
    while (true) {
        system("cls");
        std::cout << "1. Отправить всем\n2. Личное сообщение\n3. Просмотр сообщений\n4. Выход\nВыберите: ";
        std::string choice;
        getline(std::cin, choice);

        if (choice == "1") sendToAll(user);
        else if (choice == "2") sendPrivate(user);
        else if (choice == "3") viewMessages(user);
        else if (choice == "4") break;
        else {
            std::cout << "Неверный выбор!\n";
            system("cls");
            std::cout << "Для продолжения нажмите на END" << std::endl;
            while (!GetAsyncKeyState(VK_END)) {}
        }
    }
}

//Точка входа программы
int main() {
    setlocale(LC_ALL, "RUS");
    while (true) {
        system("cls");
        std::cout << "1. Регистрация\n2. Вход\n3. Выход\nВыберите: ";
        std::string choice;
        getline(std::cin, choice);

        if (choice == "1") registerUser();
        else if (choice == "2") {
            User* user = loginUser();
            if (user != nullptr) {
                chatMenu(user);
                delete user;
            }
        }
        else if (choice == "3") break;
        else {
            std::cout << "Неверный выбор!\n";
            system("cls");
            std::cout << "Для продолжения нажмите на END" << std::endl;
            while (!GetAsyncKeyState(VK_END)) {}
        }
    }
    return 0;
}
