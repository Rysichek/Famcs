// Usik.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// ConsoleApplication12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <string>
#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>
#include <list>
#include <map>
#include <vector>

using namespace std;

struct  Flower {

	pair <string, string> flow;
	string forma;
	int numflow_b;
	Flower(int num, string form, string n_fl, string year)
	{
		numflow_b = num;
		forma = form;
		flow.first = year;
		flow.second = n_fl;
	}

	Flower()
	{
		numflow_b = 0;
		forma = "";
		flow.first = "";
		flow.second = "";
	}
	friend ostream & operator << (ostream &OS, Flower Bus_);
	friend istream & operator >> (istream &IS, Flower& Bus_);
};


ostream & operator << (ostream &OS, Flower Fl)
{
	OS << Fl.numflow_b << " " << Fl.forma << " " << Fl.flow.first << " " << Fl.flow.second << "\n";
	return OS;
}
istream & operator >> (istream &IS, Flower& Fl)
{
	IS >> Fl.numflow_b >> Fl.forma >> Fl.flow.first >> Fl.flow.second;
	return IS;
}


void list_fl(multimap<int, Flower> &m, int k)
{
	cout << "the amount of flowers on "<<k<<" flower bed"<<endl;
	multimap<int, Flower>::iterator it;
	bool a = 0;
	for (it = m.begin(); it != m.end(); ++it)
	{
		if (k == it->first)
		{
			cout << it->second.flow.second << " ";
			a = 1;
		}

	}
	if (a == 0)
	{
		cout << "there is no such flower bed" << endl;
	}
}

void list_different(multimap<int, Flower> &m)
{
	cout << "the amount of all the flowers" << endl;
	multimap<int, Flower>::iterator it;
	list<string> listik;
	list<string>::iterator k;
	for (it = m.begin(); it != m.end(); ++it)
	{
		string s;
		s=it->second.flow.second;
		listik.push_back(s);
	}
	listik.sort();
	listik.unique();
	for (k= listik.begin(); k != listik.end(); ++k)
	{
		cout << (*k) << " ";
	}
}

void flower_anywhere(multimap<int, Flower> &m)
{
	cout << "the flower, which is on every flower bed" << endl;

	typedef pair<int, string> par;
    list<par> listik;
	list<par>::iterator k;
	

	multimap<int, Flower>::iterator it;
	
	list<int> l;

	for (it = m.begin(); it != m.end(); ++it)
	{
		string s;
		s = it->second.flow.second;
		int k = 0;
		pair<int, string> f;
		f = make_pair(k, s);
		listik.push_back(f);
		l.push_back(it->first);
	}
	l.unique();
	int count = l.size();
	listik.sort();
	listik.unique();


	for (it = m.begin(); it != m.end(); ++it)
	{

		for (k = listik.begin(); k != listik.end(); k++)
		{
			if (it->second.flow.second == k->second)
			{
				k->first++;
			}
		}
	}

	for (k = listik.begin(); k != listik.end(); ++k)
	{
		
		if (k->first == count)
		{
			cout << k->second << " ";
		}

	}
}

void maxfl_cl(multimap<int, Flower> &m)
{
	multimap<int, Flower>::iterator it;
	cout << "the flower bed with max amount of flowers" << endl;
	typedef pair<int, int> par;
	list<par> l;
	list<par>::iterator k;
	for (it = m.begin(); it != m.end(); it++)
	{
		l.push_back(make_pair(0, it->first));
	}
	l.sort();
	l.unique();

	for (it = m.begin(); it != m.end(); it++)
	{
		for (k = l.begin(); k != l.end(); k++)
		{
			if (it->first == k->second)
			{
				k->first++;
			}
		}
	}
	int max = 0;
	int min = 1000;
	for (k = l.begin(); k != l.end(); k++)
	{
		if (k->first > max)
			max = k -> first;
		if (k->first < min)
			min = k->first;
	}
	for (k = l.begin(); k != l.end(); k++)
	{
		if (k->first == max)
		{
			cout << k->second << " flower bed with " << k->first <<" flowers "<<endl;
		}
	}
	cout << endl;

}

int main()
{
	ifstream ifile("in.txt");
	Flower fl;
	list <Flower> fl_list;
	list <Flower> ::iterator i;

	while (!ifile.eof())
	{
		ifile >> fl;
		fl_list.push_back(fl);
	}

	cout << "Our list of flowers " << endl<<endl;
	for (i = fl_list.begin(); i != fl_list.end(); i++)
	{
		cout << (*i);
	}



	for (int i = 0; i < 20; i++)
	{
		cout << "***";
	}
	cout << endl;

	cout << "Our list of flowers after sort of number flowerbeds" << endl << endl;
	fl_list.sort([](Flower & k, Flower & f)
	{
		return f.numflow_b > k.numflow_b;
	});
	for (i = fl_list.begin(); i != fl_list.end(); i++)
	{
		cout << (*i);
	}


	for (int i = 0; i < 20; i++)
	{
		cout << "***";
	}
	cout << endl;

	multimap <int, Flower> mapFl;
	multimap<int, Flower>::iterator it;
	for (i = fl_list.begin(); i != fl_list.end(); i++)
	{
		mapFl.insert(make_pair(i->numflow_b, *i));
	}

	
	cout << "Our multimap amount of flowers" << endl << endl;;

	for (it = mapFl.begin(); it != mapFl.end(); it++)
	{
		cout << it->first << " " << it->second;
	}

	for (int i = 0; i < 20; i++)
	{
		cout << "***";
	}
	cout << endl;

	cout << "write down number of the flower-bed " << endl<<endl;
	int n;
	cin >> n;
	list_fl(mapFl, n);
	cout << endl;
	for (int i = 0; i < 20; i++)
	{
		cout << "***";
	}
	cout << endl;
	list_different(mapFl);
	cout << endl;
	for (int i = 0; i < 20; i++)
	{
		cout << "***";
	}
	cout << endl;
	flower_anywhere(mapFl);
	cout << endl;
	for (int i = 0; i < 20; i++)
	{
		cout << "***";
	}
	cout << endl;
	maxfl_cl(mapFl);
}


