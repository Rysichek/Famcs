// Class_Polynom.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include<iostream>

using namespace std;
class Polynom
{
	friend void change(Polynom &, int, int, int);
	friend istream &operator >>(istream &, Polynom &);
	friend ostream &operator<<(ostream &, Polynom &);
private:
	int n;
	int *Kf;
public:
	Polynom();
	Polynom(int);
	Polynom(const Polynom &c);
	~Polynom();
};
Polynom::Polynom() {
	Kf = 0;
}
Polynom::Polynom(int k) {
	n = k;
	Kf = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		Kf[i] = 0;
	}
}
Polynom::Polynom(const Polynom &c) {
	n = c.n;
	Kf = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		Kf[i] = c.Kf[i];
	}
}
Polynom::~Polynom() {
	delete[]Kf;
}

istream &operator>>(istream &s, Polynom &c)
{
	for (int i = 0; i <= c.n; i++)
	{
		s >> c.Kf[i];
	}
	return s;
}

ostream &operator<<(ostream &s, Polynom &k)
{
	int count = 0;
	for (int i = 0; i < k.n; i++)
	{
		if (k.Kf[i] != 0)
			count++;
	}
	if (count != 0)
	{
		if (k.Kf[0] != 0)
		{
			s << k.Kf[0];
		}
		for (int i = 1; i <= k.n; i++)
		{
			if (k.Kf[i] < 0)
			{
				if (k.Kf[i] != -1)
					s << k.Kf[i] << "X^" << i;
				else
					s << "-" << "X^" << i;
			}
			else
			{
				if (k.Kf[i] != 0)
				{
					if (k.Kf[i] != 1)
						s << "+" << k.Kf[i] << "X^" << i;
					else
						s << "+" << "X^" << i;
				}
			}
		}
		s << endl;
	}
	else {
		s << 0;
	}
	return s;
}

void change(Polynom &c, int n1, int n2, int mean)
{
	for (int i = n1; i <= n2; i++)
	{
		c.Kf[i] = mean;
	}
}

int main()
{
	Polynom k(10);
	cout << "write down "<<11<<" numbers "<<endl;
	cin >> k;
	cout << "your polinom" << endl;
	cout << k;
	cout << endl;
	cout << "your new polinom" << endl;
	change(k, 2, 4, 31);
	cout << k;

}
