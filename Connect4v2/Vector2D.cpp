#include "Vector2D.h"
#include <iostream>
#include <cstring>
#include <cctype>

Vector2D::Vector2D()
{
	this->x = 0;
	this->y = 0;
}

Vector2D::Vector2D(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Vector2D::linearize()
{
	return this->y * 7 + this->x;
}

int Vector2D::getX() const
{
	return this->x;
}

int Vector2D::getY() const
{
	return this->y;
}

void Vector2D::print() const
{
	std::cout << "("<< this->x<< ", "<< this->y<< ")"<< std::endl;
}

void Vector2D::addX(int argument)
{
	this->x += argument;
}

void Vector2D::addY(int argument)
{
	this->y += argument;
}
