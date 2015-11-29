#pragma once

class Character;
//타일의 종류를 담아두는 set

class Self_Tile : public cocos2d::Sprite
{

public:
	static std::shared_ptr<Self_Tile> create(TileKind type);

	/*
	@brief		매개변수로 주어진 타일이 인근에 위치한 타일인 경우, 해당 타일의 상대 숫자를 반환한다
				해당 숫자는 좌측 하단을 0으로하여, 시계 반대 방향으로 ++ 된다.
				해당 숫자는 sprite 생성시, 초기 sprite의 기준이 된다.
	@warning	인근에 해당 타일이 없는 경우 -1을 반환한다.
	*/
	bool CheckNearTile(std::shared_ptr<Self_Tile> tile);
	bool IsTile();
	void ChangeTile(TileKind type);
	void setOwnerPlayer(PlayerInfo pInfo);
	void setCharacterOnThisTile(std::shared_ptr<Character> character);
	void setNearTile(int num, std::shared_ptr<Self_Tile> tile);

	DirectionKind ReturnNearTileDirection(std::shared_ptr<Self_Tile> tile);	
	std::shared_ptr<Self_Tile>		getNearTile(DirectionKind direction);
	PlayerInfo		getOwnerPlayer();
	std::shared_ptr<Character> getCharacterOnThisTile();

	CC_SYNTHESIZE(TileKind, _typeOfTile, TypeOfTile);

	Self_Tile();
	~Self_Tile();

private:
	//타일 종류에 따른 스프라이트 파일명을 저장해둘 배열
	static std::string _DictionaryForFilenames[MAX_TILEKIND];

	//타일의 소유주
	PlayerInfo _OwnerPlayer;
	std::shared_ptr<Character> _CharacterOnThisTile = nullptr;
	std::shared_ptr<Self_Tile> _NearTile[6];
};