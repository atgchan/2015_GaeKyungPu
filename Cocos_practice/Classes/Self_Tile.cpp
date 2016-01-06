#include "pch.h"
#include "definition.h"
#include "Self_Tile.h";
#include "Character.h"

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
	"tile_volcano_activated.png",
	"tile_lava.png",
	"tile_rich.png",
	"tile_move.png"
};

Self_Tile::Self_Tile(TileKind type)
{
	///# 생성자를 사용할거면, 모든 멤버변수가 초기화되는지 확인하고 기본값으로 초기화 할 것

	if (type == TILE_FOREST)
		_FoodToConsume = 2;
}

Self_Tile::~Self_Tile()
{
}

Self_Tile* Self_Tile::create(TileKind type)
{
	Self_Tile* tile = new Self_Tile(type);

	tile->initWithSpriteFrameName(_DictionaryForFilenames[type]);
	tile->autorelease();
	tile->setTypeOfTile(type);
	tile->setCharacterOnThisTile(nullptr);
	tile->setAnchorPoint(cocos2d::Vec2(0, 0));
	tile->setName("Tile");
	return tile;
}

void Self_Tile::setOwnerPlayer(PlayerInfo pInfo)
{
	if (pInfo != PLAYER_ERR)
		_OwnerPlayer = pInfo;
}

void Self_Tile::ChangeTile(TileKind type)
{
	this->setSpriteFrame(_DictionaryForFilenames[type]);
	this->setTypeOfTile(type);
}

Character* Self_Tile::getCharacterOnThisTile()
{
	if (_CharacterOnThisTile != nullptr)
		return _CharacterOnThisTile;
	else
		return nullptr;
}

void Self_Tile::setCharacterOnThisTile(Character* character)
{
	this->_CharacterOnThisTile = character;
}

bool Self_Tile::CheckNearTile(Self_Tile* tile)
{
	for (int i = 0; i < DIRECTION_MAX; ++i)
	{
		if (_NearTile[i] == tile)
			return true;
	}
	return false;
}

DirectionKind Self_Tile::getNearTileDirection(Self_Tile* tile)
{
	for (int i = 0; i < DIRECTION_MAX; ++i)
	{
		if (_NearTile[i] == tile)
			return static_cast<DirectionKind>(i);
	}
	return DIRECTION_ERR;
}

bool Self_Tile::isMovableTile()
{
	if (getTypeOfTile() == TILE_LAVA || getTypeOfTile() == TILE_VOLCANO || getTypeOfTile()==TILE_VOLCANO_ACTIVATED || getTypeOfTile() == TILE_NULL || getTypeOfTile() == TILE_LAKE)
		return false;
	return true;
}

bool Self_Tile::isSpawnable()
{
	if (getTypeOfTile() == TILE_BARRACK || getTypeOfTile() == TILE_HEADQUARTER)
		return true;
	return false;
}

int Self_Tile::getFoodToConsume()
{
	return _FoodToConsume;
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

void Self_Tile::CaculateAttackPowerAllNearTile(bool displayAlso /*= false*/)
{

	for (int i = DIRECTION_DOWN_LEFT; i != DIRECTION_MAX; ++i)
	{
		Character* tCharacter = getNearTile(static_cast<DirectionKind>(i))->getCharacterOnThisTile();
		if (tCharacter)
			tCharacter->CalculateAttackPower(displayAlso);
	}
}
