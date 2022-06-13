#pragma once

class Vector2D
{
	private:
		int x;
		int y;

	public:
		Vector2D();
		Vector2D(int, int);
		int linearize();
		int getX() const;
		int getY() const;
		void print() const;
		void addX(int);
		void addY(int);
};

