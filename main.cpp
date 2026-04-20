#include<iostream>
#include<vector>
#include "graph.h"
#include "draw_graph.h"
#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
	Graph g("graph.txt");

	if (g.v() == 0)
	{
		cout << "Something is wrong, the graph is empty" << endl;
		return 1;
	}

	string graphType = g.checkGraphStatus();
	cout << "Graph type: " << graphType << endl;
	if (graphType != "Simple")
	{
		cout << "Because the graph is not simple, further analysis might fail (for now). To test the program further, use a simple graph.";
		return 2;
	}
	bool isSpojny = g.czySpojny();
	cout << "Is it connected? " << (isSpojny ? "Yes" : "No") << endl;
	if (isSpojny)
	{
		bool isCykl = g.czyCyklExists();
		cout << "Are there cycles? " << (isCykl ? "Yes" : "No") << endl;
		cout << "Is it a path? " << (g.czySciezka() ? "Yes" : "No") << endl;
		if (!isCykl)
		{
			cout << "This graph is a tree." << endl;
		}
	}
	cout << "Graph diameter: " << g.diameter() << endl;
	drawGraph(g);
}