#ifndef __TILE_MAP_H_
#define __TILE_MAP_H_
#include "Self_Tile.h"
USING_NS_CC;

class TileMap : public Layer
{
private:
	
	Self_Tile* _TileSet[9][8];
	static TileKind _MapData[9][8];
	
	TileMap();
	TileMap(const TileMap& other);
	static TileMap* inst;

public:
	static TileMap* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new TileMap();
		}
		return inst; 
	}
	bool createMap();
};

#endif