#ifndef Self_Tile_h__
#define Self_Tile_h__

class Character;
//타일의 종류를 담아두는 set

class Self_Tile : public cocos2d::Sprite
{
private:
	//타일 종류에 따른 스프라이트 파일명을 저장해둘 배열
	static std::string DictionaryForFilenames[10];

	//타일의 소유주
	PlayerInfo ownerPlayer;
	Character* characterOnThisTile;
public:
	
	static Self_Tile* create(TileKind type);
	void setOwnerPlayer(PlayerInfo pInfo);
	PlayerInfo getOwnerPlayer(){ return ownerPlayer; }
	void changeTile(TileKind type);
	Character* getCharacterOnThisTile();
	Character* setCharacterOnThisTile(Character* character);

	CC_SYNTHESIZE(TileKind, _typeOfTile, TypeOfTile);
	
	Self_Tile();
	~Self_Tile();

};
#endif // Self_Tile_h__
