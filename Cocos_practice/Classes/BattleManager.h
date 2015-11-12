#pragma once
#include "definition.h"

class Character;

class BattleManager
{
public:
	BattleManager();
	~BattleManager();
	/**
		@brief	병사 두명을 싸움을 붙입니다.
	*/
	void	BattleBetween(Character* attacker, Character* defender);

	/**
		@brief	attacker를 기점으로 하는 공격 대형을 설정합니다.
	*/
	void	SetAttackFormation(Character* attacker);
	
	void	SetDefenseFormation(Character* defender);
	std::list<Character*>	GetCurrentAttackFormation(){ return _CurrentAttackFormation; }
private:
	void SearchGraphAndOverwriteAttackFormation(std::list<Character*> checkedNode, Character* currentNode, int currentDepth);
	std::list<Character*>	_CurrentAttackFormation;
	std::list<Character*>	_CurrentDefenseFormation;
};