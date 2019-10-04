#pragma once

//#include "Stack.h"
#include "Stack,Iterator.h"

using namespace std;

class Visitor
{
public:
	virtual void visit(int& s) = 0;

};



class GetMax_Numb :public Visitor
{
private:
	int max;
public:
	GetMax_Numb()
	{
		max = INT_MIN;
	}
	void visit(int& s)
	{
		if (s > max)
		{
			max = s;
		}
	}
	int GetNumb()
	{
		return max;
	}

};