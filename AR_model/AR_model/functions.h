#pragma once
#include <vector>
#include <math.h>
#include <string>
//метод Качмажа-решение слау
vector<double> kazf(vector<double> a, vector<double> b, int nn, int ny)
{

	// nn - количество неизвестных;  ny - количество уравнений
	double eps = 1.e-6;
	vector<double> x(nn);
	//float s;
	int i, j, k;
	double s1, s2, fa1, t;
	vector<double> x1(nn);

	x[0] = 0.5;
	for (i = 1; i < nn; i++)  x[i] = 0.;

	s1 = s2 = 1.;
	while (s1 > eps * s2)
	{
		for (i = 0; i < nn; i++) x1[i] = x[i];

		for (i = 0; i < ny; i++)
		{
			s1 = 0.0;
			s2 = 0.0;
			for (j = 0; j < nn; j++)
			{
				fa1 = a[i * nn + j];
				s1 += fa1 * x[j];
				s2 += fa1 * fa1;
			}
			t = (b[i] - s1) / s2;
			x[0] = 1;
			for (k = 1; k < nn; k++)    x[k] += a[i * nn + k] * t;
		}

		s1 = 0.0;
		s2 = 0.0;
		for (i = 0; i < nn; i++)
		{
			s1 += (x[i] - x1[i]) * (x[i] - x1[i]);
			s2 += x[i] * x[i];
		}
		s1 = (double)sqrt(s1);
		s2 = (double)sqrt(s2);
	}
	return x;
}

//поиск максимального по модулю элемента в векторе
double MaxElement(vector <double> x)
{
	double max = abs(x[0]);
	for (int i = 1; i < x.size(); i++)
	{
		if (max <= abs(x[i])) max = abs(x[i]);
	}
	return max;
}

CString toCString(string  str)
{
	return CString(str.c_str());
}
