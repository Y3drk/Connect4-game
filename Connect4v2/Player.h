#pragma once
#include <string>
#include "Color.h"

class Player
{
private:
	Color color;
	std::string name;

public:
	Player() {
		this->name = "Player1";
		this->color = RED;
	}
	Player(std::string, Color);
	Color getColor();
	std::string getName();
};

