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
	static std::string CharacterAnimation::GetDirectionName(int spriteNum); ///# ?? Ŭ���� �ȿ� Ŭ���� ������ ��? 
	///# ��Ʈ��ó�� ũ�Ⱑ Ŀ���� �ִ� ��ü�� ��~���� �����ϴ� ���� ��ȿ����. const ref�� �����ϴ� ���� ����.
	static std::string LoadPlist(PlayerInfo cPInfo, std::string frameName);
};