#include "Tile.h"

Tile::Tile(Color color, Vector2D position)
{
	this->color = color;
	this->position = position;
}

Color Tile::getColor() const
{
	return this->color;
}

Vector2D Tile::getPosition()
{
	return this->position;
}
