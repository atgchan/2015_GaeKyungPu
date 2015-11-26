#include "pch.h"
#include "TileMap.h"
#include "GameSceneManager.h"

TileMap* TileMap::getInstance()
{
	if (_Inst == nullptr)
	{
		_Inst = new TileMap();
		_Inst->setName("TileMap");
	}
	return _Inst;
}

TileMap* TileMap::_Inst = nullptr;

std::array<std::array<TileKind, MAP_MAX_WIDTH>, MAP_MAX_HEIGHT> TileMap::_NewMapData =
{ {
	{ TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL },
	{ TILE_NULL, TILE_NULL, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL },
	{ TILE_NULL, TILE_NULL, TILE_RICH_SIDE, TILE_LAKE, TILE_VILLAGE, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_NULL, TILE_NULL },
	{ TILE_NULL, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_FOREST, TILE_HEADQUARTER, TILE_PLAIN, TILE_NULL, TILE_NULL },
	{ TILE_NULL, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_RICH, TILE_RICH, TILE_FOREST, TILE_PLAIN, TILE_NULL, TILE_NULL },
	{ TILE_NULL, TILE_PLAIN, TILE_PLAIN, TILE_RICH, TILE_VOCANO, TILE_RICH, TILE_PLAIN, TILE_PLAIN, TILE_NULL, TILE_NULL },
	{ TILE_NULL, TILE_NULL, TILE_PLAIN, TILE_FOREST, TILE_RICH, TILE_RICH, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_NULL },
	{ TILE_NULL, TILE_PLAIN, TILE_HEADQUARTER, TILE_FOREST, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_NULL, TILE_NULL },
	{ TILE_NULL, TILE_NULL, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_VILLAGE, TILE_LAKE, TILE_RICH_SIDE, TILE_NULL, TILE_NULL },
	{ TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_PLAIN, TILE_PLAIN, TILE_PLAIN, TILE_NULL, TILE_NULL, TILE_NULL },
	{ TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL }
} };

bool TileMap::create()
{
	for (int i = 0; i < MAP_MAX_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_MAX_WIDTH; ++j)
		{
			float positionX;
			float positionY;
			_TileSet[i][j] = Self_Tile::create(_NewMapData[i][j]);

			if (j == 0)
			{
				if (((i-1) % 2) == 0)
				{
					positionX = i * 51 + 12 -200;
				}
				else
				{
					positionX = (i - 1) * 51 - 200;
				}

				if (i == 0)
				{ 
					positionY = 450;
				}
				else
				{
					float addnum = 0;
					if ((i-1) % 2 == 0)
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

			_Inst->addChild(_TileSet[i][j]);
			GameSceneManager::getInstance()->PushTileToList(rect, _TileSet[i][j]);
		}
	}
//	다음 함수에서 모든 타일을 순회하여 tile마다 nearTile을 저장한다.
	SetTotalNearTile();

	_TileSet[7][2]->setOwnerPlayer(PLAYER_RED);
	_TileSet[3][6]->setOwnerPlayer(PLAYER_BLUE);

	return true;
}

void TileMap::setCharacterOnTile(Character* character, Self_Tile* tile, bool moveMode /*= false*/)
{
	tile->setCharacterOnThisTile(character);
	float xPos = tile->getPositionX();
	float yPos = tile->getPositionY();

	character->setPosition(xPos +80, yPos +60);
	character->setZOrder(tile->getZOrder()+100);
	if(!moveMode)
		addChild(character);
}

void TileMap::KillCharacter(Character* target)
{
	this->removeChild(target);
}

void TileMap::Terminate()
{
	delete this;
}

TileMap::TileMap()
{

}

void TileMap::SetTotalNearTile()
{
	for (int i = 0; i < MAP_MAX_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_MAX_WIDTH; ++j)
		{
			if ((i - 1) % 2 == 0)
			{
				if ((j - 1) >= 0)
					_TileSet[i][j]->setNearTile(0, _TileSet[i][j - 1]);
				if ((i + 1) < MAP_MAX_HEIGHT)
					_TileSet[i][j]->setNearTile(1, _TileSet[i + 1][j]);
				if (((i + 1) < MAP_MAX_HEIGHT) && ((j + 1) < MAP_MAX_WIDTH))
					_TileSet[i][j]->setNearTile(2, _TileSet[i + 1][j + 1]);
				if ((j + 1) < MAP_MAX_WIDTH)
					_TileSet[i][j]->setNearTile(3, _TileSet[i][j + 1]);
				if (((i - 1) >= 0) && ((j + 1) < MAP_MAX_WIDTH))
					_TileSet[i][j]->setNearTile(4, _TileSet[i - 1][j + 1]);
				if ((i - 1) >= 0)
					_TileSet[i][j]->setNearTile(5, _TileSet[i - 1][j]);
			}
			else
			{
				if ((j - 1) >= 0)
					_TileSet[i][j]->setNearTile(0, _TileSet[i][j - 1]);
				if (((i + 1) < MAP_MAX_HEIGHT) && ((j - 1) >= 0))
					_TileSet[i][j]->setNearTile(1, _TileSet[i + 1][j - 1]);
				if ((i + 1) < MAP_MAX_HEIGHT)
					_TileSet[i][j]->setNearTile(2, _TileSet[i + 1][j]);
				if ((j + 1) < MAP_MAX_WIDTH)
					_TileSet[i][j]->setNearTile(3, _TileSet[i][j + 1]);
				if ((i - 1) >= 0)
					_TileSet[i][j]->setNearTile(4, _TileSet[i - 1][j]);
				if (((i - 1) >= 0) && ((j - 1) >= 0))
					_TileSet[i][j]->setNearTile(5, _TileSet[i - 1][j - 1]);
			}
		}
	}
}
