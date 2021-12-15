#include "Settlement.h"
#include "Globals.h"
#include "Confirmation.h"
#include "Spawner.h"
#include "Tile.h"
#include <iostream>
Settlement::Settlement(Tile& home, sf::Color colour, MapManager& Data)
{
	Colour = colour;

	Home = &home;
	MapData = &Data;
	Home->occupied = true;
	Home->Occupier = this;
	x = home.x;
	y = home.y;

	Home->x = x;
	Home->y = y;

	Home->DrawSegment(Colour, MapData->Map);
}


Settlement::Settlement()
{


	
}

void Settlement::Delete()
{
	sf::Color(51, 204, 0, 255);

	//MapData->DrawSegment(MapData->Map, Home->x, Home->y, sf::Color(0, 255, 0, 255));

	Home = NULL;
	delete Home;

	Target = NULL;
	delete Target;

	MapData = NULL;
	delete MapData;

}

MapManager &Settlement::GetMapData()
{
	return *MapData;
}

Tile* Settlement::GetHomeTile()
{
	return Home;
}


Tile& GetTileFromCord(int X, int Y,MapManager *MapData )
{

	if (Y < 1)
	{
		return(MapData->TileMap[X / TileSize]);
	}
	else
	{
		int StepsX = 980 / TileSize;
		int StepsY = 1520 / TileSize;
		if (Y / TileSize != 1)
		{
			int Position = (Y / TileSize);
			Position = Position * StepsX;
			Position = Position + X / TileSize;
			return(MapData->TileMap[Position]);
		}
		else
		{
			int Position = StepsX + X / TileSize;
			return MapData->TileMap[Position];
		}
	}


}	
Tile* TileTest;

void Settlement::SetTarget(Settlement *Targ)
{
	Target = Targ;
}

void CheckTarget(Settlement *S, Tile *Targ)
{
	if (S->GetColour() != Targ->Occupier->GetColour())
	{
		S->SetTarget(Targ->Occupier);
	}

}

//																	    UP	Down	Left	Right
Confirmation TestAvailableLand(Tile* TestTile, Settlement S) //Return A Hex Value of 0		0		0		0      And pick one
{
	//Tile* TileTest = new Tile();

	//Right    //THESE TESTS DO LITERALLY NOTHING LMAO
	if (TestTile->x != Width - TileSize) //Not too far offmap to the right
	{
		TileTest = &GetTileFromCord(TestTile->x + TileSize, TestTile->y, &S.GetMapData());
		if (TileTest->land)
		{
			//printf("Tile Found \n");
			if(TileTest->occupied == false)
				return  Confirmation(0x0001, TileTest);

			CheckTarget(&S, TileTest);

			//return TileTest;
		}
		//printf("Invalid Tile \n");
	}


	//Down
	if (TestTile->y != Height - TileSize)
	{
		TileTest = &GetTileFromCord(TestTile->x, TestTile->y + TileSize, &S.GetMapData());
		if (TileTest->land)
		{
			//printf("Tile Found \n");
			if (TileTest->occupied == false)
				return  Confirmation(0x0100, TileTest);
			CheckTarget(&S, TileTest);
		}
		//printf("Invalid Tile \n");
	}
	//UP
	if (TestTile->y != 0)
	{
		TileTest = &GetTileFromCord(TestTile->x, TestTile->y - TileSize, &S.GetMapData());
		if (TileTest->land)
		{
			//printf("Tile Found \n");
			if (TileTest->occupied == false)
				return  Confirmation(0x1000, TileTest);
			CheckTarget(&S, TileTest);
		}
		//printf("Invalid Tile \n");
	}


	//LEFT
	if (TestTile->x != 0) //Not offmap to the left
	{
		TileTest = &GetTileFromCord(TestTile->x - TileSize, TestTile->y, &S.GetMapData());
		if (TileTest->land == true)
		{
			if (TileTest->occupied == false)
				return  Confirmation(0x0010, TileTest);
			CheckTarget(&S, TileTest);
		}
	}

	return Confirmation(0x0000, TestTile);
	//return *TileTest;
}


sf::Color Settlement::GetColour()
{
	return Colour;
}

void Settlement::RecieveDamage(int Damage)
{
	Health -= Damage;
	if (Health <= 0)
	{
		
	}

}

void Settlement::AttackState()
{
	if (Target != NULL)
	{




	}
	else //Pick a target
	{


	}


}
void Settlement::Simulate()
{
	ReproductiveValue += 0.03f;

	if (ReproductiveValue >= ReproductionThreshold)
	{
		ReproductiveValue = 0;
		Confirmation Result=TestAvailableLand(Home, *this);

		
		switch (Result.ValidState & 0x1111)
		{
		case 0x1000: //UP
			MapData->SpawnController->CreateCharacter(this, Result.Home);
			//printf("Up \n");

			break;
		case 0x0100: //DOWN
			MapData->SpawnController->CreateCharacter(this, Result.Home);
			//printf("Down \n");
			break;

		case 0x0010: //LEFT
			MapData->SpawnController->CreateCharacter(this, Result.Home);
			//printf("Left \n");
			break;

		case 0x0001: //RIGHT
			MapData->SpawnController->CreateCharacter(this, Result.Home);
		//	printf("Right \n");
			break;

	
		}

		//Result.Home = NULL;
		//delete Result.Home;
		//std::cout << Result << std::endl;
		//CreateNew
		//MapData->
	}
}



bool Settlement::operator==(Settlement b)
{
	return Home->x == b.GetHomeTile()->x;

}

