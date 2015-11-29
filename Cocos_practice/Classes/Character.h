#pragma once
#include "Self_Tile.h"


class Character : public cocos2d::Sprite
{
public:
	/**
	@brief	플레이어의 종류(레드, 블루)를 받아와서 해당 팀에 속하는 색깔의 캐릭터 스프라이트를 생성한다.
			Red Blue 구분은 CharacterAnimation내부에서 구분한다.
			create은 그저 캐릭터 객체를 만들 뿐, 실제 그래픽 구현은 CharacterAnimation에서 처리
	*/
	static std::shared_ptr<Character> create(PlayerInfo currentPlayerInfo, DirectionKind spriteNum);

	/**
	@brief	방향을 받아서 해당 방향으로 스프라이트 이미지를 회전한다.
	@args	돌릴 방향(RotateDirection enum이다.), 돌릴 character의 포인터
	*/
	void RotateToDirection(RotateDirection);
	void RotateToDirection(DirectionKind);

	/**
	@brief	타일 카인드를 하나 받아와서 현재 캐릭터가 올라와있는 타일과 동일한 종류인지 검사하고 bool을 리턴한다.
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

