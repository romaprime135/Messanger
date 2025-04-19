#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "message.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

std::string message::getGetter() const { return this->Getter; }


std::string message::getSender() const { return this->Sender; }


std::string message::getText() const { return this->Text; }


std::string message::getTag() const { return this->Tag; }


message::message(std::string Getter = "None", std::string Sender = "None", std::string Text = "None", std::string Tag = "None") : Getter(Getter), Sender(Sender), Text(Text), Tag(Tag) {};


message::message() : Getter("None"), Sender("None"), Text("None"), Tag("None") {};

//Отправка сообщения
void addMessage(const char* Path, message Msg)
{
	std::string buffer("");

	{
		std::ifstream file(Path);
		if (file.good()) 
		{
			char ch;

			FILE* file = fopen(Path, "r");
			
			while ((ch = fgetc(file)) != EOF) { buffer += ch; }

			fclose(file);
		}
	}

	FILE* file = fopen(Path, "w");

	std::string result = buffer + Msg.getGetter() + ";" + Msg.getText() + ";" + Msg.getSender() + ";" + Msg.getTag() + "\n";

	fputs(result.c_str(), file);

	fclose(file);
}

//Получение сообщений
std::vector<message>  getMessage(const char* Path)
{
	std::vector<message> res;

	{
		std::ifstream file(Path);
		if (not file.good()) { return res; }
	}

	FILE* file = fopen(Path, "r");

	std::string Getter;
	std::string Text;
	std::string Sender;
	std::string Tag;

	std::string arg;
	char ch;

	int i = 0;

	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == ';')
		{
			switch (i)
			{
			case 0: Getter = arg; break;
			case 1: Text = arg; break;
			case 2: Sender = Sender; break;
			}
			i++;
			arg.clear();
		}
		else if (ch == '\n') 
		{
			Tag = arg; res.push_back(message(Getter, Sender, Text, Tag));
			arg.clear();
			i = 0;
		}
		else { arg += ch; }
	}
	fclose(file);

	return res;
}
