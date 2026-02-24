#pragma once
#include <vector>
#include <string>

class Graph {
private:
	std::vector<std::vector<int>> adjList;
	int numVertices;
public:
	//Graph(std::vector<std::vector<int>> g);
	Graph(std::string filename);

	bool czySpojny();
	std::string checkGraphStatus();
	bool czySciezka();
	bool czyCyklExists();

	int v() const { return numVertices; }
	std::vector<std::vector<int>> data() const { return adjList; }
};