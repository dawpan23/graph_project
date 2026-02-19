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
		{1},
	};
	cout << czySpojny(G);
	return 1;
}