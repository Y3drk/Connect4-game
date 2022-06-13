#include "Gameboard.h"
#include <stdexcept>
#include "Player.h"
#include "Tile.h"
#include <iostream>

int Gameboard::checkDiagonals()
{
	Vector2D currentLocation;
	int counter = 1;
	Color currentColor;

	//upper left to tight
	for (int i = 2; i > 0; i--) {
		currentLocation = Vector2D(0, i);
		currentColor = this->getTileFrom(currentLocation).getColor();
		counter = 1;

		while (currentLocation.getX() < 6 - i && currentLocation.getY() < 6) {
			currentLocation.addX(1);
			currentLocation.addY(1);
			if (currentColor == getTileFrom(currentLocation).getColor() && currentColor != WHITE) {
				counter++;
				if (counter == 4) {
					if (this->players[0].getColor() == currentColor) {
						return 1;
					}
					else if (this->players[1].getColor() == currentColor) return 2;
				}
			}
			else {
				currentColor = getTileFrom(currentLocation).getColor();
				counter = 1;
			}
		}
	}

	//bottom left to right
	for (int i = 0; i < 4; i++) {
		currentLocation = Vector2D(i, 0);
		currentColor = this->getTileFrom(currentLocation).getColor();
		counter = 1;

		while (currentLocation.getX() < std::min(5+i, 7) && currentLocation.getY() < std::min(6, 7 - i)) {
			currentLocation.addX(1);
			currentLocation.addY(1);
			if (currentColor == getTileFrom(currentLocation).getColor() && currentColor != WHITE) {
				counter++;
				if (counter == 4) {
					if (this->players[0].getColor() == currentColor) {
						return 1;
					}
					else if (this->players[1].getColor() == currentColor) return 2;
				}
			}
			else {
				currentColor = getTileFrom(currentLocation).getColor();
				counter = 1;
			}
		}
	}

	//bottom right to left
	for (int i = 6; i > 2; i--) {
		currentLocation = Vector2D(i, 0);
		currentColor = this->getTileFrom(currentLocation).getColor();
		counter = 1;

		while (currentLocation.getX() > std::max(0, i - 5) && currentLocation.getY() < std::max(6, i + 1)) {
			currentLocation.addX(-1);
			currentLocation.addY(1);
			if (currentColor == getTileFrom(currentLocation).getColor() && currentColor != WHITE) {
				counter++;
				if (counter == 4) {
					if (this->players[0].getColor() == currentColor) {
						return 1;
					}
					else if (this->players[1].getColor() == currentColor) return 2;
				}
			}
			else {
				currentColor = getTileFrom(currentLocation).getColor();
				counter = 1;
			}
		}
	}

	//upper right to left
	for (int i = 2; i > 0; i--) {
		currentLocation = Vector2D(6, i);
		currentColor = this->getTileFrom(currentLocation).getColor();
		counter = 1;

		while (currentLocation.getX() > i && currentLocation.getY() < 6) {
			currentLocation.addX(-1);
			currentLocation.addY(1);
			if (currentColor == getTileFrom(currentLocation).getColor() && currentColor != WHITE) {
				counter++;
				if (counter == 4) {
					if (this->players[0].getColor() == currentColor) {
						return 1;
					}
					else if (this->players[1].getColor() == currentColor) return 2;
				}
			}
			else {
				currentColor = getTileFrom(currentLocation).getColor();
				counter = 1;
			}
		}
	}


	return 0;
}

Gameboard::Gameboard(Player player1, Player player2)
{
	this->players[0] = player1;
	this->players[1] = player2;

	for (int i = 0; i < 7; i++) {
		this->nextFreePlaceinColumn[i] = 0;
	}
}

Player Gameboard::getPlayer(std::string name) const
{
	Player temp1 = this->players[0];
	Player temp2 = this->players[1];

	if (name == temp1.getName()) {
		return this->players[0];
	}
	else if (name == temp2.getName()) {
		return this->players[1];
	}
	else {
		throw std::invalid_argument("There is no player with such name!\n");
	}
}

Player Gameboard::getPlayerFromIndex(int index) const
{	
	if (index == 0) return this->players[0];
	else return this->players[1];
}

Tile Gameboard::getTileFrom(Vector2D location)
{	
	return this->board[location.linearize()];

}

int Gameboard::checkGameState() //this needs to be reimplemented!!!
{
	// 0 -> ongoing
	// 1 -> player 1 won,
	// 2 -> player 2 won,
	// 3 -> draw

	int counter;

	Vector2D currentLocation;

	//checking --->
	for (int y = 0; y < 6; y++) {
		currentLocation = Vector2D(0, y);
		counter = 1;
		Color currentColor = getTileFrom(currentLocation).getColor();

		for (int x = 1; x < 7; x++) {
			currentLocation = Vector2D(x, y);
				if (currentColor == getTileFrom(currentLocation).getColor() && currentColor != WHITE) {
					counter++;
					if (counter == 4) {
						if (this->players[0].getColor() == currentColor) {
							return 1;
						}
						else if (this->players[1].getColor() == currentColor) return 2;
					}
				}
				else {
					currentColor = getTileFrom(currentLocation).getColor();
					counter = 1;
				}

		}
	}

	//checking |||| ^
	for (int x = 0; x < 7 ; x++) {
		currentLocation = Vector2D(x,0);
		counter = 1;
		Color currentColor = getTileFrom(currentLocation).getColor();

		for (int y = 1; y < 6; y++) {
			currentLocation = Vector2D(x,y);
				if (currentColor == getTileFrom(currentLocation).getColor() && currentColor != WHITE) {
					counter++;
					if (counter == 4) {
						if (this->players[0].getColor() == currentColor) {
							return 1;
						}
						else if (this->players[1].getColor() == currentColor) return 2;
					}
				}
				else {
					currentColor = getTileFrom(currentLocation).getColor();
					counter = 1;
				}
		}
	}

	//checking diagonals
	int diagonal_result = checkDiagonals();
	if (diagonal_result == 1 || diagonal_result == 2) return diagonal_result;

	//checking for empty spots
	for (int i = 0; i < 7; i++) {
		if (this->nextFreePlaceinColumn[i] < 6) {
			return 0;
		}
	}

	return 3;
}

Vector2D Gameboard::placeTile(int column)
{	
	if ( this->nextFreePlaceinColumn[column] < 6) {
		Vector2D newLocation = Vector2D(column, nextFreePlaceinColumn[column]);
		Tile toPlace = Tile(getPlayerFromIndex(this->whoseMove).getColor(), newLocation);
		this->board[newLocation.linearize()] = toPlace;
		this->nextFreePlaceinColumn[column] += 1;

		return newLocation;
	}
	else {
		throw std::invalid_argument("There is no place in this column!\n");
	}

}

void Gameboard::decideStarter()
{
	int whoWillStart = rand() % 2;
	this->whoseMove = whoWillStart;
}

void Gameboard::newTurn()
{
	this->whoseMove = (whoseMove + 1) % 2;
}

int Gameboard::getNextPlaceFrom(int columnNumber)
{
	return this->nextFreePlaceinColumn[columnNumber];
}

int Gameboard::getMove()
{
	return this->whoseMove;
}

void Gameboard::resetBoard()
{
	for (int i = 0; i < 7; i++) {
		this->nextFreePlaceinColumn[i] = 0;
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			Vector2D temp = Vector2D(i, j);
			this->board[temp.linearize()] = Tile();
		}
	}
}
