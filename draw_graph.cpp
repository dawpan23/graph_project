#define _USE_MATH_DEFINES

#include<vector>
#include "graph.h"
#include<string>
#include<cmath>
#include<iostream>

using namespace std;
using graph = std::vector<std::vector<int>>;

void wypiszWspolrzedne(graph g)
{
	int N = g.size();
	for (int i = 0; i < N; i++)
	{
		double x = 100 * cos(M_PI * 2 * i / N);
		double y = 100 * sin(M_PI * 2 * i / N);
		cout << "Wspolrzedne wierzcholka " << i << ": " << round(x) << ", " << round(y) << endl;
	}
	return;
}