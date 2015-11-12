#include "pch.h"
#include "BattleManager.h"
#include "GameSceneManager.h"

BattleManager::BattleManager()
{
}


BattleManager::~BattleManager()
{
}

void BattleManager::BattleBetween(Character* attacker, Character* defender)
{
	SetAttackFormation(attacker);
	SetDefenseFormation(defender);

	while (_CurrentAttackFormation.size() && _CurrentDefenseFormation.size())
	{
		std::list<Character*> *winner = nullptr, *loser = nullptr;
		winner = (FightBetween(_CurrentAttackFormation.front(), _CurrentDefenseFormation.front()) == WINNER_ATTACKER) ? &_CurrentAttackFormation : &_CurrentDefenseFormation;
		loser = (winner == &_CurrentAttackFormation) ? &_CurrentDefenseFormation : &_CurrentAttackFormation;
		winner->pop_front();
		
	}
}

void BattleManager::SetAttackFormation(Character* attacker)
{
	std::list<Character*> tempList;
	SearchGraphAndOverwriteAttackFormation(tempList, attacker, 1);

}

bool isHave(std::list<Character*> *checkedNode, Character* node)
{
	for (auto iter : *checkedNode)
	{
		if (iter == node)
			return true;
	}
	return false;
}
void BattleManager::SearchGraphAndOverwriteAttackFormation(std::list<Character*> checkedNode,Character* currentNode, int currentDepth)
{
	static int maxDepth = 0;
	
	checkedNode.push_back(currentNode);

	if (maxDepth <= currentDepth)
	{
		this->_CurrentAttackFormation = checkedNode;
		maxDepth = currentDepth;
	}

	//왼쪽 아래부터 반시계방향으로 모든 방향을 순회
	for (int i = DIRECTION_DOWN_LEFT; i <= DIRECTION_UP_LEFT; ++i)
	{
		//i방향으로 인접한 캐릭터
		auto compareNode = currentNode->GetNearCharacter(static_cast<DirectionKind>(i));

		
		if (compareNode != nullptr)
			//해당 캐릭터가 자신을 바라보고 있으면
			if (compareNode->GetNearCharacter(compareNode->getCurrentDirection()) == currentNode)
				//이미 탐색했던 node가 아니면
				if (!isHave(&checkedNode, compareNode))
					SearchGraphAndOverwriteAttackFormation(checkedNode, compareNode, currentDepth + 1);
	}
}
