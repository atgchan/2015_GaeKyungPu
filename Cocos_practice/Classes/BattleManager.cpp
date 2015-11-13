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
		loser->pop_front();
		
		for (auto iter : *loser)
		{
			GM->MoveCharacter(iter,iter->getCurrentTile()->GetNearTile(iter->getCurrentDirection()));
			iter->setCurrentDirection((iter - 1)->getCurrentDirection);
			//in progress
		}
		
	}
}

Winner BattleManager::FightBetween(Character* attacker, Character* defender)
{
	return WINNER_ATTACKER;
}

void BattleManager::SetAttackFormation(Character* attacker)
{
	std::list<Character*> tempList;
	SearchGraphAndOverwriteAttackFormation(tempList, attacker, 1);

}

void BattleManager::SetDefenseFormation(Character* defender)
{
	Character* nearby = nullptr;
	for (int i = DIRECTION_DOWN_LEFT; i <= DIRECTION_UP_LEFT; i++)
	{
		nearby = defender->GetNearCharacter((DirectionKind)i);
		if (nearby != nullptr && isCharFacingMe(defender, nearby))
		{
			_CurrentDefenseFormation.push_back(nearby);
		}
	}
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

	//���� �Ʒ����� �ݽð�������� ��� ������ ��ȸ
	for (int i = DIRECTION_DOWN_LEFT; i <= DIRECTION_UP_LEFT; ++i)
	{
		//i�������� ������ ĳ����
		auto compareNode = currentNode->GetNearCharacter(static_cast<DirectionKind>(i));

		
		if (compareNode != nullptr)
			//�ش� ĳ���Ͱ� �ڽ��� �ٶ󺸰� ������
			if (compareNode->GetNearCharacter(compareNode->getCurrentDirection()) == currentNode)
				//�̹� Ž���ߴ� node�� �ƴϸ�
				if (!isHave(&checkedNode, compareNode))
					SearchGraphAndOverwriteAttackFormation(checkedNode, compareNode, currentDepth + 1);
	}
}

bool BattleManager::isCharFacingMe(Character* me, Character* other)
{
	if (other->GetNearCharacter(other->getCurrentDirection()) == me)
	{
		return true;
	}
	else
		return false;
}
