#include "pch.h"
#include "Self_Tile.h";

std::string Self_Tile::DictionaryForFilenames[10] = {
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
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
