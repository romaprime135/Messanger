#pragma once
#include <string>
#include <vector>

class message {
    std::string Sender;
    std::string Getter;
    std::string Text;

public:
    std::string getText() const;
    std::string getSender() const;
    std::string getGetter() const;
    void setText(std::string t);
    void setSender(std::string s);
    void setGetter(std::string g);
    message(std::string Getter, std::string Sender, std::string Text);
    message();
};

std::vector<message> getMessage(const char* Path);
void addMessage(const char* Path, message Msg);