// Method Haffmana_decode.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <queue>
#include <bitset>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

ifstream in("D:\\pr\\Method Haffmana\\Method Haffmana\\key.txt");
ifstream tex("D:\\pr\\Method Haffmana\\Method Haffmana\\out.txt");
ifstream nb("D:\\pr\\Method Haffmana\\Method Haffmana\\number.txt");

typedef pair<char, string> decode;


int main()
{
	vector<decode> vect;
	vector<decode>::iterator i;
	vector<bitset<8>> v;
	vector<bitset<8>>::iterator it;
	string tmp;
		while (!in.eof())
		{
			string a;
			char ch;
			getline(in, tmp);
			ch=tmp[0];
			for (int j = 2; j < tmp.size(); j++)
			{
				a.push_back(tmp[j]);
			}
			vect.push_back(make_pair(ch, a));
		}
		in.close();

		char ch;

		while (tex.get(ch))
		{
			bitset<8> b(ch);
			cout << endl;
			v.push_back(b);
		}

		int counter = 0;


		string example = "";

		int count;
		nb >> counter;
		int iter = 0;

			for (it = v.begin(); it != v.end(); it++)
			{
				if (iter == counter)
					break;
				bitset <8> m = *it;
				for (int j = 7; j >= 0; j--)
				{
					if (iter == counter)
						break;
					if (m[j] == 0)
					{
						example = example + '0';
					}
					else {
						example = example + '1';
					}
					int c = 0;
					for (i = vect.begin(); i != vect.end(); i++)
					{
						if (i->second == example)
						{
							cout << i->first;
							c++;
							iter++;
						}
					}
					if (c != 0)
					{
						example = "";
					}
				}
			}
		

}

