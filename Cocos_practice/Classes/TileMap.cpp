#include "pch.h"
#include "TileMap.h"
#include "GameSceneManager.h"
#include "Odbc.h"

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

void TileMap::MakeMapData(int max_width, int max_height, int map_id)
{
	Odbc* mysql = Odbc::GetInstance();
	if (mysql->IsConnect() == false)
		mysql->Connect(L"me", L"testudo", L"next!!@@##$$");

	std::vector<TileKind> tempMapData;
	for (int height = 0; height < max_height; ++height){
		tempMapData.clear();

		for (int width = 0; width < max_width; ++width){
			std::string sql_tile_kind =  mysql->GetMapData(width, height, map_id);
			sql_tile_kind.pop_back();
			std::map<std::string, TileKind>::iterator tile = _TileKind_Dictionary->find(sql_tile_kind);
			tempMapData.push_back(tile->second);
		}
		_SQLMapData.push_back(tempMapData);
	}
}

bool TileMap::CreateMap(int map_id)
{
	Odbc* mysql = Odbc::GetInstance();
	int max_width = mysql->GetMapInfo(map_id, SQL_WIDTH);
	int max_height = mysql->GetMapInfo(map_id, SQL_HEIGHT);

	MakeMapData(max_width, max_height, map_id);

	for (int i = 0; i < max_height; ++i)
	{
		for (int j = 0; j < max_width; ++j)
		{
			float positionX;
			float positionY;

			_TileSet[i][j] = Self_Tile::create(_SQLMapData[i][j]);

			if (_TileSet[i][j]->getTypeOfTile() == TILE_RICH)
				_RichTiles.push_back(_TileSet[i][j]);

			if (_TileSet[i][j]->getTypeOfTile() == TILE_VOLCANO)
				_VolcanoTiles.push_back(_TileSet[i][j]);

			if (j == 0)
			{
				if (((i - 1) % 2) == 0)
					positionX = i * 51 + 12 - 200;
				else
					positionX = (i - 1) * 51 - 200;

				if (i == 0)
					positionY = 450;
				else
				{
					float addnum = 0;
					if ((i - 1) % 2 == 0)
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
			_TileSet[i][j]->setZOrder(-100 * positionY);
			_TileSet[i][j]->setPosition(positionX, positionY);
			_Inst->addChild(_TileSet[i][j]);

		}
	}
	for (int i = MAP_MAX_HEIGHT - 1; i >= 0; --i)
	{
		for (int j = 0; j < MAP_MAX_WIDTH; ++j)
			GameSceneManager::getInstance()->PushTileToList(_TileSet[i][j]);
	}
	//	다음 함수에서 모든 타일을 순회하여 tile마다 nearTile을 저장한다.
	SetTotalNearTile();

	_TileSet[7][3]->setPositionY(_TileSet[7][3]->getPositionY() + 12);
	_TileSet[6][3]->setPositionY(_TileSet[6][3]->getPositionY() + 12);
	_TileSet[3][5]->setPositionY(_TileSet[3][5]->getPositionY() + 12);
	_TileSet[4][6]->setPositionY(_TileSet[4][6]->getPositionY() + 12);

	_TileSet[7][2]->setOwnerPlayer(PLAYER_RED);
	//_TileSet[7][2]->setPositionY(_TileSet[7][2]->getPositionY() + 9);
	_TileSet[3][6]->setOwnerPlayer(PLAYER_BLUE);
	//_TileSet[3][6]->setPositionY(_TileSet[3][6]->getPositionY() + 9);

	return true;
}

void TileMap::setCharacterOnTile(Character* character, Self_Tile* tile, bool moveMode /*= false*/)
{
	tile->setCharacterOnThisTile(character);
	float xPos = tile->getPositionX();
	float yPos = tile->getPositionY();

	character->setPosition(xPos +84, yPos +60);
	if(!moveMode)
		addChild(character);
}

void TileMap::KillCharacter(Character* target)
{
	this->removeChild(target);
}
std::vector<Self_Tile*> TileMap::getRichTiles()
{
	return _RichTiles;
}
std::vector<Self_Tile*> TileMap::getVolcanoTiles()
{
	return _VolcanoTiles;
}

TileMap::TileMap()
{
	typedef std::pair<std::string, TileKind> TilePair;

	_TileKind_Dictionary = new std::map<std::string, TileKind>;
	_TileKind_Dictionary->insert(TilePair("TILE_NULL", TILE_NULL));
	_TileKind_Dictionary->insert(TilePair("TILE_PLAIN", TILE_PLAIN));
	_TileKind_Dictionary->insert(TilePair("TILE_FOREST", TILE_FOREST));
	_TileKind_Dictionary->insert(TilePair("TILE_VILLAGE", TILE_VILLAGE));
	_TileKind_Dictionary->insert(TilePair("TILE_HEADQUARTER", TILE_HEADQUARTER));
	_TileKind_Dictionary->insert(TilePair("TILE_BARRACK", TILE_BARRACK));
	_TileKind_Dictionary->insert(TilePair("TILE_RICH", TILE_RICH));
	_TileKind_Dictionary->insert(TilePair("TILE_LAKE", TILE_LAKE));
	_TileKind_Dictionary->insert(TilePair("TILE_VOLCANO", TILE_VOLCANO));
	_TileKind_Dictionary->insert(TilePair("TILE_VOLCANO_ACTIVATED", TILE_VOLCANO_ACTIVATED));
	_TileKind_Dictionary->insert(TilePair("TILE_LAVA", TILE_LAVA));
	_TileKind_Dictionary->insert(TilePair("TILE_RICH_SIDE", TILE_RICH_SIDE));
	_TileKind_Dictionary->insert(TilePair("TILE_MOVE", TILE_MOVE));
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

TileMap::~TileMap()
{
	delete _TileKind_Dictionary;
	_Inst = nullptr;
}
