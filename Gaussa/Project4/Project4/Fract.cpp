// ConsoleApplication12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;

class Fraction {
public:
	Fraction()
	{
		nom = 0;
		denom = 0;
	}
	Fraction(int n, int d)
	{
		nom = n;
		denom = d;
	}
	Fraction operator*(const Fraction&c)
	{
		Fraction k;
		k.nom = nom * c.nom;
		k.denom = denom * c.denom;
		k.cancellation();
		return k;
	}
	Fraction operator/(const Fraction&c)
	{
		Fraction k;
		k.nom = nom * c.denom;
		k.denom = denom * c.nom;
		k.cancellation();
		return k;
	}
	Fraction operator = (const Fraction&c)
	{
		nom = c.nom;
		denom = c.denom;
		(*this).cancellation();
		return *this;
	}
	void sign()
	{
		if (nom > 0 && denom < 0)
		{
			nom = -nom;
			denom = -denom;
		}
		if (nom < 0 && denom < 0)
		{
			nom = -nom;
			denom = -denom;
		}
		if (nom == 0)
		{
			denom = 0;
		}
	}
	Fraction operator+(const Fraction&l)
	{
		Fraction f;
		f.denom = denom * l.denom;
		f.nom = nom * l.denom + l.nom*denom;
		f.cancellation();
		return f;
	}
	Fraction operator-	(const Fraction&l)
	{
		Fraction f;
		f.denom = denom * l.denom;
		f.nom = nom * l.denom - l.nom*denom;
		f.cancellation();
		return f;
	}
	Fraction cancellation()
	{
		int nom1, denom1;
		nom1 = abs(nom);
		denom1 = abs(denom);
		if (nom1 != 0 && denom1 != 1)
		{
			while (nom1 != denom1)
			{
				if (nom1 > denom1)
					nom1 = nom1 - denom1;
				else
					denom1 = denom1 - nom1;
			}

			if (denom1 != 0 && nom1 != 0)
			{
				denom = denom / denom1;
				nom = nom / nom1;
			}
		}
		return *this;
	}
	friend istream &operator >> (istream &in, Fraction &c)
	{
		c.nom = 0;
		string str;
		getline(in, str);
		int sign = (str[0] == '-' ? -1 : 1);
		size_t i = (str[0] == '-' ? 1 : 0);
		for (; isdigit(str[i]) && i < str.length(); i++)
			c.nom = c.nom * 10 + (str[i] - '0');
		c.nom *= sign;
		if (i == str.length())
			c.denom = 1;
		else
		{
			c.denom = 0;
			for (i++; isdigit(str[i]) && i < str.length(); i++)
				c.denom = c.denom * 10 + (str[i] - '0');
		}
		return in;
	}
	friend ostream &operator<<(ostream&out, Fraction &k)
	{
		k.sign();

		if (k.nom == 0)
		{
			out << 0 << endl;
		}
		else
		{
			if (k.denom == 1)
			{
				out << k.nom << endl;
			}
			else {
				out << k.nom << "/" << k.denom << endl;
			}
		}

		return out;
	}
	int getNom()
	{
		return nom;
	}
private:
	int nom;
	int denom;
};



