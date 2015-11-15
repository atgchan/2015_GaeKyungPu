#pragma once
#include <array>

class CharacterAnimation
{
public:
	static Animation* CreateAnimationDefault(PlayerInfo cPInfo, int spriteNum);
	static Animation* CreateAnimationMove(PlayerInfo cPInfo, int spriteNum);
	static Animation* CreateAnimationAttack(PlayerInfo cPInfo, int spriteNum);
	static Animation* CreateAnimationBeHit(PlayerInfo cPInfo, int spriteNum);

private:
	static std::string CharacterAnimation::GetDirectionName(int spriteNum);
};