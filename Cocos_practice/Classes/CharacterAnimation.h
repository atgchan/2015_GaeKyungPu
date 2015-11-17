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
	static std::string CharacterAnimation::GetDirectionName(int spriteNum); ///# ?? 클래스 안에 클래스 지정을 왜? 
	///# 스트링처럼 크기가 커질수 있는 객체를 쌩~으로 리턴하는 것은 비효율적. const ref로 리턴하는 것이 좋다.
	static std::string LoadPlist(PlayerInfo cPInfo, std::string frameName);
};