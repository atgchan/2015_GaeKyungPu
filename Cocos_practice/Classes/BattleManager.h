#pragma once
#include "definition.h"

class Character;

class BattleManager
{
public:
	BattleManager();
	~BattleManager();
	/**
		@brief	���� �θ��� �ο��� ���Դϴ�.
	*/
	void	BattleBetween(Character* attacker, Character* defender);

	/**
		@brief	attacker�� �������� �ϴ� ���� ������ �����մϴ�.
	*/
	void	SetAttackFormation(Character* attacker);
	
	void	SetDefenseFormation(Character* defender);
	std::list<Character*>	GetCurrentAttackFormation(){ return _CurrentAttackFormation; }
private:
	void SearchGraphAndOverwriteAttackFormation(std::list<Character*> checkedNode, Character* currentNode, int currentDepth);
	std::list<Character*>	_CurrentAttackFormation;
	std::list<Character*>	_CurrentDefenseFormation;
};