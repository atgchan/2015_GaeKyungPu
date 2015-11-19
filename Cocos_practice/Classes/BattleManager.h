#pragma once
#include "definition.h"

class Character;

class BattleManager
{
public:
	BattleManager();
	~BattleManager();
	
	
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
	
	std::list<Character*>	GetCurrentAttackFormation(){ return _CurrentAttackFormation; }
	std::list<Character*>	GetCurrentDeffenseFormation(){ return _CurrentDefenseFormation; }

	bool	isCharFacingMe(Character* me, Character* other);
private:
	void SearchGraphAndOverwriteAttackFormation(std::list<Character*> checkedNode, Character* currentNode, int currentDepth, int maxDepth);
	std::list<Character*>	_CurrentAttackFormation;
	std::list<Character*>	_CurrentDefenseFormation;
};

