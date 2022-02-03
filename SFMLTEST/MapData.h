#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<vector>
#include "Tile.h"
class Settlement;
class Spawner;
class MapManager
{
public: 
	
	MapManager(int width, int height, std::string MapName,sf::RenderWindow &WindowRef);
	MapManager(int Size);


	sf::Image Map; //Contain the supplied Map PNG

	std::vector<Tile> TileMap; //Holds a generated map of tiles that settlements can occupy and reference during gameplay

	std::vector<Settlement> *PlayerList; //Player List stores all generated settlements and can be crossreferenced to find correct players


	bool LoadMapFile(std::string FileName);


	void DrawSegment(sf::Image& map, int x, int y, sf::Color DrawColour); //Fill a rectangle at x & y * TileSize

	bool TestSegment(int x, int y); //If a single pixel is not perfectly green (land) then ignore it, this is an early implementation

	bool CreateTexture(int X, int Y);

	void UpdateWindow(sf::RenderWindow &t); //Redraw window instance

	void SetWindowReference(sf::RenderWindow &Rw);

	void GenerateValidLand(); //Create Tile Map of valid land tiles

	int FindElementInList(Settlement *Target);

	Settlement& SlowSearch(int X, int Y);

	bool ConfirmTile(Settlement *Tar);

	//Speed up with more intelligent method later
	void RemoveObject(Settlement *Target); //Iterate through playerlist and find the target

	//Manages spawning new settlements at the start of the game and during reproduction
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
