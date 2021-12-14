#pragma once
#include "MapData.h"
#include <SFML/Graphics.hpp>
class Spawner
{
public:

	Spawner();

	MapManager* mapManager;

	sf::Color TerrainShade = sf::Color(51, 204, 0, 255);

	sf::Color Colours[5] = { sf::Color(255,0,0),sf::Color(255,255,255),sf::Color(0,0,255) , sf::Color(255,255,0),sf::Color(242,210,189)};

	void SpawnCharacters();

	void CreateCharacter(int TileLocation, int i);
	void CreateCharacter(Settlement* Original, Tile* NewTile);

};
