#include<iostream>
#include<vector>
#include "graph_logic.h"
using namespace std;

int main() 
{
	using graph = std::vector<std::vector<int>>;
	
	graph G = {
		{1},
		{0, 2},
		{},
	};
	string typGrafu = checkGraphStatus(G);
	if (typGrafu == "Skierowany")
	{
		cout << "Graf skierowany. Program takich obecnie nie obsluguje.";
	}
	else if (typGrafu == "Pseudograf")
	{
		cout << "Graf jest pseudografem. Ciezko o dalsza, ciekawa analize";
	}
	else if (typGrafu == "Multigraf")
	{
		cout << "Graf jest multigrafem.";
	}
	else if (typGrafu == "Prosty")
	{
		cout << "Graf jest prosty. Sprawdzam czy jest sciezka... " << endl;
		if (czySciezka(G))
		{
			cout << "Graf jest sciezka. Swietnie!" << endl;
		}
		else
		{
			cout << "Graf nie jest sciezka. Sprawdze czy ma cykle... " << endl;
			if (czyCyklExists(G))
			{
				cout << "Ma cykl.";
			}
			else
			{
				cout << "Nie ma cyklu.";
			}
		}
	}
	return 1;
}