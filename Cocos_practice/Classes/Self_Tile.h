#ifndef Self_Tile_h__
#define Self_Tile_h__

///# ifndef 쓰지말고 pragma once써라.. 지금은 쌍팔년도가 아님 ㅎㅎ
///# 그리고 파일 이름 형태도 통일 할 것.. _를 쓰든 CamelCase를 쓰든..

class Character;
//타일의 종류를 담아두는 set

class Self_Tile : public cocos2d::Sprite
{
	///# 코딩 컨벤션: private를 앞에 놓든, 퍼블릭을 앞에 놓든 통일 할 것..
private:
	//타일 종류에 따른 스프라이트 파일명을 저장해둘 배열
	static std::string DictionaryForFilenames[10]; ///# 상수값은 하드코딩 하지 말 것 반드시 따로 define또는 const로 뺄 것.

	//타일의 소유주
	PlayerInfo ownerPlayer;
	Character* characterOnThisTile;

public:
	
	static Self_Tile* create(TileKind type);
	void setOwnerPlayer(PlayerInfo pInfo);
	PlayerInfo getOwnerPlayer(){ return ownerPlayer; }
	void changeTile(TileKind type);
	Character* getCharacterOnThisTile();
	void setCharacterOnThisTile(Character* character);

	CC_SYNTHESIZE(TileKind, _typeOfTile, TypeOfTile);
	
	bool isTile(){ return true; }

	Self_Tile();
	~Self_Tile();

};
#endif // Self_Tile_h__
