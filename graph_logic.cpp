#include<iostream>
#include<vector>
#include<queue>

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

string checkGraphStatus(const graph& G)
{
	bool multiGraph = false;
	bool pseudoGraph = false;
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

}