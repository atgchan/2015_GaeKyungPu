#pragma once
#include <array>

class Character;

class CharacterAnimation
{
public:
	static CharacterAnimation* getInstance();
	void	Init();

	Animation*	getAnimationDefault(PlayerInfo cPInfo, DirectionKind dir);
	Animation*	getAnimationMove(PlayerInfo cPInfo, DirectionKind dir);
	Animation*	getAnimationAttack(PlayerInfo cPInfo, DirectionKind dir);
	Animation*	getAnimationBeHit(PlayerInfo cPInfo, DirectionKind dir);
	

	//void		setAnimationDefault(Character* targetCharacter);
	static void	Terminate();
private:
	CharacterAnimation() {};
	~CharacterAnimation();

	static CharacterAnimation* _Inst;

	cocos2d::Vector<Animation*> _AnimationArray;

	Animation*	CreateAnimationDefault(PlayerInfo cPInfo, DirectionKind dir);
	Animation*	CreateAnimationMove(PlayerInfo cPInfo, DirectionKind dir);
	Animation*	CreateAnimationAttack(PlayerInfo cPInfo, DirectionKind dir);
	Animation*	CreateAnimationBeHit(PlayerInfo cPInfo, DirectionKind dir);

	std::string	GetDirectionName(int spriteNum);
	std::string	LoadPlist(PlayerInfo cPInfo, std::string frameName);
};
