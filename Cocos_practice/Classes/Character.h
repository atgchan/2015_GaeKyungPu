#pragma once
#include "Self_Tile.h"
#include <memory>

class Character : public cocos2d::Sprite
{
public:
	/**
	@brief	플레이어의 종류(레드, 블루)를 받아와서 해당 팀에 속하는 색깔의 캐릭터 스프라이트를 생성한다.
			Red Blue 구분은 CharacterAnimation내부에서 구분한다.
			create은 그저 캐릭터 객체를 만들 뿐, 실제 그래픽 구현은 CharacterAnimation에서 처리
	*/
	static Character* create(PlayerInfo currentPlayerInfo, DirectionKind spriteNum);

	/**
	@brief	방향을 받아서 해당 방향으로 스프라이트 이미지를 회전한다.
	@args	돌릴 방향(RotateDirection enum이다.), 돌릴 character의 포인터
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

