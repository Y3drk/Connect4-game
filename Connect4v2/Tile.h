#pragma once
#include <string>
#include "Vector2D.h"
#include "Color.h"

class Tile
{
	private:
		Color color;
		Vector2D position;
	public:
		Tile() {
			this->color = WHITE;
			this->position = Vector2D(8, 8);
		}
		Tile(Color, Vector2D);
		Color getColor() const;
		Vector2D getPosition();

};

