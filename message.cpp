#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "message.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

void message::setGetter(std::string g)
{
	if (g.size() < 10) { this->Getter = g; }
}


void message::setSender(std::string s) 
{
	if (s.size() < 10) { this->Sender = s; }
}


void message::setText(std::string t)
{
	if (t.size() < 5000) { this->Text = t; }
}


std::string message::getGetter() const { return this->Getter; }


std::string message::getSender() const { return this->Sender; }


std::string message::getText() const { return this->Text; }


message::message(std::string Getter = "None", std::string Sender = "None", std::string Text = "None") : Getter(Getter), Sender(Sender), Text(Text) {};


message::message() : Getter("None"), Sender("None"), Text("None") {};

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

	std::string result = buffer + Msg.getGetter() + ";" + Msg.getText() + ";" + Msg.getSender() + "\n";

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
			}
			i++;
			arg.clear();
		}
		else if (ch == '\n') 
		{
			Sender = arg; res.push_back(message(Getter, Sender, Text));
			arg.clear();
			i = 0;
		}
		else { arg += ch; }
	}
	fclose(file);

	return res;
}