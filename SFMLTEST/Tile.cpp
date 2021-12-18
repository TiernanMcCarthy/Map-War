#include "Tile.h"

Tile::Tile(float X, float Y, bool L)
{
	x = X;
	y = Y;
	land = L;
	occupied = false;
	Occupier = nullptr;
}

Tile::Tile()
{
	//Do something
	occupied = false;
	Occupier = nullptr;
}


void Tile::SetAttributes(bool Occupation, bool Land, Settlement& occu)
{
	occupied = Occupation;
	land = true;
	Occupier = &occu;
}


void Tile::DrawSegment(sf::Color c, sf::Image &Map)
{
	if (x > 0 && y > 0)
	{
		for (int Y = y; Y < y + TileSize; Y++)
		{
			for (int X = x; X < x + TileSize; X++)
			{
				Map.setPixel(X, Y, c);
			}
		}
	}
}