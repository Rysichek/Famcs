// ConsoleApplication14.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
using namespace std;
int main()
{
	cout << "how many lines do you need?" << endl;
	int size;
	int **A;
	cin >> size;
	A = new int*[size];
	for (int i = 0; i < size; i++)
		A[i] = new int[size];
	for (int i = 0; i < size; i++)

		for (int j = 0; j < size; j++)
		{
			A[i][j] = 0;
			A[i][0] = 1;
			A[i][i] = 1;

		}
	for (int i = 1; i < size; i++)

		for (int j = 1; j < size; j++)
		{
			A[i][j] = A[i - 1][j - 1] + A[i - 1][j];

		}
	cout << "your Paskal triangle" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}
}