#include "Player.h"

Player::Player()
{
	Username = " ";
	Score = 0;
}

void Player::set_username(std::string Username)
{
	this->Username = Username;
}

std::string Player::get_username()
{
	return Username;
}

void Player::set_score(int Score)
{
	this->Score = Score;
}

int Player::get_score()
{
	return Score;
}