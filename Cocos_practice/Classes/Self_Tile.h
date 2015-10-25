#include <map>

enum TileKind {
	TILE_NULL,
	TILE_PLAIN,
	TILE_FOREST,
	TILE_VILLAGE,
	TILE_HEADQUARTER,
	TILE_BARRACK,
	TILE_RICH,
	TILE_LAKE,
	TILE_VOCANO,
	TILE_LAVA
};

class Self_Tile : public cocos2d::Sprite
{
private:
	static std::string DictionaryForFilenames[10];
public:

	static Self_Tile* create(TileKind type);

	CC_SYNTHESIZE(TileKind, _typeOfTile, TypeOfTile);
	Self_Tile();
	~Self_Tile();

};