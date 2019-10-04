#pragma once


#include <iostream>
#include <initializer_list> // для std::initializer_list	
using namespace std;



class Stack {
private:
	int ind;
	int size = 5;
	int* Arr;

public:

	Stack()
	{
		Arr = new int[size];
		ind = 0;
	}

	Stack(int kolvo)
	{
		size = kolvo;
		Arr = new int[size];
		ind = 0;
	}

	Stack(Stack& s)
	{
		Arr = new int[s.size];
		for (int i = 0;i < s.size;i++)
		{
			Arr[i] = s.Arr[i];
		}
		ind = s.ind;
	}

	Stack(Stack&& s)
	{
		Arr = s.Arr;
		ind = s.ind;
		size = s.size;
		s.ind = 0;
		s.Arr = nullptr;
	}

	Stack(const initializer_list<int>& list)
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

	~Stack()
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
		else return -1;
	}
	int Size()
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
	void Swap(Stack& s)
	{
		swap(Arr, s.Arr);
		swap(ind, s.ind);
		swap(size, s.size);

	}

	Stack& operator =(Stack&& s)
	{
		if (this != &s)
		{
			Swap(s);
		}
		return *this;
	}

	Stack& operator =(Stack& s)
	{
		if (this != &s)
		{
			Stack temp(s);
			Swap(temp);
		}
		return *this;
	}

	Stack operator +(Stack& s)
	{
		Stack c;
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

	Stack& operator +=(Stack& s)
	{
		for (int i = 0;i < s.ind;i++)
		{
			push(s.Arr[i]);
		}
		return *this;

	}

	bool operator == (Stack& s)
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

	bool operator!= (Stack& s)
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

	friend ostream& operator<<(ostream& out, Stack& s)
	{
		cout << "Elements of your stack :" << endl;
		Stack::Iterator it = Stack::Iterator(s.begin());
		while (it != s.end())
		{
			out << *it << " ";
			it++;
		}
		return out;
	}
	friend istream& operator>>(istream& in, Stack& c)
	{
		for (int i = 0; i < c.Size(); i++)
		{
			in >> c.Arr[i];
			c.ind++;
		}
		return in;
	}
	class Iterator;

	Iterator createIterator()
	{
		return Iterator(Arr);
	}

	Iterator begin()
	{
		return Iterator(Arr);
	}
	Iterator end()
	{
		return Iterator(Arr + ind);
	}


	class Iterator
	{

	private:
		int* current;
	public:

		Iterator(int* x)
		{
			current = x;
		}
    

		Iterator& operator ++()
		{
			current++;
			return *this;
		}

		Iterator& operator ++(int)
		{
			Iterator temp(*this);
			this->current++;
			return temp;
		}

		Iterator& operator --()
		{
			current--;
			return *(this);
		}
		Iterator& operator --(int)
		{
			Iterator temp(*this);
			this->current--;
			return temp;
		}
		bool operator !=(Iterator const& x)
		{
			return current != x.current;


		}
		bool operator ==(Iterator const& x)
		{
			return current == x.current;


		}
		int& operator* ()
		{
			return *current;
		}

		
	};


};
