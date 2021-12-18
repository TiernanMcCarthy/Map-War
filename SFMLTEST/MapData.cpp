#include "MapData.h"
#include "Globals.h"
#include "Tile.h"
#include "Settlement.h"
#include "Spawner.h"
#include <SFML/System.hpp>
#include <vector>
#include <thread>
#include <math.h>
#include <future>


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

	CheatTile = new Settlement();

	CheatTile->RecieveDamage(-999999999);

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
			//delete TempTile;
			X += 1;
		}
		Y += 1;

	}
	//TempTile = NULL;
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


void Gaming(int epic)
{

	for (int i = 0; i < epic; i++)
	{
		printf("Thread using function pointer as a callable \n");
	
	
	}



}

struct Passer
{
public:

	int Index;
	bool Result;


	Passer(int Ind, bool Res)
	{
		Index = Ind;
		Result = Res;
	}

	Passer()
	{
		Index = 0;
		Result = false;
	}
};


Passer GetIndex(int Lower, int Higher, std::vector<Settlement> *Settlements,Settlement *Item,Passer Result)
{
	Settlement* a;
	for (int i = Lower; i <= Higher; i++)  //Maybe wrong? Maybe missing some??
	{
		a=&(*Settlements)[i];
		if (a == Item)
		{
			printf("We FOUND THEM");
			a = NULL;
			delete a;
			Result = Passer(i, true);
			return Passer(i, true);
		}

	}




	return Passer(0, false);


}


// A callable object
class thread_obj {
public:
	void operator()(int Lower, int Higher, std::vector<Settlement>* Settlements, Settlement* Item, Passer& Result)
	{
		Settlement* a;
		for (int i = Lower; i <= Higher; i++)  //Maybe wrong? Maybe missing some??
		{
			a = &(*Settlements)[i];
			if (a == Item)
			{
				printf("We FOUND THEM");
				//a = NULL;
				//delete a;
				Result = Passer(i, true);
				break;
				//return Passer(i, true);
			}

		}
	}
};



int MapManager::FindElementInList(Settlement *Target)
{
	int TotalSize = PlayerList->size();
	//int TotalSize = 0;
	if (TotalSize>= 4)
	{



		int Quarter = TotalSize / 4 - 1;

		Passer Result1;
		Passer Result2;
		Passer Result3;
		Passer Result4;
		//Thread 1 gets 0-Quater;

		//auto future = std::async(GetIndex, 0, Quarter, PlayerList, Target, std::ref(Result1));
		//Passer simple = future.get();


		std::thread th1(thread_obj(), 0, Quarter, PlayerList, Target, std::ref(Result1));

		
		//Thread 2 gets Quarter+1 +Quarter
		std::thread th2(thread_obj(), Quarter+1, Quarter*2, PlayerList, Target, std::ref(Result2));

	


		//Thread 3 gets 2*Quater+1 + Quarter

		std::thread th3(thread_obj(), Quarter*2 + 1, Quarter * 3, PlayerList, Target, std::ref(Result3));



		//Thread 4 gets (2*Quater+1 + Quarter) Onwards to TotalSize-1
		std::thread th4(thread_obj(), Quarter*3 + 1, PlayerList->size()-1, PlayerList, Target, std::ref(Result4));

	
		
		th1.join();
		th2.join();
		th3.join();
		th4.join();


		if (Result1.Result)
		{
			return Result1.Index;
		}
		else if (Result2.Result)
		{
			return Result2.Index;
		}
		else if (Result3.Result)
		{
			return Result3.Index;
		}
		else if (Result4.Result)
		{
			return Result4.Index;
		}

	}


	return -1;

}

int MapManager::SlowSearchInt(Settlement *X)
{

	Settlement* a;
	for (int i = 0; i < PlayerList->size(); i++)
	{
		a = &(*PlayerList)[i];
		if (a->GetHomeTile()->x == X->GetHomeTile()->x)
		{
			return i;
		}


	}


	return -1;
}

bool MapManager::ConfirmTile(Settlement *Tar)
{
	Settlement* a;
	for (int i = 0; i < PlayerList->size(); i++)
	{
		a = &(*PlayerList)[i];
		if (a->GetHomeTile()->x == Tar->GetHomeTile()->x)
		{
			return true;
		}
	}


	return false;
}

void MapManager::RemoveObject(Settlement* Target)
{
	int Index = SlowSearchInt(Target);

	if (Index != -1)
	{
		Target->Delete();
		PlayerList->erase(PlayerList->begin() + Index);
	}

}

//MultiThread FIX!
/*
void MapManager::RemoveObject(Settlement *Target)
{
	//Prevent invalid execution
	int Index = FindElementInList(Target);


	if (PlayerList != NULL)
	{

		if (Index <= PlayerList->size() - 1 && Index != -1)
		{

			//Clear all data within
			Settlement* a = &(*PlayerList)[Index];
			a->Delete();

			//delete a;
			//a = NULL;


			//Remove from Vector Array

			PlayerList->erase(PlayerList->begin() + Index);



		}

	}


}*/


Settlement& MapManager::SlowSearch(int X)
{
	
	Settlement* a;
	for (int i = 0; i < PlayerList->size();i++)
	{
		a = &(*PlayerList)[i];
		if (a->GetHomeTile()->x == X)
		{
			return *a;
		}


	}


	return *(new Settlement());
}

/*

printf("Threads 1 and 2 and 3 "
		"operating independently");

	// This thread is launched by using
// function pointer as callable
	std::thread th1(Gaming, 3);


	// This thread is launched by using
   // function object as callable
	std::thread th2(thread_obj(), 3);

	auto f = [](int x) {
		for (int i = 0; i < x; i++)
			printf("Thread using lambda"
			" expression as callable\n");
	};


	// This thread is launched by using
   // lamda expression as callable
	std::thread th3(f, 3);

	// Wait for the threads to finish
	// Wait for thread t1 to finish
	th1.join();

	// Wait for thread t2 to finish
	th2.join();

	// Wait for thread t3 to finish
	th3.join();


	printf("Threads have finished!");

	return 0;




*/