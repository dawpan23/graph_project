#include<iostream>
#include<vector>
#include "graph.h"
#include "draw_graph.h"
#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
	Graph g("graf.txt");

	if (g.v() == 0)
	{
		cout << "Cos poszlo nie tak, graf sie nie wczytal/plik jest pusty" << endl;
		return 1;
	}

	string graphType = g.checkGraphStatus();
	cout << "Typ grafu: " << graphType << endl;
	if (graphType != "Prosty")
	{
		cout << "Poniewaz zwrocony typ grafu jest inny niz prosty, dalsza analiza moze nie zadzialac, wroc z grafem prostym.";
		return 2;
	}
	bool isSpojny = g.czySpojny();
	cout << "Czy spojny? " << (isSpojny ? "Tak" : "Nie") << endl;
	if (isSpojny)
	{
		cout << "Czy cykle? " << (g.czyCyklExists() ? "Tak" : "Nie") << endl;
		cout << "Czy sciezka?" << (g.czySciezka() ? "Tak" : "Nie") << endl;
	}

	wypiszWspolrzedne(g.data());

	sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}