#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<vector>
#include "Tile.h"
//#include "Settlement.h"
//#include "Spawner.h"
class Settlement;
class Spawner;
class MapManager
{
public: 
	
	MapManager(int width, int height, std::string MapName,sf::RenderWindow &WindowRef);
	MapManager(int Size);

	sf::Image Map;

	std::vector<Tile> TileMap;

	std::vector<Settlement> *PlayerList;



	bool LoadMapFile(std::string FileName);


	void DrawSegment(sf::Image& map, int x, int y, sf::Color DrawColour);
	bool TestSegment(int x, int y); //If a single pixel is not perfectly green (land) then ignore it, this is an early implementation

	bool CreateTexture(int X, int Y);

	void UpdateWindow(sf::RenderWindow &t);

	void SetWindowReference(sf::RenderWindow &Rw);

	void GenerateValidLand();

	int FindElementInList(Settlement *Target);

	Settlement& SlowSearch(int X);

	bool ConfirmTile(Settlement *Tar);

	void RemoveObject(Settlement *Target);


	Spawner* SpawnController;

	MapManager();


	Settlement *CheatTile;
private:
	sf::Texture MapTexture;
	sf::RenderWindow* WindowReference;
	sf::Sprite sprite;
	void CreateTileMap(int width, int height);
	int SlowSearchInt(Settlement *X);


};
