#pragma once
#include "definition.h"

class Character;

class BattleManager
{
public:
	BattleManager();
	~BattleManager();
	void	BattleBetween(Character* attacker, Character* defender);
	void	GetAttackFormation(Character* attacker);
	void	getDefenseFormation(Character* defender);
};