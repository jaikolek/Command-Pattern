#pragma once
#include <iostream>

class Player
{
protected:
	std::string Username;
	int Score;

public:
	Player();
	void set_username(std::string);
	std::string get_username();
	void set_score(int);
	int get_score();
};

