#pragma once
#include "definition.h"

class Character;

class BattleManager
{
public:
	
	void	BattleBetween(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender);
	/**
		@brief	병사 두명을 싸움을 붙이고 승자를 반환합니다.
	*/
	bool	IsAttackerWin(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender);

	/**
		@brief	attacker를 기점으로 하는 공격 대형을 설정합니다.
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

