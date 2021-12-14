#pragma once

class MapManager;


class GameManager
{
public:

	GameManager(MapManager map);
	void Execute(MapManager map);
	

private:

	MapManager *mapManager;


};