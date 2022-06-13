#pragma once
#include "Tile.h"
#include "Vector2D.h"
#include "Player.h"

class Gameboard
{
	private:
		Tile board[42];
		Player players[2];
		int nextFreePlaceinColumn[7];
		int whoseMove;
		int checkDiagonals();

	public:
		Gameboard() {

		}
		Gameboard(Player, Player);
		Player getPlayer(std::string) const;
		Player getPlayerFromIndex(int) const;
		Tile getTileFrom(Vector2D);
		int checkGameState();
		Vector2D placeTile(int);
		void decideStarter();
		void newTurn();
		int getNextPlaceFrom(int);
		int getMove();
		void resetBoard();
		
};

