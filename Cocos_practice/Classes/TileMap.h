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
	
	///# �Ʒ� �� 2���� �迭�� �����ϰ� �ٲܰ�:  http://blog.naver.com/spacesun/140202708191
	Self_Tile* _TileSet[9][8];
	static TileKind _MapData[9][8];
	
	TileMap();
	TileMap(const TileMap& other); ///# �̰Ŵ� private�� �س��Ҵµ� ������� ������ operator=�� �� private�� ���س��Ҵ°�? �׻� ��������ڿ� ������Կ����ڴ� ��Ʈ��... �� �׷���?
	static TileMap* inst;


};
