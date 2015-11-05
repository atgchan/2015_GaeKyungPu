#pragma once
#include "Self_Tile.h"


enum CharacterAngle  ///# 코딩 컨벤션 맞출것 
{
	ANGLE_DOWN_LEFT,
	ANGLE_DOWN,
	ANGLE_DOWN_RIGHT,
	ANGLE_UP_RIGHT,
	ANGLE_UP,
	ANGLE_UP_LEFT,
	ANGLE_ERR = -1 ///# 보통 기본값 또는 에러에 해당하는 놈들은 맨 위로
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
	static Character* create(PlayerInfo currentPlayerInfo, int spriteNum = 0);

	/**
	@brief	방향을 받아서 해당 방향으로 스프라이트 이미지를 회전한다.
	*/
	void rotateToDirection(RotateDirection, Character* character); ///# 아규먼트도 넣어라

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