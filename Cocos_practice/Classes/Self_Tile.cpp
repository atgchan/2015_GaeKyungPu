#include "pch.h"
#include "definition.h"
#include "Self_Tile.h";

std::string Self_Tile::DictionaryForFilenames[10] = 
{
	"Map/tile_null.png",
	"Map/tile_plain.png",
	"Map/tile_forest.png",
	"Map/tile_village.png",
	"Map/tile_barrack.png",
	"Map/tile_barrack.png",
	"Map/tile_rich.png",
	"Map/tile_lake.png",
	"Map/tile_volcano.png",
	"Map/tile_volcano.png"
};

Self_Tile::Self_Tile() 
{

}

Self_Tile::~Self_Tile()
{

}

Self_Tile* Self_Tile::create(TileKind type)
{
	Self_Tile* sprite = new Self_Tile();

	if (sprite && (sprite->initWithFile(DictionaryForFilenames[type])))
	{
		sprite->autorelease();
		sprite->setTypeOfTile(type);
		sprite->setCharacterOnThisTile(nullptr);
		sprite->setAnchorPoint(cocos2d::Vec2(0, 0));
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;

}

void Self_Tile::setOwnerPlayer(PlayerInfo pInfo)
{
	if (pInfo != PLAYER_ERR)
	{
		ownerPlayer = pInfo;
	}
}

void Self_Tile::changeTile(TileKind type)
{
	this->initWithFile(DictionaryForFilenames[type]);
	this->setTypeOfTile(type);
	this->setAnchorPoint(cocos2d::Vec2(0, 0));
}

Character* Self_Tile::getCharacterOnThisTile()
{
	if (characterOnThisTile)
		return characterOnThisTile;
	else
		return nullptr;
}

void Self_Tile::setCharacterOnThisTile(Character* character)
{
	this->characterOnThisTile = character;
}

//void Self_Tile::setPositionInt(int _xPos, int _yPos)
//{
//	xPos = _xPos;
//	yPos = _yPos;
//}

DirectionKind Self_Tile::CheckNearTileAndReturnItsDirection(Self_Tile* tile)
{
	for (int i = 0; i < 6; ++i)
	{
		if (nearTile[i] == tile)
			return static_cast<DirectionKind>(i);
	}
	return DIRECTION_ERR;
}

void Self_Tile::setNearTile(int num, Self_Tile* tile)
{
	nearTile[num] = tile;
}

Self_Tile* Self_Tile::GetNearTile(DirectionKind direction)
{
	return nearTile[direction];
}
