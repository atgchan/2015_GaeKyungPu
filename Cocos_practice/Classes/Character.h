#pragma once
#include "Self_Tile.h"
#include <memory>

class Character : public cocos2d::Sprite
{
public:
	/**
	@brief	�÷��̾��� ����(����, ���)�� �޾ƿͼ� �ش� ���� ���ϴ� ������ ĳ���� ��������Ʈ�� �����Ѵ�.
			Red Blue ������ CharacterAnimation���ο��� �����Ѵ�.
			create�� ���� ĳ���� ��ü�� ���� ��, ���� �׷��� ������ CharacterAnimation���� ó��
	*/
	static Character* create(PlayerInfo currentPlayerInfo, DirectionKind spriteNum);

	/**
	@brief	������ �޾Ƽ� �ش� �������� ��������Ʈ �̹����� ȸ���Ѵ�.
	@args	���� ����(RotateDirection enum�̴�.), ���� character�� ������
	*/
	void	RotateToDirection(RotateDirection);
	void	RotateToDirection(DirectionKind,bool displayAlso = false);
	void	RotateToDirection(Ref *sender, RotateDirection rotateDirection);

	void MovoToTile(Self_Tile* dest, bool battleMode = true);
	void	CharacterBeHit();
	void	CharacterAttack();

	int		_AttackPower = ATTACK_POWER_DEFAULT;
	void	SetOwnerPlayer(PlayerInfo pInfo);
	void	ShowMovableTile();

	Character* GetNearCharacter(DirectionKind direction);
	const PlayerInfo	GetOwnerPlayer();
	void				InitializeDirection(DirectionKind direction);
	DirectionKind		getCurrentDirectionToShow();
	void				setCurrentDirectionToShow(DirectionKind direction);
	DirectionKind		getCurrentDirection();
	void				setCurrentDirection(DirectionKind direction);
	int					getAttackPower();
	void				setAttackPower(int);

	void				setAttackPowerToDisplay(int);
	int					getAttackPowerToDisplay();
	void				InitAttackPowerSprite();
	void				UpdateAttackPowerSprite();
	int					CalculateDiffBetweenDirections(DirectionKind dir1, DirectionKind dir2);
	void				CalculateAttackPower(bool displayAlso = false);
	void				CalculateAttackPowerAllNearTile(bool displayAlso = false);
	~Character();

private:
	Character(PlayerInfo cPInfo, DirectionKind spriteNum);

	PlayerInfo		_OwnerPlayer = PLAYER_ERR;
	DirectionKind	_CurrentDirection = DIRECTION_ERR;
	DirectionKind	_CurrentDirectionToShow = DIRECTION_ERR;

	CC_SYNTHESIZE(Self_Tile*, CurrentTile, CurrentTile);
	CC_SYNTHESIZE(PlayerInfo, CurrentPlayerInfo, CurrentPlayerInfo);
	CC_SYNTHESIZE(AnimationState, AnimState, AnimState);
	
	int		_AttackPowerToDisplay = ATTACK_POWER_DEFAULT;
	cocos2d::Sprite* _AttackPowerBall;
	void setAttackPowerBallNameFromNumber(int);
};

