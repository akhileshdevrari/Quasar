#include <iostream>
#ifndef CMOVE_HPP
#define CMOVE_HPP
class CMove
{
	private:
		int from_i;	//row from which piece is moved
		int from_j;	//column from which piece is moved
		int to_i;		//row to which piece is moved
		int to_j;		//column to which piece is moved
		// int piece;	//piece to be moved -6 to 6 i.e Black King to White King
		int move_material;	//material gained by making move
	public:
		CMove(std::string str)
		{
			//convert a1a3 to "from [0][0] to [2][0]"
			// std::cout<<"str = "<<str<<"\n";
			from_i = str[1] - (int)'1';
			from_j = str[0] - (int)'a';
			to_i = str[3] - (int)'1';
			to_j = str[2] - (int)'a';
			move_material = 0;
		}
		//Constructor to create object when move information is given in coordinate form
		CMove(int f_i, int f_j, int t_i, int t_j)
		{
			//convert a1a3 to "from [0][0] to [2][0]"
			from_i = f_i;
			from_j = f_j;
			to_i = t_i;
			to_j = t_j;
			move_material = 0;
		}
		int _from_i()
		{
			return from_i;
		}
		int _from_j()
		{
			return from_j;
		}
		int _to_i()
		{
			return to_i;
		}
		int _to_j()
		{
			return to_j;
		}
		void print()
		{
			std::cout<<((char)(from_j+'a'));
			std::cout<<((char)(from_i+'1'));
			std::cout<<((char)(to_j+'a'));
			std::cout<<((char)(to_i+'1'));
		}
};
#endif