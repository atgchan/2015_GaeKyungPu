#pragma once
#include "Self_Tile.h"
#include <memory>

class Character : public cocos2d::Sprite
{
public:

	static Character* create(PlayerInfo currentPlayerInfo, DirectionKind spriteNum);

	void				RotateToDirection(RotateDirection);
	void				RotateToDirection(DirectionKind,bool displayAlso = false);

	void				MoveToTile(Self_Tile* dest, bool battleMode = true);
	void				CharacterBeHit();
	void				CharacterAttack();

	int					_AttackPower = ATTACK_POWER_DEFAULT;
	void				SetOwnerPlayer(PlayerInfo pInfo);
	void				ShowMovableTile();

	Character*			GetNearCharacter(DirectionKind direction);
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
	int					CalculateDiffBetweenDirections(DirectionKind dir1, DirectionKind dir2);
	void				CalculateAttackPower(bool displayAlso = false);
	void				CalculateAttackPowerAllNearTile(bool displayAlso = false);
	void				resetRotateResource();

	void				setIsMovable(bool);
	bool				getIsMovable();
	void				setIsAttackable(bool);
	bool				getIsAttackable();
	void				ShowBattleIndicator(Self_Tile* tile);

	~Character();

private:
	Character(PlayerInfo cPInfo, DirectionKind spriteNum);

	PlayerInfo				_OwnerPlayer = PLAYER_ERR;
	DirectionKind			_CurrentDirection = DIRECTION_ERR;
	DirectionKind			_CurrentDirectionToShow = DIRECTION_ERR;

	CC_SYNTHESIZE(Self_Tile*, CurrentTile, CurrentTile);
	CC_SYNTHESIZE(PlayerInfo, CurrentPlayerInfo, CurrentPlayerInfo);
	CC_SYNTHESIZE(AnimationState, AnimState, AnimState);

	int						_RotateResource;
	int						_AttackPowerToDisplay = ATTACK_POWER_DEFAULT;
	bool					_IsMovable = true;
	bool					_IsAttackable = true;

	cocos2d::Sprite*		_AttackPowerBall;
	void setAttackPowerBallNameFromNumber(int);

};

