#include "pch.h"
#include "TileMap.h"

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
			_TileSet[i][j] = Self_Tile::create(_MapData[i][j]);
			if (j == 0)
			{
				if ((i%2) == 0)
					_TileSet[i][j]->setPositionX(i * 51 + 12);
				else
					_TileSet[i][j]->setPositionX((i-1) * 51);

				if (i == 0)
					_TileSet[i][j]->setPositionY(500);
				else
				{
					float addnum = 0;
					if (i % 2 == 0)
						addnum = 39;
					else
						addnum = 66;
					_TileSet[i][j]->setPositionY(_TileSet[i - 1][j]->getPositionY() - addnum);
				}

			}
			else
			{
				_TileSet[i][j]->setPosition(_TileSet[i][j - 1]->getPositionX() + 126, _TileSet[i][j - 1]->getPositionY() + 27);
			}
			
			_TileSet[i][j]->setZOrder(-1 * _TileSet[i][j]->getPositionY());
			

			inst->addChild(_TileSet[i][j]);
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