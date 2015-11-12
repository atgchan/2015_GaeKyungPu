#pragma once
class Character;

class BattleManager
{
public:
	BattleManager();
	~BattleManager();
	void	BattleBetween(Character*, Character*);
	void	SetAttackPower();
};