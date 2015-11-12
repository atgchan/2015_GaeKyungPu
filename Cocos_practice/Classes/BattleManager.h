#pragma once
#include "definition.h"

class Character;

class BattleManager
{
public:
	BattleManager();
	~BattleManager();
	void	BattleBetween(Character* attacker, Character* defender);
	void	SetAttackPower(std::list<Character*>* attackersCharacterList);
};