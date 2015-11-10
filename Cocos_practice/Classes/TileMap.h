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
	
	///# 아래 두 2차원 배열을 안전하게 바꿀것:  http://blog.naver.com/spacesun/140202708191
	Self_Tile* _TileSet[9][8];
	static TileKind _MapData[9][8];
	
	TileMap();
	TileMap(const TileMap& other); ///# 이거는 private로 해놓았는데 복사대입 연산자 operator=는 왜 private로 안해놓았는가? 항상 복사생성자와 복사대입연산자는 세트로... 왜 그럴까?
	static TileMap* inst;


};
