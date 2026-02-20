#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using graph = std::vector<std::vector<int>>;

bool czySpojny(const graph& G)
{
	int N = G.size();
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

string checkGraphStatus(graph& G)
{
	bool multiGraph = false;
	bool pseudoGraph = false;
	bool directed = false;
	int N = G.size();
	std::vector<int> connections(N, 0);
	std::vector<int> dirtyIndices;
	for (int i = 0; i < N; i++)
	{
		if (pseudoGraph)
		{
			break;
		}
		std::vector<int> sasiedzi = G[i];
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
	
	if (directed)
	{
		return "Skierowany";
	}
	if (pseudoGraph)
	{
		return "Pseudograf";
	}
	else if (multiGraph)
	{
		return "Multigraf";
	}
	else
	{
		return "Prosty";
	}
}

bool czySciezka(const graph& G)
{
	//Uwaga: Funkcja zakłada, że graf jest prosty i spójny
	int konceGrafu = 0;
	int N = G.size();
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

bool czyCyklExists(const graph& G)
{
	int N = G.size();
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

