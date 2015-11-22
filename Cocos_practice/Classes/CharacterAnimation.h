#pragma once
#include <array>

class Character;

class CharacterAnimation
{
public:
	static Animation*	CreateAnimationDefault(PlayerInfo cPInfo, int spriteNum);
	static Animation*	CreateAnimationMove(PlayerInfo cPInfo, int spriteNum);
	static Animation*	CreateAnimationAttack(PlayerInfo cPInfo, int spriteNum);
	static Animation*	CreateAnimationBeHit(PlayerInfo cPInfo, int spriteNum);
	static void			setAnimationDefault(Character* targetCharacter);

private:
	static std::string	GetDirectionName(int spriteNum);
	static std::string	LoadPlist(PlayerInfo cPInfo, std::string frameName);
};

