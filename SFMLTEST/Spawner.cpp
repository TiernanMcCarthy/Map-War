#include "Spawner.h"
#include "Settlement.h"

#include <math.h>
void Spawner::SpawnCharacters()
{
	srand(time(NULL));
	int count = NumberOfAgents;
	int upperlimit=mapManager->TileMap.size();
	while (count > 0)
	{
		int Position = rand() % upperlimit +1;

		if (mapManager->TileMap[Position].land)
		{
			count--;
			CreateCharacter(Position, count);
		}
	}
}

void Spawner::CreateCharacter(int TileLocation,int i)
{
	mapManager->PlayerList->push_back(Settlement(mapManager->TileMap[TileLocation], Colours[i], *mapManager));

	Settlement* a = &(*mapManager->PlayerList)[mapManager->PlayerList->size() - 1];

	mapManager->TileMap[TileLocation].SetAttributes(true, true, *a);

	a->SetTarget(NULL);


}

void Spawner::CreateCharacter(Settlement *Original, Tile *NewTile)
{
	mapManager->PlayerList->push_back(Settlement(*NewTile, Original->GetColour(), *mapManager));
	Settlement* a = &(*mapManager->PlayerList)[mapManager->PlayerList->size() - 1];
	NewTile->SetAttributes(true, true, *a);
	a->SetTarget(NULL);


}

Spawner::Spawner()
{

}