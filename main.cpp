#include<iostream>
#include<vector>
#include "graph.h"
using namespace std;

int main() 
{
	Graph g("graf.txt");

	if (g.v() == 0)
	{
		cout << "Cos poszlo nie tak, graf sie nie wczytal/plik jest pusty" << endl;
		return 1;
	}

	string graphType = g.checkGraphStatus();
	cout << "Typ grafu: " << graphType << endl;
	if (graphType != "Prosty")
	{
		cout << "Poniewaz zwrocony typ grafu jest inny niz prosty, dalsza analiza moze nie zadzialac, wroc z grafem prostym.";
		return 2;
	}
	bool isSpojny = g.czySpojny();
	cout << "Czy spojny? " << (isSpojny ? "Tak" : "Nie") << endl;
	if (isSpojny)
	{
		cout << "Czy cykle? " << (g.czyCyklExists() ? "Tak" : "Nie") << endl;
		cout << "Czy sciezka?" << (g.czySciezka() ? "Tak" : "Nie") << endl;
	}
	return 0;
}