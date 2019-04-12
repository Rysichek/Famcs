// clasiia.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include"fstream"
using namespace std;


class Long {
	friend ostream &operator<<(ostream&, const Long &);
	friend istream &operator>>(istream&, Long &);
private:
	int *Array;
	int size;
public:
	Long(int);                           /*конструктор по умолчанию*/
	Long(const Long &);                  /*конструктор копирования*/
	Long(int, const Long&);              /*конструктор с параметрами*/
	~Long();                             /*деструктор*/
	bool operator==(const Long&);
	bool operator!=(const Long&);
	bool operator>(const Long&);
	bool operator<(const Long&);
	Long operator++();
	Long operator++(int notused);
	Long operator--();
	Long operator--(int notused);
	Long operator+(const Long &);
	Long operator+=(const Long &);
	Long & operator=(const Long &);
};
Long::Long(int sep)
{
	size = sep;
	Array = new int[size];
	for (int i = 0; i < size; i++)
	{
		Array[i] = 0;
	}
}
Long::Long(const Long &a)
{
	size = a.size;
	Array = new int[size];
	for (int i = 0; i < size; i++)
	{
		Array[i] = a.Array[i];
	}
}
Long::Long(int kol, const Long& b)
{
	size = b.size;
	Array = new int[size];
	Array[0] = b.Array[0] + kol;
	for (int i = 1; i < size; i++)
	{
		if (kol + b.Array[i] > 9)
		{
			Array[i - 1] = Array[i - 1] + 1;
			Array[i] = b.Array[i] + kol - 10;
		}
		else Array[i] = b.Array[i] + kol;
	}
}
Long::~Long()
{
	delete[] Array;
}

ostream &operator<<(ostream & output, const Long &a)
{
	for (int i = 0; i < a.size; i++)
	{
		output << a.Array[i];

	}

	return output;
}

istream &operator>>(istream& input, Long &a)
{
	for (int i = 0; i < a.size; i++)
	{
		input >> a.Array[i];

	}

	return input;
}

bool Long::operator==(const Long& c)
{
	int count = 0;
	if (size != c.size)
		return false;

	else {
		for (int i = 0; i < size; i++)
		{
			if (Array[i] != c.Array[i])
				count++;
		}
		if (count > 0)
			return false;
		else return true;
	}

}

bool Long::operator!=(const Long& c)
{
	int count = 0;
	if (size != c.size)
		return true;

	else {
		for (int i = 0; i < size; i++)
		{
			if (Array[i] == c.Array[i])
				count++;
		}
		if (count == size)
			return false;
		else return true;
	}

}

bool Long::operator>(const Long& c)
{
	int count = 0;
	if (size < c.size)
		return false;
	else {
		if (size > c.size)
			return true;
		else {
			for (int i = 0; i < size; i++)
			{
				if (Array[i] > c.Array[i])
				{
					return true;
					break;
				}
				if (Array[i] < c.Array[i])
				{
					return false;
					break;
				}
				if (Array[i] == c.Array[i])
					count++;
			}
		}
		if (count == size)
			return false;
	}
}

bool Long::operator<(const Long& c)
{
	int count = 0;
	if (size > c.size)
		return false;
	else {
		if (size < c.size)
			return true;
		else {
			for (int i = 0; i < size; i++)
			{
				if (Array[i] < c.Array[i])
				{
					return true;
					break;
				}
				if (Array[i] > c.Array[i])
				{
					return false;
					break;
				}
				if (Array[i] == c.Array[i])
					count++;
			}
		}
		if (count == size)
			return false;
	}
}

Long Long::operator++()
{
	Array[size - 1] = Array[size - 1] + 1;
	for (int i = size - 1; i > 0; i--)
	{
		if (Array[i] > 9)
		{
			Array[i] = Array[i] - 10;
			Array[i - 1]++;
		}
	}
	return*this;
}

Long Long::operator++(int notused)
{
	Long copy = *this;
	Array[size - 1] = Array[size - 1] + 1;
	for (int i = size - 1; i > 0; i--)
	{
		if (Array[i] > 9)
		{
			Array[i] = Array[i] - 10;
			Array[i - 1]++;
		}
	}
	return copy;
}

Long Long::operator--()
{
	Array[size - 1] = Array[size - 1] - 1;
	return*this;
}

Long Long::operator--(int notused)
{
	Long copy = *this;
	Array[size - 1] = Array[size - 1] - 1;
	return copy;
}

Long Long::operator+(const Long &c)
{
	if (size >= c.size)
	{
		Long b(*this);
		for (int i = size - 1,j = c.size - 1; j >= 0; j--, i--)
		{
			b.Array[i] = Array[i] + c.Array[j];
		}
		for (int i = b.size - 1; i > 0; i--)
		{
			if (b.Array[i] > 9)
			{
				b.Array[i] = b.Array[i] - 10;
				b.Array[i - 1]++;
			}
		}
		return b;
		}
	else {
		Long b(c);
		for (int i = size - 1, j = c.size - 1; i >= 0; j--, i--)
		{
			b.Array[j] = Array[i] + c.Array[j];
		}
		for (int i = b.size - 1; i > 0; i--)
		{
			if (b.Array[i] > 9)
			{
				b.Array[i] = b.Array[i] - 10;
				b.Array[i - 1]++;
			}
		}
		return b;
	}
	
	
}

Long Long:: operator+=(const Long &c)
{
	if (size >= c.size)
	{
		for (int i = size - 1, j = c.size - 1; j >= 0; j--, i--)
		{
			Array[i] = Array[i] + c.Array[j];
		}
		for (int i = size - 1; i > 0; i--)
		{
			if (Array[i] > 9)
			{
				Array[i] = Array[i] - 10;
				Array[i - 1]++;
			}
		}
		return *this;
	}
	else {
		for (int i = size - 1, j = c.size - 1; i >= 0; j--, i--)
		{
			c.Array[j] = Array[i] + c.Array[j];
		}
		for (int i = c.size - 1; i > 0; i--)
		{
			if (c.Array[i] > 9)
			{
				c.Array[i] = c.Array[i] - 10;
				c.Array[i - 1]++;
			}
		}
		size = c.size;
		Array = new int[size];
		for (int i = 0; i < size; i++)
		{
			Array[i] = c.Array[i];
		}
		return *this;
	}


}

Long & Long::operator=(const Long &a)
{
	if (this != &a)
	{
		delete[] Array;
		size = a.size;
		Array = new int[size];
		for (int i = 0; i < size; i++)
		{
			Array[i] = a.Array[i];
		}
	}
	return *this;
}

Long** sort(Long** a, int n)
{
	Long temp(10);
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (*a[j] > *a[j + 1])
			{
				temp = *a[j];
				*a[j] = *a[j + 1];
				*a[j + 1] = temp;
			}
		}
	}
	return a;
}

int main()
{
    fstream fin;
	fin.open("input.txt");
	int n;
	fin >> n;
	Long **Arr = new Long*[n];
	int k;
	for (int i = 0; i < n; i++)
	{
		fin >> k;
		Arr[i] = new Long(k);
		fin >> *Arr[i];
	}
	
	sort(Arr, n);
	fin.close();

	ofstream fout;
	fout.open("output.txt");
	for (int i = 0; i < n; i++)
	{
		fout << *Arr[i] << endl;
	 }
	fout << *Arr[0] + *Arr[1];

	fout.close();




	
	

	

}

