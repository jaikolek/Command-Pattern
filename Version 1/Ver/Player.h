#pragma once
#include "Header.h"

class Player
{
private:
	std::string username;
	int score;
public:
	Player();
	~Player() = default;
	void set_username(std::string);
	void set_score(int);
	std::string get_username();
	int get_score();
};
