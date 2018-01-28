#include <iostream>
#include "ChessBoard.hpp"
#include "CMove.hpp"
#include "CMovesList.hpp"
#ifndef AI_HPP
#define AI_HPP
class ai
{
	private:
		chessboard board;
	public:
		ai(chessboard _board)
		{
			board = _board;
		}
		void search()
		{
			CMovesList moveslist;
			board.find_legal_moves(moveslist);
			moveslist.print();
		}
};
#endif