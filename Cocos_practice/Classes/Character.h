#pragma once
#include "Self_Tile.h"


class Character : public cocos2d::Sprite
{
public:
	/**
	@brief	�÷��̾��� ����(����, ���)�� �޾ƿͼ� �ش� ���� ���ϴ� ������ ĳ���� ��������Ʈ�� �����Ѵ�.
	*/
	static Character* create(PlayerInfo currentPlayerInfo, int spriteNum = 0);

	/**
	@brief	������ �޾Ƽ� �ش� �������� ��������Ʈ �̹����� ȸ���Ѵ�.
	@args	���� ����(RotateDirection enum�̴�.), ���� character�� ������
	*/
	void rotateToDirection(RotateDirection);

	/**
	@brief	Ÿ�� ī�ε带 �ϳ� �޾ƿͼ� ���� ĳ���Ͱ� �ö���ִ� Ÿ�ϰ� ������ �������� �˻��ϰ� bool�� �����Ѵ�.
	*/
	bool		isOnTile(TileKind tileTypeToCheck);
	void		MovoToTile(Self_Tile* dest);
	//bool		isTile(){ return false; }

	int			_AttackPower = 0;
	int			_DefensePower = 0;
	const PlayerInfo	GetOwnerPlayer();
	void				SetOwnerPlayer(PlayerInfo pInfo);
	Character*			GetNearCharacter(DirectionKind direction);

	~Character();
private:
	
	Character(PlayerInfo cPInfo, int spriteNum);

	PlayerInfo		_OwnerPlayer = PLAYER_ERR;
	CC_SYNTHESIZE(DirectionKind, CurrentDirection, CurrentDirection);
	CC_SYNTHESIZE(Self_Tile*, CurrentTile, CurrentTile);
	CC_SYNTHESIZE(PlayerInfo, CurrentPlayerInfo, CurrentPlayerInfo);
};