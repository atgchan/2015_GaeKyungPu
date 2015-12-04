#pragma once
#include "definition.h"

class Character;

class BattleManager
{
public:
	
	void	BattleBetween(Character* attacker, Character* defender);
	/**
		@brief	���� �θ��� �ο��� ���̰� ���ڸ� ��ȯ�մϴ�.
	*/
	bool	IsAttackerWin(Character* attacker, Character* defender);

	/**
		@brief	attacker�� �������� �ϴ� ���� ������ �����մϴ�.
	*/
	void	SetAttackFormation(Character* attacker);
	
	void	SetDefenseFormation(Character* defender);
	
	bool	IsCharFacingMe(Character* me, Character* other);

private:
	int SearchGraphAndOverwriteAttackFormation(std::list<Character*> checkedNode, Character* currentNode, int currentDepth, int maxDepth);
	std::list<Character*>	_CurrentAttackFormation;
	std::list<Character*>	_CurrentDefenseFormation;
	void									GiveForestBonus(Character*);
};

