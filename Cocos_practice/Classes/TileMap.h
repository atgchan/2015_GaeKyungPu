#pragma once
#include <array>
USING_NS_CC;

#include "definition.h"
#include "Self_Tile.h"
#include "Character.h"

class TileMap : public Layer
{
public:
	static TileMap* getInstance();
	~TileMap();

	bool	create();
	bool	CreateMap(int map_id);

	void	setCharacterOnTile(Character* character, Self_Tile* tile, bool moveMode = false);
	void	KillCharacter(Character* target);
	
	std::vector<Self_Tile*> getRichTiles();
	std::vector<Self_Tile*> getVolcanoTiles();

private:
	static TileMap*	_Inst;

	TileMap();
	TileMap(const TileMap& other);
	TileMap& operator=(TileMap& other);

	void	SetTotalNearTile();
	void	MakeMapData(int width, int height, int map_id);

	std::array<std::array<Self_Tile*, MAP_MAX_WIDTH>, MAP_MAX_HEIGHT> _TileSet;
	
	std::vector<Self_Tile*> _RichTiles;
	std::vector<Self_Tile*> _VolcanoTiles;
	std::vector<std::vector<TileKind>> _SQLMapData;
	std::map<std::string, TileKind>* _TileKind_Dictionary;
};