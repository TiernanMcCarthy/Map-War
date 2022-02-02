#include "GameManager.h"
#include "Settlement.h"
#include "MapData.h"
GameManager::GameManager(MapManager map)
{
	mapManager = &map;

}


void GameManager::Execute(MapManager map)
{
	//Settlement a = (*mapManager->PlayerList)[0];
	int OriginalLength = map.PlayerList->size();
	for (int i = 0; i < map.PlayerList->size(); i++)
	{
		Settlement* a;
		a = &(*map.PlayerList)[i];
		a->GetHomeTile()->SetAttributes(true, true, *a);
		a->Simulate();

	}



}