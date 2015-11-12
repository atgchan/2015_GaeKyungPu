#pragma once
#include "definition.h"

class Character;

class BattleManager
{
public:
	BattleManager();
	~BattleManager();
	void	BattleBetween(Character* attacker, Character* defender);
	void	SetAttackFormation(Character* attacker);
	void	SetDefenseFormation(Character* defender);

private:
	std::list<Character*>	_CurrentAttackFormation;
	std::list<Character*>	_CurrentDefenseFormation;
};