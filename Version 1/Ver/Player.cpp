#include "Player.h"

Player::Player()
{
	username = "";
	score = 0;
}

void Player::set_username(std::string username)
{
	this->username = username;
}

void Player::set_score(int score)
{
	this->score = score;
}

std::string Player::get_username()
{
	return username;
}

int Player::get_score()
{
	return score;
}