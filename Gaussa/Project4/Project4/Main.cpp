// ConsoleApplication6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include"Fract.cpp"
#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

int main()
{
	int i, j, n, m;
	cout << "Number of equations: ";
	cin >> n;
	cout << "Number of variables: ";
	cin >> m;
	m += 1;
	Fraction **Arr = new Fraction *[n];
	cin.ignore();
	for (i = 0; i < n; i++)
	{
		Arr[i] = new Fraction[m];
		for (j = 0; j < m; j++)
		{
			cout << " Element " << "[" << i + 1 << " , " << j + 1 << "]: ";
			cin >> Arr[i][j];
		}
	}
	cout << endl;

	
	Fraction  tmp;
	int k;
	Fraction *xx = new Fraction[m];

	for (i = 0; i < n; i++)
	{
		tmp = Arr[i][i];
		for (j = n; j >= i; j--)
			Arr[i][j] = Arr[i][j]/tmp;
		for (j = i + 1; j < n; j++)
		{
			tmp = Arr[j][i];
			for (k = n; k >= i; k--)
				Arr[j][k] = Arr[j][k]-tmp * Arr[i][k];
		}
	}

	xx[n - 1] = Arr[n - 1][n];
	for (i = n - 2; i >= 0; i--)
	{
		xx[i] = Arr[i][n];
		for (j = i + 1; j < n; j++) xx[i] = xx[i]- Arr[i][j] * xx[j];
	}

	
	for (i = 0; i < n; i++)
		cout << xx[i] << " ";
	cout << endl;

	delete[] Arr;
	system("pause");
	return 0;
}