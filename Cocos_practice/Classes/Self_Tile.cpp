#include "pch.h"
#include "definition.h"
#include "Self_Tile.h";

std::string Self_Tile::_DictionaryForFilenames[MAX_TILEKIND] =
{
	"tile_null.png",
	"tile_plain.png",
	"tile_forest.png",
	"tile_village.png",
	"tile_barrack.png",
	"tile_barrack.png",
	"tile_rich.png",
	"tile_lake.png",
	"tile_volcano.png",
	"tile_volcano.png",
	"tile_rich.png",
	"tile_move.png"
};

Self_Tile::Self_Tile() 
{
}

Self_Tile::~Self_Tile()
{
}

Self_Tile* Self_Tile::create(TileKind type)
{
	//Self_Tile* sprite = std::make_shared<Self_Tile>();
	Self_Tile* tile = new Self_Tile();

	tile->initWithSpriteFrameName(_DictionaryForFilenames[type]);
	tile->autorelease();
	tile->setTypeOfTile(type);
	tile->setCharacterOnThisTile(nullptr);
	tile->setAnchorPoint(cocos2d::Vec2(0, 0));
	return tile;
}

void Self_Tile::setOwnerPlayer(PlayerInfo pInfo)
{
	if (pInfo != PLAYER_ERR)
	{
		_OwnerPlayer = pInfo;
	}
}

void Self_Tile::ChangeTile(TileKind type)
{
	this->initWithSpriteFrameName(_DictionaryForFilenames[type]);
	this->setTypeOfTile(type);
	this->setAnchorPoint(cocos2d::Vec2(0, 0));
}

std::shared_ptr<Character> Self_Tile::getCharacterOnThisTile()
{
	if (_CharacterOnThisTile)
		return _CharacterOnThisTile;
	else
		return nullptr;
}

void Self_Tile::setCharacterOnThisTile(std::shared_ptr<Character> character)
{
	this->_CharacterOnThisTile = character;
}

bool Self_Tile::CheckNearTile(Self_Tile* tile)
{
	for (int i = 0; i < 6; ++i)
	{
		if (_NearTile[i] == tile)
			return true;
	}
	return false;
}

DirectionKind Self_Tile::ReturnNearTileDirection(Self_Tile* tile)
{
	for (int i = 0; i < 6; ++i)
	{
		if (_NearTile[i] == tile)
			return static_cast<DirectionKind>(i);
	}
	return DIRECTION_ERR;
}

void Self_Tile::setNearTile(int num, Self_Tile* tile)
{
	_NearTile[num] = tile;
}

Self_Tile* Self_Tile::getNearTile(DirectionKind direction)
{
	return _NearTile[direction];
}

PlayerInfo Self_Tile::getOwnerPlayer()
{
	return _OwnerPlayer; 
}

bool Self_Tile::IsTile()
{
	return true; 
}