#include <iostream>
#include <stdlib.h>
#include "ChessBoard.hpp"
#include "CMove.hpp"
#include "CMovesList.hpp"

//Colors to show game on console
#define WHITE "[33m"	//For White pieces
#define BLACK   "[30m" //For Black pieces
#define EMPTY   "[0m" //For Empty cells in board
#define SIDEBAR "[0m" //SIDEBAR consisting a,b...h and 1,2,...8
#define RESET "[0m" //Default value

// Chess board is a 8*8 int matrix
// Each element contains one of the following values:
//   0  :  Empty
//   1  :  White Pawn
//   2  :  White Knight
//   3  :  White Bishop
//   4  :  White Rook
//   5  :  White Queen
//   6  :  White King
//   -1 :  Black Pawn
//   -2 :  Black Knight
//   -3 :  Black Bishop
//   -4 :  Black Rook
//   -5 :  Black Queen
//   -6 :  Black King


void chessboard::newgame()
{
	side_to_move = 1; //White moves first
	//Initializing empty board
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			board[i][j] = 0;
		}
	}
	// Setting initial configuration as
	// 	   BLACK SIDE
	// 8 R N B Q K B N R
	// 7 P P P P P P P P
	// 6 . . . . . . . .
	// 5 . . . . . . . .
	// 4 . . . . . . . .
	// 3 . . . . . . . .
	// 2 P P P P P P P P
	// 1 R N B Q K B N R
	//  a b c d e f g h
	// 	   WHITE SIDE
	board[0][0] = board[0][7] = 4; //White Rook
	board[0][1] = board[0][6] = 2; //White Knight
	board[0][2] = board[0][5] = 3; //White Bishop
	board[0][3] = 5; //White Queen
	board[0][4] = 6; //White King
	board[7][0] = board[7][7] = -4; //Black Rook
	board[7][1] = board[7][6] = -2; //Black Knight
	board[7][2] = board[7][5] = -3; //Black Bishop
	board[7][3] = -5; //Black Queen
	board[7][4] = -6; //Black King
	//Pawns
	for (int i = 0; i < 8; ++i)
	{
		board[1][i] = 1;
		board[6][i] = -1;
	}
}


void chessboard::printboard()
{
	for (int i = 7; i >= 0; --i)
	{
		std::cout<<SIDEBAR<<(i+1)<<" ";
		for (int j = 0; j < 8; ++j)
		{
			switch(board[i][j])
			{
				case 0:	std::cout<<EMPTY<<"."<<" ";
						break;
				case 1:	std::cout<<WHITE<<"P"<<" ";
						break;
				case 2:	std::cout<<WHITE<<"N"<<" ";
						break;
				case 3:	std::cout<<WHITE<<"B"<<" ";
						break;
				case 4:	std::cout<<WHITE<<"R"<<" ";
						break;
				case 5:	std::cout<<WHITE<<"Q"<<" ";
						break;
				case 6:	std::cout<<WHITE<<"K"<<" ";
						break;
				case -1: std::cout<<BLACK<<"P"<<" ";
						break;
				case -2: std::cout<<BLACK<<"N"<<" ";
						break;
				case -3: std::cout<<BLACK<<"B"<<" ";
						break;
				case -4: std::cout<<BLACK<<"R"<<" ";
						break;
				case -5: std::cout<<BLACK<<"Q"<<" ";
						break;
				case -6: std::cout<<BLACK<<"K"<<" ";
						break;
			}
		}
		std::cout<<std::endl<<RESET;
	}
	std::cout<<SIDEBAR<<"  a b c d e f g h\n";
}

bool chessboard::is_move_valid(CMove &move)
{
	// std::cout<<"is_move_valid me aaya  ";
	// move.print();
	// Check if move includes a cell out of bound
	if(move._from_i() < 0 or move._from_i() > 7 or move._from_j() < 0 or move._from_j() > 7)
		return false;
	// std::cout<<"   one   ";
	if(move._to_i() < 0 or move._to_i() > 7 or move._to_j() < 0 or move._to_j() > 7)
		return false;
	// std::cout<<"   two   ";
	//"From" cell cannot be empty
	if(board[move._from_i()][move._from_j()] == 0)
		return false;
	// std::cout<<"   three   ";
	// White Pawn
	// if(board[move._from_i()][move._from_j()] == 1)
	// {
	// 	// std::cout<<"   four   \n";
	// 	//White pawn captures black piece
	// 	if(move._to_i() == move._from_i()+1 and abs(move._to_j() - move._from_j())==1 and board[move._to_i()][move._to_j()] < 0)
	// 		return true;
	// 	// std::cout<<"   five   \n";
	// 	//White pawn moves one cell ahead
	// 	if(move._to_i() == move._from_i()+1 and move._to_j() == move._from_j() and board[move._to_i()][move._to_j()] == 0)
	// 		return true;
	// 	// std::cout<<"   six   \n";
	// 	//White pawn moves two cells ahead
	// 	if(move._to_i() == move._from_i()+2 and move._to_j() == move._from_j() and board[move._to_i()][move._to_j()] == 0 and board[move._to_i()-1][move._to_j()] == 0 and move._from_i()==1)
	// 		return true;
	// 	// std::cout<<"   seven  \n";
	// 	return false;
	// }
	// std::cout<<"   eight   \n";

	//Check if a piece is capturing it's own teammates
	if(board[move._from_i()][move._from_j()]*board[move._to_i()][move._to_j()] > 0)
		return false;

	return true;
}


// Find all legal moves in current board position and store it in moveslist
void chessboard::find_legal_moves(CMovesList &moveslist)
{
	// std::cout<<"arey bhai bhai bhai\n";
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			if(side_to_move == 1) //White's turn to move
			{
				// std::cout<<"arey\n";
				//White Pawn, possible moves from [i][j] are [i+1][j], [i+2][j], [i+1][j-1], [i+1][j+1]
				//Other things I leave for future are promotion, en passent, etc.
				if(board[i][j] == 1)
				{
					CMove move1(i, j, i+1, j);
					CMove move2(i, j, i+2, j);
					CMove move3(i, j, i+1, j+1);
					CMove move4(i, j, i+1, j-1);
					// std::cout<<"ye b ho raha h\n";
					if(is_move_valid(move1))
					{
						// std::cout<<"atleast ye aaya\n";
						moveslist.push_back(move1);
					}
					if(is_move_valid(move2) and i==1) //Only in first move, pawn can go two place ahead
						moveslist.push_back(move2);
					if(is_move_valid(move3) and board[i+1][j+1] < 0)//Captures a black piece
						moveslist.push_back(move3);
					if(is_move_valid(move4) and board[i+1][j-1] < 0)//Captures a black piece
						moveslist.push_back(move4);
				}

				//White Knight can go to [i+-2][j+-1] and [i+-1][j+-2]
				if(board[i][j] == 2)
				{
					CMove move1(i, j, i+2, j+1);
					CMove move2(i, j, i+2, j-1);
					CMove move3(i, j, i-2, j+1);
					CMove move4(i, j, i-2, j-1);
					CMove move5(i, j, i+1, j+2);
					CMove move6(i, j, i+1, j-2);
					CMove move7(i, j, i-1, j+2);
					CMove move8(i, j, i-1, j-2);
					if(is_move_valid(move1))
						moveslist.push_back(move1);
					if(is_move_valid(move2))
						moveslist.push_back(move2);
					if(is_move_valid(move3))
						moveslist.push_back(move3);
					if(is_move_valid(move4))
						moveslist.push_back(move4);
					if(is_move_valid(move5))
						moveslist.push_back(move5);
					if(is_move_valid(move6))
						moveslist.push_back(move6);
					if(is_move_valid(move7))
						moveslist.push_back(move7);
					if(is_move_valid(move8))
						moveslist.push_back(move8);
				}

				//White Bishop can go diagonally
				if(board[i][j] == 3)
				{
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j-k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j-k] != 0)
								break;
						}
						else break;
					}
				}

				//White rook
				if(board[i][j] == 4)
				{
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i][j-k] != 0)
								break;
						}
						else break;
					}
				}

				//White Queen
				if(board[i][j] == 5)
				{
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j-k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j-k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i][j-k] != 0)
								break;
						}
						else break;
					}
				}

				//White King
				if(board[i][j] == 6)
				{
					CMove move1(i, j, i+1, j);
					CMove move2(i, j, i-1, j);
					CMove move3(i, j, i, j+1);
					CMove move4(i, j, i, j-1);
					CMove move5(i, j, i+1, j+1);
					CMove move6(i, j, i+1, j-1);
					CMove move7(i, j, i-1, j+1);
					CMove move8(i, j, i-1, j-1);
					if(is_move_valid(move1))
						moveslist.push_back(move1);
					if(is_move_valid(move2))
						moveslist.push_back(move2);
					if(is_move_valid(move3))
						moveslist.push_back(move3);
					if(is_move_valid(move4))
						moveslist.push_back(move4);
					if(is_move_valid(move5))
						moveslist.push_back(move5);
					if(is_move_valid(move6))
						moveslist.push_back(move6);
					if(is_move_valid(move7))
						moveslist.push_back(move7);
					if(is_move_valid(move8))
						moveslist.push_back(move8);
				}
			}

			else // Black's turn
			{
				//Black Pawn, possible moves from [i][j] are [i-1][j], [i-2][j], [i-1][j-1], [i-1][j+1]
				//Other things I leave for future are promotion, en passent, etc.
				if(board[i][j] == -1)
				{
					CMove move1(i, j, i-1, j);
					CMove move2(i, j, i-2, j);
					CMove move3(i, j, i-1, j+1);
					CMove move4(i, j, i-1, j-1);
					if(is_move_valid(move1))
						moveslist.push_back(move1);
					if(is_move_valid(move2) and i==6) //Only here, black pawn can go two steps ahead, i.e in beginning
						moveslist.push_back(move2);
					if(is_move_valid(move3) and board[i-1][j+1] > 0) //Captures a white piece
						moveslist.push_back(move3);
					if(is_move_valid(move4) and board[i-1][j-1] > 0) //Captures a white piece
						moveslist.push_back(move4);
				}

				//Black Knight can go to [i+-2][j+-1] and [i+-1][j+-2]
				if(board[i][j] == -2)
				{
					CMove move1(i, j, i+2, j+1);
					CMove move2(i, j, i+2, j-1);
					CMove move3(i, j, i-2, j+1);
					CMove move4(i, j, i-2, j-1);
					CMove move5(i, j, i+1, j+2);
					CMove move6(i, j, i+1, j-2);
					CMove move7(i, j, i-1, j+2);
					CMove move8(i, j, i-1, j-2);
					if(is_move_valid(move1))
						moveslist.push_back(move1);
					if(is_move_valid(move2))
						moveslist.push_back(move2);
					if(is_move_valid(move3))
						moveslist.push_back(move3);
					if(is_move_valid(move4))
						moveslist.push_back(move4);
					if(is_move_valid(move5))
						moveslist.push_back(move5);
					if(is_move_valid(move6))
						moveslist.push_back(move6);
					if(is_move_valid(move7))
						moveslist.push_back(move7);
					if(is_move_valid(move8))
						moveslist.push_back(move8);
				}

				//Black Bishop
				if(board[i][j] == 3)
				{
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j-k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j-k] != 0)
								break;
						}
						else break;
					}
				}

				//Black rook
				if(board[i][j] == 4)
				{
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i][j-k] != 0)
								break;
						}
						else break;
					}
				}

				//Black Queen
				if(board[i][j] == -5)
				{
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j-k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j-k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i+k, j);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i+k][j] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i-k, j);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i-k][j] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i, j+k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i][j+k] != 0)
								break;
						}
						else break;
					}
					for(int k=0; k<8; k++)
					{
						CMove move(i, j, i, j-k);
						if(is_move_valid(move))
						{
							moveslist.push_back(move);
							if(board[i][j-k] != 0)
								break;
						}
						else break;
					}
				}

				//Black King
				if(board[i][j] == -6)
				{
					CMove move1(i, j, i+1, j);
					CMove move2(i, j, i-1, j);
					CMove move3(i, j, i, j+1);
					CMove move4(i, j, i, j-1);
					CMove move5(i, j, i+1, j+1);
					CMove move6(i, j, i+1, j-1);
					CMove move7(i, j, i-1, j+1);
					CMove move8(i, j, i-1, j-1);
					if(is_move_valid(move1))
						moveslist.push_back(move1);
					if(is_move_valid(move2))
						moveslist.push_back(move2);
					if(is_move_valid(move3))
						moveslist.push_back(move3);
					if(is_move_valid(move4))
						moveslist.push_back(move4);
					if(is_move_valid(move5))
						moveslist.push_back(move5);
					if(is_move_valid(move6))
						moveslist.push_back(move6);
					if(is_move_valid(move7))
						moveslist.push_back(move7);
					if(is_move_valid(move8))
						moveslist.push_back(move8);
				}
			}
		}
	}
}

void chessboard::makemove(CMove move)
{
	board[move._to_i()][move._to_j()] = board[move._from_i()][move._from_j()];
	board[move._from_i()][move._from_j()] = 0;
	side_to_move *= -1;
	// std::cout<<"_from_i = "<<move._from_i()<<"  _from_j = "<<move._from_j()<<"\n";
}


//Gives material score to side_to_move in static position
//Side_to_move will have positive score if it is winning, irrespective of it is black or white
int chessboard::material()
{	
	//More legal moves in hand, better you are in game
	CMovesList moves;
	find_legal_moves(moves);
	int num_moves_self = moves.size();
	moves.clear();
	side_to_move *= -1;
	find_legal_moves(moves);
	int num_moves_opp = moves.size();
	side_to_move *= -1;

	int value = 0;
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			switch(board[i][j])
			{
				case 1:	value += 10; break;
				case 2: value += 30; break;
				case 3: value += 30; break;
				case 4: value += 50; break;
				case 5: value += 90; break;
				case -1: value -=10; break;
				case -2: value -= 30; break;
				case -3: value -= 30; break;
				case -4: value -= 50; break;
				case -5: value -= 90; break;
			}
		}
	}

	if(side_to_move == 1)
		return (num_moves_self - num_moves_opp + value);
	else return (num_moves_self - num_moves_opp - value);
}

int chessboard::whose_turn()
{
	return side_to_move;
}