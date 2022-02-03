#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <math.h>
#include "Tile.h"
#include "Globals.h"
#include "MapData.h"
#include "Settlement.h"
#include "GameManager.h"

sf::Image Map;



int main()
{
	
	sf::RenderWindow window(sf::VideoMode(981, 1521), "Map War 0.1");




	//SFML window systems are managed by the map manager
	//Map manager is responsible for loading the map file and generating tiles for populating from this data
	MapManager MapData = MapManager(Width, Height,Mapname,window);
	//Draw and manage the first texture
	MapData.UpdateWindow(window);


	window.setFramerateLimit(FrameRate);
	//Create Manager for simulation execution
	GameManager Manager = GameManager(MapData);
	

	bool pause = false;

	//By increasing variables and the natural flow of the simulation this might be redundant
	int IterationsPerFrame = 3;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type==sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					//Draw all alive Tiles
					for (int i = 0; i < MapData.TileMap.size() - 1; i++)
					{
						Tile* a;
						a = &(MapData.TileMap)[i];

						if (a->occupied)
						{
							a->DrawSegment(sf::Color(0, 0, 0), MapData.Map);
						}
					}

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					pause = !pause;
				}
			}
		}
		
		for (int i = 0; i < IterationsPerFrame; i++)
		{
			if (!pause)
			{
				Manager.Execute(MapData);
			}

		}
		MapData.UpdateWindow(window);
	}

	return 0;
}