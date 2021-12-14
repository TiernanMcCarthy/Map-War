#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Settlement;
class Tile
{
public:
	float x, y; //origin of the top left corner. Add tilesize to them for outer margins
	bool land;
	bool occupied;
	Settlement *Occupier;

	//sf::Image* localmap;

	Tile(float X, float Y, bool L);

	Tile();
	
	
	void DrawSegment(sf::Color c, sf::Image& Map);
	
};

