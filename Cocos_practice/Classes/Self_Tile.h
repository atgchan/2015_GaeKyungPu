#ifndef Self_Tile_h__
#define Self_Tile_h__


//타일의 종류를 담아두는 set
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
	//타일 종류에 따른 스프라이트 파일명을 저장해둘 배열
	static std::string DictionaryForFilenames[10];

	//타일의 소유주
	int ownerPlayer;
	Character* characterOnThisTile;
public:
	
	static Self_Tile* create(TileKind type);
	void setOwnerPlayer(PlayerInfo pInfo);
	void changeTile(TileKind type);
	Character* getCharacterOnThisTile(Self_Tile* tile);
	Character* setCharacterOnThisTile(Self_Tile* tile, Character* character);

	CC_SYNTHESIZE(TileKind, _typeOfTile, TypeOfTile);
	Self_Tile();
	~Self_Tile();

};
#endif // Self_Tile_h__
