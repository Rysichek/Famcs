#pragma once

#include <iostream>
#include "Visitor.h"
#include"String.h"
#include"vector"

using namespace std;



class Object
{
public:
	virtual void accept(Visitor& visitor) = 0;
};


class Model : public Object {


private:
	string str;
	int ind;
	int size = 5;
	int* Arr;

public:
	friend class Iterator;
	Model()
	{

		Arr = new int[size];
		ind = 0;
	}

	Model(int kolvo)
	{
		size = kolvo;
		Arr = new int[size];
		ind = 0;
	}

	Model(Model& s)
	{
		Arr = new int[s.size];
		for (int i = 0;i < s.size;i++)
		{
			Arr[i] = s.Arr[i];
		}
		ind = s.ind;
	}

	Model(Model&& s)
	{
		Arr = s.Arr;
		ind = s.ind;
		size = s.size;
		s.ind = 0;
		s.Arr = nullptr;
	}

	Model(const initializer_list<int>& list)
	{
		size = list.size();
		Arr = new int[size];
		int i = 0;
		ind = 0;
		for (auto& x : list)
		{
			ind++;
			Arr[i] = x;
			++i;
		}


	}

	~Model()
	{
		delete[] Arr;
		ind = 0;
	}

	void pop()
	{

		if (ind != 0)
		{
			ind--;
		}
	}

	void accept(Visitor& visitor);


	bool empty_place()
	{
		if (ind < size)

			return 1;

		else return 0;
	}
	void push(int element)
	{
		if (ind < size)
		{
			Arr[ind] = element;
			ind++;
		}
		else {
			size = 2 * size;
			int* Array = new int[size];
			for (int i = 0;i < ind;i++)
			{
				Array[i] = Arr[i];
			}
			swap(Arr, Array);
			Arr[ind] = element;
			ind++;
		}
	}
	int top()
	{
		if (ind != 0)
		{
			return(Arr[ind - 1]);
		}

		else {

			if (ind == 0)
				throw exception("Mistake, Model is empty");

		}
	}
	int GetSize()
	{
		return size;
	}
	bool IsEmpty()
	{
		if (ind == 0)
			return 1;
		else return 0;
	}
	void Clear()
	{
		ind = 0;
		delete[] Arr;
		Arr = new int[size];
	}
	void Swap(Model& s)
	{
		swap(Arr, s.Arr);
		swap(ind, s.ind);
		swap(size, s.size);
	}

	string toString()
	{
		string temp;
		int per;
		string final;
		for (int i = 0;i < ind;i++)
		{
			per = Arr[i];
			while (per > 0)
			{
				temp = temp + char(per % 10);
				per = per / 10;
			}
			reverse(temp.begin(), temp.end());
			final = final + temp + ' ';
			temp.clear();
		}

		return final;
	}

	Model& operator =(Model&& s)
	{
		if (this != &s)
		{
			Swap(s);
		}
		return *this;
	}

	Model& operator =(Model& s)
	{
		if (this != &s)
		{
			Model temp(s);
			Swap(temp);
		}
		return *this;
	}

	Model operator +(Model& s)
	{
		Model c;
		for (int i = 0;i < ind;i++)
		{
			c.push(Arr[i]);
		}
		for (int i = 0; i < s.ind;i++)
		{
			c.push(s.Arr[i]);
		}
		return c;
	}

	Model& operator +=(Model& s)
	{
		for (int i = 0;i < s.ind;i++)
		{
			push(s.Arr[i]);
		}
		return *this;

	}

	bool operator == (Model& s)
	{
		if (ind != s.ind)
			return 0;
		else {
			int k = 0;
			for (int i = 0;i < ind;i++)
			{
				if (Arr[i] != s.Arr[i])
					k++;
			}
			if (k > 0)
				return 0;
			else return 1;

		}
	}

	bool operator!= (Model& s)
	{
		if (ind != s.ind)
			return 1;
		else {
			int k = 0;
			for (int i = 0;i < ind;i++)
			{
				if (Arr[i] == s.Arr[i])
					k++;
			}
			if (k > 0)
				return 0;
			else return 1;

		}

	}

	friend ostream& operator<<(ostream& out, Model& s);
	friend istream& operator>>(istream& in, Model& c)
	{
		for (int i = 0; i < c.GetSize(); i++)
		{
			in >> c.Arr[i];
			c.ind++;
		}
		return in;
	}

	int* GetArray()
	{
		return Arr;
	}
	int GetInd()
	{
		return ind;
	}

	Iterator createIterator();
};













class Iterator
{

private:
	int _current;
	Model* ptr_collection;
public:
	Iterator(Model* s)
	{
		ptr_collection = s;
		_current = 0;
	}
	void next()
	{
		_current++;
	}
	void first()
	{
		_current = 0;
	}
	bool isDone()
	{
		if (_current < ptr_collection->GetInd())
			return 0;
		else return 1;
	}
	int& current()
	{
		if (isDone() == 1)
		{
			throw exception("Mistake! Out of range");
		}
		else return ptr_collection->Arr[_current];
	}
};


Iterator  Model::createIterator()
{
	return Iterator(this);
}


ostream& operator<<(ostream& out, Model& s)
{
	cout << "Elements of your Model :" << endl;
	Iterator it = s.createIterator();
	for (it.first();it.isDone() != 1;it.next())
	{
		out << it.current() << " ";
	}
	return out;
}

void Model::accept(Visitor& visitor)
{
	Iterator it = this->createIterator();
	for (it.first();it.isDone() != 1;it.next())
	{
		visitor.visit(it.current());
	}
}
