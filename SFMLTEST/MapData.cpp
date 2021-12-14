#include "MapData.h"
#include "Globals.h"
#include "Tile.h"
#include "Settlement.h"
#include "Spawner.h"
#include <SFML/System.hpp>
#include <vector>


MapManager::MapManager(int Size) //Do not pursue
{
	CreateTileMap(30, 30);
}



MapManager::MapManager(int X, int Y,std::string MapName, sf::RenderWindow &WindowRef)
{
	//SetWindowReference(WindowRef);
	WindowReference = &WindowRef;
	LoadMapFile(MapName);
	CreateTileMap(X, Y);
	CreateTexture(X, Y);
	printf("Map Generated \n");
	PlayerList = new std::vector<Settlement>;
	Spawner SpawnerGaming = Spawner();
	SpawnController = new Spawner;

	*SpawnController = SpawnerGaming;
	SpawnController->mapManager = this;
	SpawnController->SpawnCharacters();
	printf("Settlements created! \n");
}

bool MapManager::CreateTexture(int X, int Y)
{
	if (!MapTexture.create(X, Y))
	{
		printf("Texture failed \n");
		return false;
	}
	if (!MapTexture.loadFromImage(Map))
	{
		printf("Loading the texture form map failed \n");
		return false;
	}

	MapTexture.update(Map); //fill the map contents
	MapTexture.setRepeated(false);
	MapTexture.setSmooth(false);

	sprite.setTexture(MapTexture);
	//UpdateWindow();
	//WindowReference->setFramerateLimit(FrameRate);


	return true;
}

void MapManager::UpdateWindow(sf::RenderWindow &temp)
{
	WindowReference->clear();
	MapTexture.update(Map);
	WindowReference->draw(sprite);
	WindowReference->display();
}

//void MapManager::SetWindowReference(sf::RenderWindow Rw)
//{
//	WindowReference = &Rw;
//}


bool MapManager::LoadMapFile(std::string FileName)
{
	if (!Map.loadFromFile(FileName))
	{
		printf("Map load failed \n");
		return false;
	}
	return true;
}

bool MapManager::TestSegment(int x, int y) //If a single pixel is not perfectly green (land) then ignore it, this is an early implementation
{
	for (int Y = y; Y < y + TileSize; Y++)
	{
		for (int X = x; X < x + TileSize; X++)
		{
			sf::Color Test = Map.getPixel(X, Y);
			if (Map.getPixel(X, Y) != sf::Color(51, 204, 0, 255)) //Just the colours of the green
			{
				return false; //Sea
			}
		}
	}
	return true; //Land 
}



void MapManager::CreateTileMap(int width, int height)
{
	//Map is not even, just pretend 980x1520 for now and make something to adjust for stuff like this later

	int StepsX = width / TileSize;
	int StepsY = height / TileSize;
	Tile* TempTile = new Tile();
	for (int Y = 0; Y < StepsY;)
	{
		for (int X = 0; X < StepsX;)
		{

			TempTile = new Tile(X * TileSize, Y * TileSize, TestSegment(X * TileSize, Y * TileSize)); //Test Segment checks all the pixels, if there is a single non green pixel, sea is implied.
			TileMap.push_back(*TempTile);
			if (TempTile->land && LandDebug)
			{
				DrawSegment(Map, TempTile->x, TempTile->y, sf::Color(255, 255, 255));
			}
			delete TempTile;
			X += 1;
		}
		Y += 1;

	}
	TempTile = NULL;
}

void MapManager::DrawSegment(sf::Image& map, int x, int y, sf::Color DrawColour)
{
	for (int Y = y; Y < y + TileSize; Y++)
	{
		for (int X = x; X < x + TileSize; X++)
		{
			map.setPixel(X, Y, DrawColour);
		}
	}
}

void MapManager::GenerateValidLand() //Regenerate Land Map incase of change
{
	for (int i = 0; i < TileMap.size(); i++)
	{
		TileMap[i].land = TestSegment(TileMap[i].x, TileMap[i].y);
		if (TileMap[i].land && LandDebug==1) //Debug
		{
			DrawSegment(Map, TileMap[i].x, TileMap[i].y, sf::Color(255, 255, 255));
		}
	}
}