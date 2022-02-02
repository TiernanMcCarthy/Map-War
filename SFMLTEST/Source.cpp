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

sf::Color colours[4] = { sf::Color(255,0,0),sf::Color(0,255,0),sf::Color(0,0,255),sf::Color(255,0,255) };

using namespace std;
SFML_VECTOR2_HPP;
sf::Image Map;

#define Width 980
#define Height 1520

//#define TileSize 10 //Tiles are square, x*y pixels e.t.c



//https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php
int main()
{
	
	srand(time(NULL)); //seed for random function
	sf::RenderWindow window(sf::VideoMode(981, 1521), "Map War 0.1");


	sf::CircleShape shape(100.0f);
	shape.setFillColor(sf::Color::Green);

	sf::Texture texture;

	//New 
	MapManager MapData = MapManager(Width, Height,"map.png",window);
	MapData.UpdateWindow(window);




	if (!Map.loadFromFile("map.png"))
	{
	printf("Map load failed \n");
	}



	if (!texture.loadFromImage(Map))
	{
		printf("Loading the texture form map failed \n");
	}

	//create texture

	if (!texture.create(981, 1521))
	{
		printf("Texture failed \n");
	}


	texture.update(Map); //fill the map contents
	texture.setRepeated(false);
	texture.setSmooth(false);


	sf::Sprite sprite;
	sprite.setTexture(texture);
	int FrameSpeed = 60;

	//int size;
	GameManager Manager = GameManager(MapData);
	

	bool pause = false;

	int IterationsPerFrame = 6;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type==sf::Event::KeyPressed)
			{
				//sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					FrameSpeed += 1;
					window.setFramerateLimit(FrameSpeed);

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
					FrameSpeed -= 1;

					pause = !pause;
					window.setFramerateLimit(FrameSpeed);
				}
			}
		}
		
		for (int i = 0; i < IterationsPerFrame; i++)
		{
			if (!pause)
			{
				Manager.Execute(MapData);
			}

			MapData.UpdateWindow(window);
		}
	}

	return 0;
}