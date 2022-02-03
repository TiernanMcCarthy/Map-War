#pragma once
#include <SFML/Graphics.hpp>
#include "MapData.h"
#include "Confirmation.h"

//Populator of Tile objects whilst attempting to reproduce and fight for land
class Settlement {

public:
	//Reference to a home tile, its colour and a pointer to the map manager that can access its peers
	Settlement(Tile& home, sf::Color colour,MapManager& Data);

	Settlement();

	void Delete();

	//Simulate all actions for the settlement, called by the MapManager
	void Simulate();

	void SetTarget(Settlement *Targ);



	void RecieveDamage(int Amount);

	Tile* GetHomeTile();


	MapManager &GetMapData();

	sf::Color GetColour();

	bool operator == (Settlement b);
	Settlement* Target = NULL;

	bool ValidMan = false;
private:

	
	float Health = 100;
	float ReproductiveValue = 0;
	int x, y;
	Tile* Home;
	
	float DamageOffsetModifier;


	MapManager *MapData;
	sf::Color Colour;


	Confirmation TestAvailableLand(Tile* TestTile, Settlement* S); //Return A Hex Value of 0		0		0		0      And pick one

	void CheckTargetTile();

	bool ValidTarget();

	bool PickTarget();
	void AttackState();
};
