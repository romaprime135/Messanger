#pragma once
#include <string>
#include <vector>

class message {
    std::string Sender;
    std::string Getter;
    std::string Text;
    std::string Tag;

public:
    std::string getText() const;
    std::string getSender() const;
    std::string getGetter() const;
    std::string getTag() const;
    message(std::string Getter, std::string Sender, std::string Text, std::string Tag);
    message();
};

std::vector<message> getMessage(const char* Path);
void addMessage(const char* Path, message Msg);
