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
	void KillCharacter(Character* target);

	void		Terminate();
private:
	
	///# 아래 두 2차원 배열을 안전하게 바꿀것:  http://blog.naver.com/spacesun/140202708191
	Self_Tile* _TileSet[11][10];
	static TileKind _MapData[11][10];
	
	TileMap();
	TileMap(const TileMap& other);
	TileMap& operator=(TileMap& other);
	static TileMap* inst;


};
