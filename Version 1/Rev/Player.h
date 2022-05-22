#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <fstream>
#include <filesystem>

class Player
{
private:
	std::string username;
	int score;
public:
	Player();
	~Player() = default;
	void set_username(std::string username);
	void set_score(int score);
	std::string get_username();
	int get_score();
};
