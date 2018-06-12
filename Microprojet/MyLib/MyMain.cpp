#include "stdafx.h"
#include "MyMain.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <tmxlite/Map.hpp>
#include "SFMLOrthogonalLayer.hpp"
#include "Hero.h"

int MyMain()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	int FPS = 16;
	tmx::Map map;
	map.load("../assets/demo.tmx");

	MapLayer layerZero(map, 0);
	MapLayer layerOne(map, 1);
	MapLayer layerTwo(map, 2);
	Hero hero{ 0, 0 };
	auto lastTime = std::chrono::system_clock::now();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		window.draw(layerZero);
		window.draw(layerOne);
		window.draw(layerTwo);

		auto current = std::chrono::system_clock::now();
		auto elapsed = (current - lastTime);
		hero.handleInput();
		hero.update(elapsed.count()/FPS);
		window.display();
		lastTime = current;
	}

	return 0;
}