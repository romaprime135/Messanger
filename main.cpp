#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include "user.h"
#include "message.h"

using namespace std;

//�����������
void registerUser() {
    system("cls");
    string username, password, name;
    cout << "������� �����: ";
    getline(cin, username);
    cout << "������� ������: ";
    getline(cin, password);
    cout << "������� ���: ";
    getline(cin, name);

    if (userExists(username)) {
        cout << "����� �����!\n";
        cout << "��� ����������� ������� �� END" << std::endl;
        while (!GetAsyncKeyState(VK_END)) {}
        return;
    }

    User newUser(username, password, name);
    saveUser(newUser);
    cout << "����������� �������!\n";
}

//����
User* loginUser() {
    system("cls");
    string username, password;
    cout << "������� �����: ";
    getline(cin, username);
    cout << "������� ������: ";
    getline(cin, password);

    vector<User> users = loadUsers();
    for (User& u : users) {
        if (u.getUsername() == username && u.getPassword() == password) {
            return new User(u.getUsername(), u.getPassword(), u.getName());
        }
    }
    system("cls");
    cout << "�������� ����� ��� ������!\n";
    cout << "��� ����������� ������� �� END" << std::endl;
    while (!GetAsyncKeyState(VK_END)) {}
    return nullptr;
}

//��������� ��������� (�������������� ����������)
void sendToAll(User* user) {
    system("cls");
    string text;
    cout << "������� ���������: ";
    getline(cin, text);
    addMessage("messages.txt", message("ALL", user->getUsername(), text));
    cout << "��������� ���������� ����!\n";
}

//��������� ���������
void sendPrivate(User* user) {
    system("cls");
    string getter, text;
    cout << "������� ����� ����������: ";
    getline(cin, getter);
    cout << "������� ���������: ";
    getline(cin, text);
    addMessage("messages.txt", message(getter, user->getUsername(), text));
    cout << "��������� ����������!\n";
}

//����� ��������� ������������
void viewMessages(User* user) {
    system("cls");
    vector<message> messages = getMessage("messages.txt");
    cout << "--- ��������� ---\n";
    for (const message& msg : messages) {
        if (msg.getGetter() == user->getUsername() || msg.getGetter() == "ALL") {
            cout << "��: " << msg.getSender() << "\n�����: " << msg.getText() << "\n\n";
        }
    }
    system("cls");
    cout << "��� ����������� ������� �� END" << std::endl;
    while (!GetAsyncKeyState(VK_END)){}
}

//����� ��������
void chatMenu(User* user) {
    while (true) {
        system("cls");
        cout << "1. ��������� ����\n2. ������ ���������\n3. �������� ���������\n4. �����\n��������: ";
        string choice;
        getline(cin, choice);

        if (choice == "1") sendToAll(user);
        else if (choice == "2") sendPrivate(user);
        else if (choice == "3") viewMessages(user);
        else if (choice == "4") break;
        else {
            cout << "�������� �����!\n";
            system("cls");
            cout << "��� ����������� ������� �� END" << std::endl;
            while (!GetAsyncKeyState(VK_END)) {}
        }
    }
}

//����� ����� ���������
int main() {
    setlocale(LC_ALL, "RUS");
    while (true) {
        system("cls");
        cout << "1. �����������\n2. ����\n3. �����\n��������: ";
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
            cout << "�������� �����!\n";
            system("cls");
            cout << "��� ����������� ������� �� END" << std::endl;
            while (!GetAsyncKeyState(VK_END)) {}
        }
    }
    return 0;
}