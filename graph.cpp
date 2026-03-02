#include<fstream>
#include "Graph.h"
#include<algorithm>
#include<sstream>
#include<queue>

using namespace std;

using graph = std::vector<std::vector<int>>;
//Wczytywanie grafu z pliku
Graph::Graph(std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) { return; }

	int V;
	file >> V;
	file.ignore(); //Przeszkocz enter
	this->numVertices = V;
	adjList.resize(V);

	int currV = 0;
	std::string line;
	while (std::getline(file, line) && currV < this->numVertices)
	{
		std::stringstream ss(line);
		int neighbor;
		while (ss >> neighbor)
		{
			this->adjList[currV].push_back(neighbor);
		}
		currV++;
	}
}



bool Graph::czySpojny()
{
	graph& G = adjList;
	int N = numVertices;
	std::vector<int> visited(N, 0);
	std::queue<int> queue;
	visited[0] = 1;
	int visits = 1;
	for (int v : G[0])
	{
		queue.push(v);
		visited[v] = 1;
		visits++;
	}

	if (visits == N) { return true; }

	while (queue.size() != 0)
	{
		for (int v : G[queue.front()])
		{
			if (visited[v] == 0)
			{
				queue.push(v);
				visited[v] = 1;
				visits++;
			}
		}
		queue.pop();
		if (visits == N) { return true; }
	}
	return false;
}

string Graph::checkGraphStatus()
{
	graph& G = adjList;
	bool multiGraph = false;
	bool pseudoGraph = false;
	bool directed = false;
	int N = numVertices;
	std::vector<int> connections(N, 0);
	std::vector<int> dirtyIndices;
	for (int i = 0; i < N; i++)
	{
		if (pseudoGraph)
		{
			break;
		}
		std::vector<int>& sasiedzi = G[i];
		for (int dirty : dirtyIndices)
		{
			connections[dirty] = 0;
		}
		dirtyIndices.clear();
		for (int idx : sasiedzi)
		{
			if (i == idx)
			{
				pseudoGraph = true;
				break;
			}

			connections[idx]++;
			if (connections[idx] > 1)
			{
				multiGraph = true;
			}
			dirtyIndices.push_back(idx);
		}
	}

	//Sprawdzam czy skierowany, najpierw sortowanie
	for (std::vector<int>& idx : G)
	{
		std::sort(idx.begin(), idx.end());
	}
	for (int curr = 0; curr < G.size(); curr++)
	{
		std::vector<int>& idx = G[curr];
		if (directed) { break; }
		for (int i = 0; i < idx.size(); i++)
		{
			if (directed) { break; }

			int inny = idx[i];
			if (!std::binary_search(G[inny].begin(), G[inny].end(), curr))
			{
				directed = true;
				break;
			}
		}
	}

	//Na razie mam wywalone w skierowane grafy
	if (directed)
	{
		return "Directed";
	}
	if (pseudoGraph)
	{
		return "Pseudograph";
	}
	else if (multiGraph)
	{
		return "Multigraph";
	}
	else
	{
		return "Simple";
	}
}

bool Graph::czySciezka()
{
	//Uwaga: Funkcja zakłada, że graf jest prosty i spójny
	graph& G = adjList;
	int konceGrafu = 0;
	int N = numVertices;
	int E = 0;

	//edge case:
	if (N == 1)
	{
		return true;
	}

	for (int i = 0; i < N; i++)
	{
		int stopien = G[i].size();
		if (stopien > 2)
		{
			return false;
		}
		if (stopien == 1)
		{
			konceGrafu++;
		}
		if (konceGrafu > 2)
		{
			return false;
		}
		E += stopien;
	}

	E = E / 2; //Lemat o uściskach dłoni. Liczba krawędzi = Suma stopni wierzchołka podzielona na 2.

	if (konceGrafu == 2 && E == (N - 1))
	{
		return true;
	}
	return false;
}

bool Graph::czyCyklExists()
{
	int N = numVertices;
	graph& G = adjList;
	std::vector<int> visited(N, 0);
	std::vector<int> parent(N, -1); //Każdy wierzchołek ma "parenta" którego ma ignorować przy sprawdzaniu, czy spotkał kogoś innego, kto jest visited
	std::queue<int> queue;
	visited[0] = 1;
	for (int v : G[0])
	{
		visited[v] = 1;
		queue.push(v);
		parent[v] = 0;
	}
	while (queue.size() != 0)
	{
		int idx = queue.front();
		for (int v : G[idx])
		{
			if (visited[v] == 1)
			{
				if (parent[idx] != v)
				{
					return true;
				}
			}
			else
			{
				visited[v] = 1;
				queue.push(v);
				parent[v] = idx;
			}
		}
		queue.pop();
	}
	return false;
}