#include <iostream>
#include "ChessBoard.hpp"
#include "ai.hpp"
#include "CMove.hpp"

int main(int argc, char const *argv[])
{
	chessboard board;
	std::string choice;
	while(1)
	{
		board.printboard();
		if(board.whose_turn()==1)
			std::cout<<"White's turn\n";
		else std::cout<<"Black's turn\n";
		std::cout<<"\nChoose Command:     move  show  quit\n";
		getline(std::cin, choice);
		if(choice.compare(0,5,"move ")==0)
		{
			CMove move(choice.substr(5));
			board.makemove(move);
		}
		else if(choice == "show")
		{
			ai engine(board);
			std::cout<<"\nLegal moves are\n";
			engine.search();
		}
		else if(choice == "quit")
			break;
		else std::cout<<"Invalid Command\n";
	}
	return 0;
}