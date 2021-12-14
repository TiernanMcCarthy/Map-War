#pragma once
#include <SFML/Graphics.hpp>
#include "MapData.h"
class Settlement {

public:

	Settlement(Tile& home, sf::Color colour,MapManager& Data);

	Settlement();
	void Delete();

	void Simulate();
	void AttackState();
	void SetTarget(Settlement *Targ);

	void RecieveDamage(int Amount);

	Tile* GetHomeTile();


	MapManager &GetMapData();

	sf::Color GetColour();


private:

	
	void Reproduce(Tile *HomeTile);
	float Health = 100;
	float ReproductiveValue = 0;
	int x, y;
	Tile* Home;
	
	Settlement* Target;

	MapManager *MapData;
	sf::Color Colour;


};
