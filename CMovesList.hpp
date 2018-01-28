#include <iostream>
#include <vector>
#include "CMove.hpp"
#ifndef CMOVESLIST_HPP
#define CMOVESLIST_HPP
class CMovesList
{
	private:
		std::vector<CMove> moveslist;
	public:
		void push_back(const CMove &move)
		{
			moveslist.push_back(move);
		}
		void clear()
		{
			moveslist.clear();
		}
		int size()
		{
			return moveslist.size();
		}
		void print()
		{
			for(std::vector<CMove>::iterator it = moveslist.begin(); it != moveslist.end(); it++)
			{
				(*it).print();
				std::cout<<"\n";
			}
		}
};
#endif