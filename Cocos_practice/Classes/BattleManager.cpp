#include "pch.h"
#include "BattleManager.h"
#include "GameSceneManager.h"
#include "DiceDice.h"
#include "EventManager.h"
#include "HistoryEventAttack.h"
#include "HistoryEventKillCharacter.h"
#include "DiceDice.h"

void BattleManager::BattleBetween(Character* attacker, Character* defender)
{
	//�̰͵� ���� �����غ���

	SetAttackFormation(attacker);
	SetDefenseFormation(defender);

	int flankBonus = std::abs(std::abs((attacker->getCurrentDirection() - defender->getCurrentDirection())) - 3);
	
	attacker->setAttackPower(flankBonus + attacker->getAttackPower());
	defender->RotateToDirection(static_cast<DirectionKind>((attacker->getCurrentDirection() + 3) % MAX_DIRECTION)); ///# C++ ĳ������ ���ų� enum�� Ÿ���� �ְų�..

	PlayerInfo playerAttacker = attacker->GetOwnerPlayer();
	PlayerInfo playerDefender = defender->GetOwnerPlayer();

	while (_CurrentAttackFormation.size() && _CurrentDefenseFormation.size())
	{
		GiveForestBonus(_CurrentAttackFormation.front());
		GiveForestBonus(_CurrentDefenseFormation.back());

		std::list<Character*> *winner = nullptr;
		std::list<Character*> *loser = nullptr;

		if (IsAttackerWin(_CurrentAttackFormation.front(), _CurrentDefenseFormation.front()))
		{
			winner = &_CurrentAttackFormation;
			loser = &_CurrentDefenseFormation;
			EventManager::getInstance()->AddHistory(HistoryEventAttack::Create(_CurrentAttackFormation.front(), _CurrentDefenseFormation.front()));
		}
		else
		{
			winner = &_CurrentDefenseFormation;
			loser = &_CurrentAttackFormation;
			EventManager::getInstance()->AddHistory(HistoryEventAttack::Create(_CurrentAttackFormation.front(), _CurrentDefenseFormation.front()));
			EventManager::getInstance()->AddHistory(HistoryEventAttack::Create(_CurrentDefenseFormation.front(), _CurrentAttackFormation.front()));
		}
		
		bool firstTime = true;

		if (firstTime)
			attacker->setAttackPower(2);

		DirectionKind tempDirection = DIRECTION_ERR;
		DirectionKind prevDirection = loser->front()->getCurrentDirection();
		GM->KillCharacter(loser->front(),true);

		auto iter = loser->begin();
		++iter;
		
		for (; iter != loser->end(); ++iter)
		{
			(*iter)->MovoToTile((*iter)->getCurrentTile()->getNearTile((*iter)->getCurrentDirection()));
			tempDirection = (*iter)->getCurrentDirection();
			(*iter)->RotateToDirection(prevDirection);
			prevDirection = tempDirection;

			if (loser == &_CurrentDefenseFormation)
				break;
		}
		loser->pop_front();
	}

	std::list<Character*> finalWinnerForm = (_CurrentAttackFormation.size()) ? _CurrentAttackFormation : _CurrentDefenseFormation;
	PlayerInfo finalWinnerPlayer = finalWinnerForm.front()->GetOwnerPlayer();

	if (finalWinnerPlayer == playerAttacker)
	{
		Character* pIter = nullptr;
		Character*characterToMove = finalWinnerForm.front();

		characterToMove->MovoToTile(characterToMove->getCurrentTile()->getNearTile(characterToMove->getCurrentDirection()));

		DirectionKind tempDirection = DIRECTION_ERR, prevDirection = characterToMove->getCurrentDirection();
		for (auto iter = ++(finalWinnerForm.begin()); iter != finalWinnerForm.end(); ++iter)
		{
			pIter = *iter;
			pIter->MovoToTile(pIter->getCurrentTile()->getNearTile(pIter->getCurrentDirection()));
			tempDirection = pIter->getCurrentDirection();
			pIter->RotateToDirection(prevDirection);
			prevDirection = tempDirection;
		}
	}
}

bool BattleManager::IsAttackerWin(Character* attacker, Character* defender)
{
	while (true)
	{
		int attackerDice = DiceDice::getInstance()->RollDiceBetween(1, attacker->_AttackPower);
		int defenderDice = DiceDice::getInstance()->RollDiceBetween(1, defender->_AttackPower);

		if (attackerDice == defenderDice)
			continue;
		return (attackerDice > defenderDice) ? true : false;
	}
}

void BattleManager::SetAttackFormation(Character* attacker)
{
	std::list<Character*> tempList;
	_CurrentAttackFormation.clear();
	SearchGraphAndOverwriteAttackFormation(tempList, attacker, 1,0);
}

void BattleManager::SetDefenseFormation(Character* defender)
{
	_CurrentDefenseFormation.clear();
	_CurrentDefenseFormation.push_back(defender);

	for (int i = DIRECTION_DOWN_LEFT; i < MAX_DIRECTION; ++i)
	{
		Character* nearby = defender->GetNearCharacter((DirectionKind)i);
		
			if (nearby != nullptr && IsCharFacingMe(defender, nearby) && nearby->GetOwnerPlayer() == defender->GetOwnerPlayer())
				_CurrentDefenseFormation.push_back(nearby);

		
	}
}

///# std::find ���� �����̸� �Ǵµ�.. �׷��� �̷��� ���� �Լ��� ���� �����ʿ䵵 ����?
bool isHave(std::list<Character*> *checkedNode, Character* node)
{
	for (auto iter : *checkedNode)
	{
		if (iter == node)
			return true;
	}
	return false;
}

int BattleManager::SearchGraphAndOverwriteAttackFormation(std::list<Character*> checkedNode, Character* currentNode, int currentDepth, int maxDepth)
{
	checkedNode.push_back(currentNode);

	if (maxDepth <= currentDepth)
	{
		this->_CurrentAttackFormation = checkedNode;
		maxDepth = currentDepth;
	}

	//���� �Ʒ����� �ݽð�������� ��� ������ ��ȸ
	for (int i = DIRECTION_DOWN_LEFT; i < MAX_DIRECTION; ++i)
	{
		//i�������� ������ ĳ����
		Character* compareNode = currentNode->GetNearCharacter(static_cast<DirectionKind>(i));

		if (compareNode != nullptr)
			//�ش� ĳ���Ͱ� �ڽ��� �ٶ󺸰� ������
			if (compareNode->GetNearCharacter(compareNode->getCurrentDirection()) == currentNode && compareNode->GetOwnerPlayer() == currentNode->GetOwnerPlayer())
				//�̹� Ž���ߴ� node�� �ƴϸ�
				if (!isHave(&checkedNode, compareNode))
					maxDepth = SearchGraphAndOverwriteAttackFormation(checkedNode, compareNode, currentDepth + 1, maxDepth);
	}

	return maxDepth;
}

void BattleManager::GiveForestBonus(Character* target)
{
	if (target->getCurrentTile()->getTypeOfTile() == TILE_FOREST)
		target->setAttackPower(target->getAttackPower() + 1);
}

bool BattleManager::IsCharFacingMe(Character* me, Character* other)
{
	if (other->GetNearCharacter(other->getCurrentDirection()) == me)
		return true;
	return false;
}