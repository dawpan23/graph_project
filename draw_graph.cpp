#define _USE_MATH_DEFINES

#include<vector>
#include "graph.h"
#include<string>
#include<cmath>
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Vertex.hpp>
using namespace std;
using graph = std::vector<std::vector<int>>;



std::vector<sf::Vector2f> wypiszWspolrzedne(Graph g, sf::Vector2f offset)
{
	std::vector<sf::Vector2f> wspolrzedne;
	wspolrzedne.resize(g.v());
	int N = g.v();
	for (int i = 0; i < N; i++)
	{
		float x = 100 * cos(M_PI * 2 * i / N);
		float y = -100 * sin(M_PI * 2 * i / N);
		//cout << "Wspolrzedne wierzcholka " << i << ": " << round(x) << ", " << round(y) << endl;
		wspolrzedne[i].x = x + offset.x;
		wspolrzedne[i].y = y + offset.y;
	}
	return wspolrzedne;
}

void drawGraph(Graph g)
{
	//rozmiary okna
	unsigned int width = 1600;
	unsigned int height = 900;
	sf::RenderWindow window(sf::VideoMode({ width, height }), "Graph visualisation");

	std::vector<sf::Vector2f> wspolrzedne = wypiszWspolrzedne(g, { width / 2.0f , height / 2.0f });

	//Wierzcholki
	std::vector<sf::CircleShape> vertices;
	vertices.resize(g.v());
	float vertexRadius = 3;
	for (int i = 0; i < g.v(); i++)
	{
		vertices[i].setRadius(vertexRadius);
		vertices[i].setOrigin({ vertexRadius, vertexRadius });
		vertices[i].setFillColor(sf::Color::White);
		vertices[i].setPosition(wspolrzedne[i]);
	}

	//Krawedzie
	std::vector<std::vector<int>>& data = g.data();
	sf::VertexArray krawData(sf::PrimitiveType::Lines);

	for (int i = 0; i < g.v(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			int sasiad = data[i][j];
			if (i < sasiad)
			{
				krawData.append( { wspolrzedne[i], sf::Color::White, wspolrzedne[i] } );
				krawData.append({ wspolrzedne[sasiad], sf::Color::White, wspolrzedne[sasiad] });
			}
		}
	}

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();
		for (sf::CircleShape vertex : vertices)
		{
			window.draw(vertex);
		}
		window.draw(krawData);
		window.display();
	}
	return;
}