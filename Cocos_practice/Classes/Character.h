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
	static std::shared_ptr<Character> create(PlayerInfo currentPlayerInfo, DirectionKind spriteNum);

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
	void	MovoToTile(std::shared_ptr<Self_Tile> dest);
	void	CharacterBeHit();
	void	CharacterAttack();

	int		_AttackPower = 2;
	void	SetOwnerPlayer(PlayerInfo pInfo);
	
	const PlayerInfo	GetOwnerPlayer();
	std::shared_ptr<Character> GetNearCharacter(DirectionKind direction);
	void				InitializeDirection(DirectionKind direction);
	DirectionKind		getCurrentDirectionToShow();
	void				setCurrentDirectionToShow(DirectionKind direction);
	DirectionKind		getCurrentDirection();
	void				setCurrentDirection(DirectionKind direction);
	int					getAttackPower();
	void				setAttackPower(int);
	~Character();
private:
	Character(PlayerInfo cPInfo, DirectionKind spriteNum);

	PlayerInfo		_OwnerPlayer = PLAYER_ERR;
	DirectionKind	_CurrentDirection = DIRECTION_ERR;
	DirectionKind	_CurrentDirectionToShow = DIRECTION_ERR;
	CC_SYNTHESIZE(std::shared_ptr<Self_Tile>, CurrentTile, CurrentTile);
	CC_SYNTHESIZE(PlayerInfo, CurrentPlayerInfo, CurrentPlayerInfo);
	CC_SYNTHESIZE(AnimationState, AnimState, AnimState);
	std::shared_ptr<Character>			_ThisShared;

};

