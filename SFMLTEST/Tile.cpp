#include "Tile.h"

Tile::Tile(float X, float Y, bool L)
{
	x = X;
	y = Y;
	land = L;
	occupied = false;
}

Tile::Tile()
{
	//Do something
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