#pragma once
///# ifndef 쓰지말고 pragma once써라.. 지금은 쌍팔년도가 아님 ㅎㅎ
///# 그리고 파일 이름 형태도 통일 할 것.. _를 쓰든 CamelCase를 쓰든..

class Character;
//타일의 종류를 담아두는 set

class Self_Tile : public cocos2d::Sprite
{

public:

	static Self_Tile* create(TileKind type);
	void setOwnerPlayer(PlayerInfo pInfo);
	PlayerInfo getOwnerPlayer(){ return ownerPlayer; }
	void changeTile(TileKind type);
	Character* getCharacterOnThisTile();
	void setCharacterOnThisTile(Character* character);
	CC_SYNTHESIZE(TileKind, _typeOfTile, TypeOfTile);
	
	/*
	void setPositionInt(int _xPos, int _yPos);
	int getPositionIntX() { return xPos; }
	int getPositionIntY() { return yPos; }
	*/

	bool isTile(){ return true; }

	/*
	@brief		매개변수로 주어진 타일이 인근에 위치한 타일인 경우, 해당 타일의 상대 숫자를 반환한다
				해당 숫자는 좌측 하단을 0으로하여, 시계 반대 방향으로 ++ 된다.
				해당 숫자는 sprite 생성시, 초기 sprite의 기준이 된다.
	@warning	인근에 해당 타일이 없는 경우 -1을 반환한다.
	*/
	int	isNearTile(Self_Tile* tile);
	void setNearTile(int num, Self_Tile* tile);

	Self_Tile();
	~Self_Tile();
	
private:
	//타일 종류에 따른 스프라이트 파일명을 저장해둘 배열
	static std::string DictionaryForFilenames[10]; ///# 상수값은 하드코딩 하지 말 것 반드시 따로 define또는 const로 뺄 것.

	//타일의 소유주
	PlayerInfo ownerPlayer;
	Character* characterOnThisTile;
	Self_Tile* nearTile[6];
	
	//int xPos, yPos;
};