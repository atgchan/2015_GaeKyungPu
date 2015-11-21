#pragma once
#include "Self_Tile.h"


class Character : public cocos2d::Sprite
{
public:
	/**
	@brief	�÷��̾��� ����(����, ���)�� �޾ƿͼ� �ش� ���� ���ϴ� ������ ĳ���� ��������Ʈ�� �����Ѵ�.
			Red Blue ������ CharacterAnimation���ο��� �����Ѵ�.
			create�� ���� ĳ���� ��ü�� ���� ��, ���� �׷��� ������ CharacterAnimation���� ó��
	*/
	static Character* create(PlayerInfo currentPlayerInfo, int spriteNum = 0);

	/**
	@brief	������ �޾Ƽ� �ش� �������� ��������Ʈ �̹����� ȸ���Ѵ�.
	@args	���� ����(RotateDirection enum�̴�.), ���� character�� ������
	*/
	void RotateToDirection(RotateDirection);
	void RotateToDirection(DirectionKind);

	/**
	@brief	Ÿ�� ī�ε带 �ϳ� �޾ƿͼ� ���� ĳ���Ͱ� �ö���ִ� Ÿ�ϰ� ������ �������� �˻��ϰ� bool�� �����Ѵ�.
	*/
	bool	IsOnTile(TileKind tileTypeToCheck);
	void	MovoToTile(Self_Tile* dest);
	void	CharacterBeHit();
	void	CharacterAttack();

	int		_AttackPower = 2;
	int		_DefensePower = 2;
	void	SetOwnerPlayer(PlayerInfo pInfo);
	
	const PlayerInfo	GetOwnerPlayer();
	Character*			GetNearCharacter(DirectionKind direction);
	void				InitializeDirection(DirectionKind direction);
	DirectionKind		getCurrentDirectionToShow();
	void				setCurrentDirectionToShow(DirectionKind direction);
	DirectionKind		getCurrentDirection();
	void				setCurrentDirection(DirectionKind direction);
	~Character();
private:
	Character(PlayerInfo cPInfo, int spriteNum);

	PlayerInfo		_OwnerPlayer = PLAYER_ERR;
	DirectionKind	_CurrentDirection = DIRECTION_ERR;
	DirectionKind	_CurrentDirectionToShow = DIRECTION_ERR;
	CC_SYNTHESIZE(Self_Tile*, CurrentTile, CurrentTile);
	CC_SYNTHESIZE(PlayerInfo, CurrentPlayerInfo, CurrentPlayerInfo);
	CC_SYNTHESIZE(AnimationState, AnimState, AnimState);
	

};

