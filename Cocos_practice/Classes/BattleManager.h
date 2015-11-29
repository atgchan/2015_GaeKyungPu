#pragma once
#include "definition.h"

class Character;

class BattleManager
{
public:
	
	void	BattleBetween(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender);
	/**
		@brief	���� �θ��� �ο��� ���̰� ���ڸ� ��ȯ�մϴ�.
	*/
	bool	IsAttackerWin(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender);

	/**
		@brief	attacker�� �������� �ϴ� ���� ������ �����մϴ�.
	*/
	void	SetAttackFormation(std::shared_ptr<Character> attacker);
	
	void	SetDefenseFormation(std::shared_ptr<Character> defender);
	
	bool	IsCharFacingMe(std::shared_ptr<Character> me, std::shared_ptr<Character> other);

private:
	int SearchGraphAndOverwriteAttackFormation(std::list<std::shared_ptr<Character>> checkedNode, std::shared_ptr<Character> currentNode, int currentDepth, int maxDepth);
	std::list<std::shared_ptr<Character>>	_CurrentAttackFormation;
	std::list<std::shared_ptr<Character>>	_CurrentDefenseFormation;
	void									GiveForestBonus(std::shared_ptr<Character>);
};

