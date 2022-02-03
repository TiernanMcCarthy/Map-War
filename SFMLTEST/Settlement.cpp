#include "Settlement.h"
#include "Globals.h"
#include "Confirmation.h"
#include "Spawner.h"
#include "Tile.h"
#include <math.h>
#include <iostream>

Settlement::Settlement(Tile& home, sf::Color colour, MapManager& Data)
{
	Colour = colour;

	//Randomise the health between 0-1, a more complicated solution is needed with more factors for a more dynamic game
	Health = rand() % 100 + 1;
	

	Home = &home;
	MapData = &Data;
	Home->occupied = true; //Inform the home tile of this settlement's existence
    Home->Occupier = this;
	x = home.x;
	y = home.y;
	Target = nullptr;
	Home->x = x;
	Home->y = y;

	Home->DrawSegment(Colour, MapData->Map);
	Home->SetAttributes(true, true, *this);

	DamageOffsetModifier = 1; //Implement later to randomise damage

	ValidMan = true;
}


Settlement::Settlement()
{
	Target = nullptr;
	ValidMan = false;
	x = -1;
	Health = 100;
	//NewTile->SetAttributes(true, true, *a);
	
}
//Clear the Occupied Tile of References to this object
void Settlement::Delete()
{
	//sf::Color(51, 204, 0, 255);
	if (ShowDeaths)
	{
		MapData->DrawSegment(MapData->Map, Home->x, Home->y, DeathColour);
	}
	Home->occupied = false;

	Home->Occupier = nullptr;



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
	if (Targ != nullptr)
	{
		Target = Targ;
	}
}

void CheckTarget(Settlement *S, Tile *Targ)
{
	if (S->GetColour() != Targ->Occupier->GetColour() && Targ->Occupier!=NULL)
	{
		S->SetTarget(Targ->Occupier);
	}

}


void Settlement::CheckTargetTile()
{
	Target = nullptr;
	Settlement* Temp = &MapData->SlowSearch(TileTest->x,TileTest->y);
	if (Temp->x == TileTest->x && Temp->GetColour()!=GetColour())
	{
		Target = Temp;
	}
}

//																	    UP	Down	Left	Right
Confirmation Settlement::TestAvailableLand(Tile* TestTile, Settlement* S) //Return A Hex Value of 0		0		0		0      And pick one
{

	if (TestTile->x != Width - TileSize) //Not too far offmap to the right
	{
		TileTest = &GetTileFromCord(TestTile->x + TileSize, TestTile->y, &S->GetMapData());
		if (TileTest->land)
		{
			//printf("Tile Found \n");
			if(TileTest->occupied == false)
				return  Confirmation(0x0001, TileTest);
			else if (TileTest->occupied == true)
			{
				//CheckTargetTile();
					
					//CheckTarget(S, TileTest);
				
			}

		}
	}


	//Down
	if (TestTile->y != Height - TileSize)
	{
		TileTest = &GetTileFromCord(TestTile->x, TestTile->y + TileSize, &S->GetMapData());
		if (TileTest->land)
		{
			//printf("Tile Found \n");
			if (TileTest->occupied == false)
				return  Confirmation(0x0100, TileTest);
			else if (TileTest->occupied == true)
			{
				
			}
		}
	}
	//UP
	if (TestTile->y != 0)
	{
		TileTest = &GetTileFromCord(TestTile->x, TestTile->y - TileSize, &S->GetMapData());
		if (TileTest->land)
		{
			//printf("Tile Found \n");
			if (TileTest->occupied == false)
				return  Confirmation(0x1000, TileTest);
			else if (TileTest->occupied == true)
			{
				//CheckTargetTile();
			}
		}
		//printf("Invalid Tile \n");
	}


	//LEFT
	if (TestTile->x != 0) //Not offmap to the left
	{
		TileTest = &GetTileFromCord(TestTile->x - TileSize, TestTile->y, &S->GetMapData());
		if (TileTest->land == true)
		{
			if (TileTest->occupied == false)
				return  Confirmation(0x0010, TileTest);
			else if (TileTest->occupied == true)
			{
				//CheckTargetTile();
			}
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

	if (this != nullptr)
	{
		Health -= Damage;
		if (Health <= 0)
		{
			if (MapData != nullptr)
			{
				MapData->RemoveObject(this);
			}
		}
	}

}

void Settlement::AttackState()
{
	//Target = NULL;
	if (Target!=nullptr)
	{

	

		Target->RecieveDamage(BaseDamage);

		//Home->DrawSegment(sf::Color(0, x, y),MapData->Map);
		//Target->Home->DrawSegment(sf::Color(0, x, y), MapData->Map);
	}
	else //Pick a target
	{


	}


}

bool Settlement::ValidTarget()
{
	Settlement* Temp = &MapData->SlowSearch(TileTest->x, TileTest->y);
	if (Temp->x == TileTest->x && Temp->GetColour() != GetColour())
	{
		Target = Temp;
		return true;
	}
	return false;
}



bool Settlement::PickTarget()
{
	Target = nullptr;
		if (x > -1 && x<Width - TileSize + 1 && y>-1 && y < Height - TileSize + 1)
		{
			//Right    //THESE TESTS DO LITERALLY NOTHING LMAO
			if (x != Width - TileSize) //Not too far offmap to the right
			{
				TileTest = &GetTileFromCord(x + TileSize, y, MapData);
				if (TileTest->land)
				{
					//printf("Tile Found \n");
					if (TileTest->occupied == true)
						CheckTargetTile();
					if (Target != nullptr)
					{
						return true;
					}

					//return TileTest;
				}
				//printf("Invalid Tile \n");
			}


			//Down
			if (y != Height - TileSize)
			{
				TileTest = &GetTileFromCord(x, y + TileSize, MapData);
				if (TileTest->land)
				{
					//printf("Tile Found \n");
					if (TileTest->occupied == true)
						CheckTargetTile();
					if (Target != nullptr)
					{
						return true;
					}
				}
				//printf("Invalid Tile \n");
			}
			//UP
			if (y != 0)
			{
				TileTest = &GetTileFromCord(x, y - TileSize, MapData);
				if (TileTest->land)
				{
					if (TileTest->occupied == true)
						CheckTargetTile();
					if (Target != nullptr)
					{
						return true;
					}
				}
				//printf("Invalid Tile \n");
			}


			//LEFT
			if (x != 0) //Not offmap to the left
			{
				TileTest = &GetTileFromCord(x - TileSize, y, MapData);
				if (TileTest->land == true)
				{
					if (TileTest->occupied == true)
						CheckTargetTile();
					if (Target != nullptr)
					{
						return true;
					}
				}
			}
		}
	
	return false;
}

void Settlement::Simulate()
{
	if (Home)
	{
		ReproductiveValue += 0.03f;
		//Home->Occupier = this;
		//TileTest = &GetTileFromCord(x, y - TileSize, MapData); /////AAAAAAAAAAAAAAAAAA HERE STUPIDUSDFHJAsaf
		//CheckTarget(this, TileTest);
		if (ReproductiveValue >= ReproductionThreshold)
		{
			ReproductiveValue = 0;
			Confirmation Result = TestAvailableLand(Home, this);

			//Result.ValidState = 0x0000;
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


			if (Target != nullptr)
			{
				//AttackState();

			}
			RecieveDamage(20.0f); //Slow decay
			if (PickTarget())
			{

				if (x > -1 && Target != nullptr)
				{
					if (Target->Home != nullptr)
					{
						if (Target->ValidMan)
						{
							if (Target->Home->occupied)
							{
								AttackState();
							}
						}
					}
				}
			}

		}
	}
}



bool Settlement::operator==(Settlement b)
{
	return Home->x == b.GetHomeTile()->x;

}

