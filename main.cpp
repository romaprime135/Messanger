#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include "user.h"
#include "message.h"

using namespace std;

//Регистрация
void registerUser() {
    system("cls");
    string username, password, name;
    cout << "Введите логин: ";
    getline(cin, username);
    cout << "Введите пароль: ";
    getline(cin, password);
    cout << "Введите имя: ";
    getline(cin, name);

    if (userExists(username)) {
        cout << "Логин занят!\n";
        cout << "Для продолжения нажмите на END" << std::endl;
        while (!GetAsyncKeyState(VK_END)) {}
        return;
    }

    User newUser(username, password, name);
    saveUser(newUser);
    cout << "Регистрация успешна!\n";
}

//Вход
User* loginUser() {
    system("cls");
    string username, password;
    cout << "Введите логин: ";
    getline(cin, username);
    cout << "Введите пароль: ";
    getline(cin, password);

    vector<User> users = loadUsers();
    for (User& u : users) {
        if (u.getUsername() == username && u.getPassword() == password) {
            return new User(u.getUsername(), u.getPassword(), u.getName());
        }
    }
    system("cls");
    cout << "Неверный логин или пароль!\n";
    cout << "Для продолжения нажмите на END" << std::endl;
    while (!GetAsyncKeyState(VK_END)) {}
    return nullptr;
}

//Публичное сообщение (дополнительный функционал)
void sendToAll(User* user) {
    system("cls");
    string text;
    cout << "Введите сообщение: ";
    getline(cin, text);
    addMessage("messages.txt", message("ALL", user->getUsername(), text));
    cout << "Сообщение отправлено всем!\n";
}

//Приватное сообщение
void sendPrivate(User* user) {
    system("cls");
    string getter, text;
    cout << "Введите логин получателя: ";
    getline(cin, getter);
    cout << "Введите сообщение: ";
    getline(cin, text);
    addMessage("messages.txt", message(getter, user->getUsername(), text));
    cout << "Сообщение отправлено!\n";
}

//Показ сообщений пользователя
void viewMessages(User* user) {
    system("cls");
    vector<message> messages = getMessage("messages.txt");
    cout << "--- Сообщения ---\n";
    for (const message& msg : messages) {
        if (msg.getGetter() == user->getUsername() || msg.getGetter() == "ALL") {
            cout << "От: " << msg.getSender() << "\nТекст: " << msg.getText() << "\n\n";
        }
    }
    system("cls");
    cout << "Для продолжения нажмите на END" << std::endl;
    while (!GetAsyncKeyState(VK_END)){}
}

//Выбор действия
void chatMenu(User* user) {
    while (true) {
        system("cls");
        cout << "1. Отправить всем\n2. Личное сообщение\n3. Просмотр сообщений\n4. Выход\nВыберите: ";
        string choice;
        getline(cin, choice);

        if (choice == "1") sendToAll(user);
        else if (choice == "2") sendPrivate(user);
        else if (choice == "3") viewMessages(user);
        else if (choice == "4") break;
        else {
            cout << "Неверный выбор!\n";
            system("cls");
            cout << "Для продолжения нажмите на END" << std::endl;
            while (!GetAsyncKeyState(VK_END)) {}
        }
    }
}

//Точка входа программы
int main() {
    setlocale(LC_ALL, "RUS");
    while (true) {
        system("cls");
        cout << "1. Регистрация\n2. Вход\n3. Выход\nВыберите: ";
        string choice;
        getline(cin, choice);

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
            cout << "Неверный выбор!\n";
            system("cls");
            cout << "Для продолжения нажмите на END" << std::endl;
            while (!GetAsyncKeyState(VK_END)) {}
        }
    }
    return 0;
}