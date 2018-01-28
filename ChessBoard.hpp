#include <iostream>
#include "CMove.hpp"
#include "CMovesList.hpp"
#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP
class chessboard
{
	private:
		int board[8][8];
		int side_to_move; // 1 means White's turn to move, -1 means Black's turn to move
	public:
		chessboard(){
			newgame();
		}
		int whose_turn();
		void newgame();
		void printboard();
		void makemove(CMove move);
		void find_legal_moves(CMovesList &moveslist);//finds all possible legal moves and inserts them in CmovesList object
		bool is_move_valid(CMove &move); //returns true if move is valid
		int material();
};
#endif