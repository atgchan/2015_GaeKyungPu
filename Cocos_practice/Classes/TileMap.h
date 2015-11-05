#pragma once
USING_NS_CC;

#include "definition.h"
#include "Self_Tile.h"
#include "Character.h"

class TileMap : public Layer
{
public:
	static TileMap* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new TileMap();
			inst->setName("TileMap");
		}
		return inst;
	}
	bool create();

	void setCharacterOnTile(Character* character, Self_Tile* tile, bool moveMode = false);
	void MoveCharacterTo(Character* character, Self_Tile* tile);
	void killCharacter(Character* target);
private:
	
	Self_Tile* _TileSet[9][8];
	static TileKind _MapData[9][8];
	
	TileMap();
	TileMap(const TileMap& other);
	static TileMap* inst;


};
