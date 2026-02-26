#define _USE_MATH_DEFINES

#include<vector>
#include "graph.h"
#include<string>
#include<cmath>
#include<iostream>
#include <SFML/Graphics.hpp>

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
		float y = 100 * sin(M_PI * 2 * i / N);
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
	sf::RenderWindow window(sf::VideoMode({ width, height }), "Wizualizacja grafu");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);


	std::vector<sf::Vector2f> wspolrzedne = wypiszWspolrzedne(g, { width / 2.0f , height / 2.0f });
	std::vector<sf::CircleShape> vertices;
	vertices.resize(g.v());
	for (int i = 0; i < g.v(); i++)
	{
		vertices[i].setRadius(20.f);
		vertices[i].setOrigin({ 20.f, 20.f });
		vertices[i].setFillColor(sf::Color::White);
		vertices[i].setPosition(wspolrzedne[i]);
	}
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();
		window.draw(shape);
		for (sf::CircleShape vertex : vertices)
		{
			window.draw(vertex);
		}
		window.display();
	}
	return;
}