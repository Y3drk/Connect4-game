#include "Player.h"

Player::Player(std::string name, Color color)
{
	this->name = name;
	this->color = color;
}

Color Player::getColor()
{
	return this->color;
}

std::string Player::getName()
{
	return this->name;
}
