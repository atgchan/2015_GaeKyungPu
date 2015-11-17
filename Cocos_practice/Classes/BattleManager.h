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
		@brief	병사 두명을 싸움을 붙이고 승자를 반환합니다.
	*/
	bool	IsAttackerWin(Character* attacker, Character* defender);

	/**
		@brief	attacker를 기점으로 하는 공격 대형을 설정합니다.
	*/
	void	SetAttackFormation(Character* attacker);
	
	void	SetDefenseFormation(Character* defender);
	
	///# 지난 시간에도 이야기했듯이 컬렉션을 통째로 복사로 리턴하지 말 것.
	std::list<Character*>	GetCurrentAttackFormation(){ return _CurrentAttackFormation; }
	std::list<Character*>	GetCurrentDeffenseFormation(){ return _CurrentDefenseFormation; }

	bool	isCharFacingMe(Character* me, Character* other);
private:
	void SearchGraphAndOverwriteAttackFormation(std::list<Character*> checkedNode, Character* currentNode, int currentDepth, int maxDepth);
	std::list<Character*>	_CurrentAttackFormation;
	std::list<Character*>	_CurrentDefenseFormation;
};