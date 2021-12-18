#pragma once
#include <SFML/Graphics.hpp>
#include "MapData.h"
#include "Confirmation.h"


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

	bool operator == (Settlement b);
	Settlement* Target = NULL;

	bool ValidMan = false;
private:

	
	void Reproduce(Tile *HomeTile);
	float Health = 100;
	float ReproductiveValue = 0;
	int x, y;
	Tile* Home;
	

	MapManager *MapData;
	sf::Color Colour;


	Confirmation TestAvailableLand(Tile* TestTile, Settlement* S); //Return A Hex Value of 0		0		0		0      And pick one

	void CheckTargetTile();

	bool ValidTarget();

	bool PickTarget();
};
