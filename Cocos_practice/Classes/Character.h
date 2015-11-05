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
	@brief	�÷��̾��� ����(����, ���)�� �޾ƿͼ� �ش� ���� ���ϴ� ������ ĳ���� ��������Ʈ�� �����Ѵ�.
	*/
	static Character* create(PlayerInfo currentPlayerInfo);

	/**
	@brief	������ �޾Ƽ� �ش� �������� ��������Ʈ �̹����� ȸ���Ѵ�.
	@args	���� ����(RotateDirection enum�̴�.), ���� character�� ������
	*/
	void rotateToDirection(RotateDirection, Character* character);

	/**
	@brief	Ÿ�� ī�ε带 �ϳ� �޾ƿͼ� ���� ĳ���Ͱ� �ö���ִ� Ÿ�ϰ� ������ �������� �˻��ϰ� bool�� �����Ѵ�.
	*/
	bool isOnTile(TileKind tileTypeToCheck);
	
	bool isTile(){ return false; }

private:
	CC_SYNTHESIZE(CharacterAngle, CurrentAngle, CurrentAngle);
	CC_SYNTHESIZE(Self_Tile*, CurrentTile, CurrentTile);
	CC_SYNTHESIZE(PlayerInfo, CurrentPlayerInfo, CurrentPlayerInfo);

};