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