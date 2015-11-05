#pragma once
#include "Self_Tile.h"


enum CharacterAngle
{
	ANGLE_DOWN_LEFT,
	ANGLE_DOWN,
	ANGLE_DOWN_RIGHT,
	ANGLE_UP_RIGHT,
	ANGLE_UP,
	ANGLE_UP_LEFT,
	ANGLE_ERR = -1
};

enum RotateDirection
{
	ROTATE_LEFT,
	ROTATE_RIGHT,
	ROTATE_ERR = -1
};


class Character : public cocos2d::Sprite
{
public:
	/**
	@brief	플레이어의 종류(레드, 블루)를 받아와서 해당 팀에 속하는 색깔의 캐릭터 스프라이트를 생성한다.
	*/
	static Character* create(PlayerInfo currentPlayerInfo);

	/**
	@brief	방향을 받아서 해당 방향으로 스프라이트 이미지를 회전한다.
	@args	돌릴 방향(RotateDirection enum이다.), 돌릴 character의 포인터
	*/
	void rotateToDirection(RotateDirection, Character* character);

	/**
	@brief	타일 카인드를 하나 받아와서 현재 캐릭터가 올라와있는 타일과 동일한 종류인지 검사하고 bool을 리턴한다.
	*/
	bool isOnTile(TileKind tileTypeToCheck);
	
	bool isTile(){ return false; }

private:
	CC_SYNTHESIZE(CharacterAngle, CurrentAngle, CurrentAngle);
	CC_SYNTHESIZE(Self_Tile*, CurrentTile, CurrentTile);
	CC_SYNTHESIZE(PlayerInfo, CurrentPlayerInfo, CurrentPlayerInfo);

};