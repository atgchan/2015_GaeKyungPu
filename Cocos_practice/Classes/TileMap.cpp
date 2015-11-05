#include "pch.h"
#include "TileMap.h"
#include "GameSceneManager.h"

TileMap* TileMap::inst = NULL;
TileKind TileMap::_MapData[9][8] = {
	{ TILE_NULL, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL },
	{ TILE_NULL, TILE_RICH, TILE_LAKE, TILE_VILLAGE, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_NULL },
	{ TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_FOREST, TILE_HEADQUARTER, TILE_PLAIN, TILE_NULL },
	{ TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_RICH, TILE_RICH, TILE_FOREST, TILE_PLAIN, TILE_NULL },
	{ TILE_PLAIN, TILE_PLAIN, TILE_RICH, TILE_VOCANO, TILE_RICH, TILE_PLAIN, TILE_PLAIN, TILE_NULL },
	{ TILE_NULL, TILE_PLAIN, TILE_FOREST, TILE_RICH, TILE_RICH, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN },
	{ TILE_PLAIN, TILE_HEADQUARTER, TILE_FOREST, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_NULL },
	{ TILE_NULL, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_VILLAGE, TILE_LAKE, TILE_RICH, TILE_NULL },
	{ TILE_NULL, TILE_NULL, TILE_NULL, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_NULL, TILE_NULL },
};
bool TileMap::create()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			float positionX;
			float positionY;
			_TileSet[i][j] = Self_Tile::create(_MapData[i][j]);
			if (j == 0)
			{
				if ((i % 2) == 0)
				{
					positionX = i * 51 + 12;
				}
				else
				{
					positionX = (i - 1) * 51;
				}

				if (i == 0)
				{ 
					positionY = 500;
				}
				else
				{
					float addnum = 0;
					if (i % 2 == 0)
						addnum = 39;
					else
						addnum = 66;
					positionY = _TileSet[i - 1][j]->getPositionY() - addnum;
				}

			}
			else
			{
				positionX = _TileSet[i][j - 1]->getPositionX() + 126;
				positionY = _TileSet[i][j - 1]->getPositionY() + 27;
			}
			_TileSet[i][j]->setZOrder(-1 * positionY);

			//클릭이 유효한 범위를 나타내는 네모 박스를 만들어서 같이 전달한다.(클릭 체크용)
			Rect rect = CCRectMake(positionX+45, positionY+30, _TileSet[i][j]->getContentSize().width-70, _TileSet[i][j]->getContentSize().height-30);

			_TileSet[i][j]->setPosition(positionX, positionY);


			inst->addChild(_TileSet[i][j]);
			GameSceneManager::getInstance()->pushTileToList(rect, _TileSet[i][j]);
			//this->setAnchorPoint(Point(0.5, 0.0));
		}
	}

	return true;
}

void TileMap::setCharacterOnTile(Character* character, Self_Tile* tile)
{
	float xPos = tile->getPositionX();
	float yPos = tile->getPositionY();
	//수정소요 ㅇㅇ
	character->setPosition(xPos +80, yPos +60);
	character->setZOrder(tile->getZOrder()+100);
	this->addChild(character);
}

void TileMap::MoveCharacterTo(Character* character, Self_Tile* tile)
{
	float xPos = tile->getPositionX();
	float yPos = tile->getPositionY();
	character->setPosition(xPos, yPos);
}

void TileMap::killCharacter(Character* target)
{
	this->removeChild(target);
}

TileMap::TileMap()
{

}