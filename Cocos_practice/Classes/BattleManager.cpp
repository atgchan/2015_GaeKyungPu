#include "pch.h"
#include "BattleManager.h"
#include "GameSceneManager.h"
#include "DiceDice.h"
#include "EventManager.h"
#include "HistoryEventAttack.h"
#include "HistoryEventKillCharacter.h"
#include "DiceDice.h"
#include "HistoryEventDice.h"
#include "HistoryEventRotateCharacter.h"

void BattleManager::BattleBetween(Character* attacker, Character* defender)
{
	SetAttackFormation(attacker);
	SetDefenseFormation(defender);

	PlayerInfo playerAttacker = attacker->GetOwnerPlayer();
	PlayerInfo playerDefender = defender->GetOwnerPlayer();
	bool bFirst = true;
	while (_CurrentAttackFormation.size() && _CurrentDefenseFormation.size())
	{
		std::list<Character*> *winner = nullptr;
		std::list<Character*> *loser = nullptr;

			_CurrentAttackFormation.front()->CalculateAttackPower();
			_CurrentDefenseFormation.front()->CalculateAttackPower();
		
		if (IsAttackerWin(_CurrentAttackFormation.front(), _CurrentDefenseFormation.front()))
		{
			winner = &_CurrentAttackFormation;
			loser = &_CurrentDefenseFormation;
			EventManager::getInstance()->AddHistory(HistoryEventRotateCharacter::Create(loser->front(), static_cast<DirectionKind>((attacker->getCurrentDirection() + 3) % DIRECTION_MAX)));
			EventManager::getInstance()->AddHistory(HistoryEventAttack::Create(_CurrentAttackFormation.front(), _CurrentDefenseFormation.front()));
			loser->front()->RotateToDirection(static_cast<DirectionKind>((attacker->getCurrentDirection() + 3) % DIRECTION_MAX), false);
		}
		else
		{
			winner = &_CurrentDefenseFormation;
			loser = &_CurrentAttackFormation;

			EventManager::getInstance()->AddHistory(HistoryEventRotateCharacter::Create(winner->front(), static_cast<DirectionKind>((attacker->getCurrentDirection() + 3) % DIRECTION_MAX)));
			EventManager::getInstance()->AddHistory(HistoryEventAttack::Create(_CurrentAttackFormation.front(), _CurrentDefenseFormation.front()));
			EventManager::getInstance()->AddHistory(HistoryEventAttack::Create(_CurrentDefenseFormation.front(), _CurrentAttackFormation.front()));
			winner->front()->RotateToDirection(static_cast<DirectionKind>((attacker->getCurrentDirection() + 3) % DIRECTION_MAX), false);
		}
		
		DirectionKind tempDirection = DIRECTION_ERR;
		DirectionKind prevDirection = loser->front()->getCurrentDirection();
		GM->KillCharacter(loser->front(),true);
		auto iter = loser->begin();
		++iter;
		
		for (; iter != loser->end(); ++iter)
		{
			(*iter)->MoveToTile((*iter)->getCurrentTile()->getNearTile((*iter)->getCurrentDirection()));
			tempDirection = (*iter)->getCurrentDirection();
			(*iter)->RotateToDirection(prevDirection,false);
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

		characterToMove->MoveToTile(characterToMove->getCurrentTile()->getNearTile(characterToMove->getCurrentDirection()));

		DirectionKind tempDirection = DIRECTION_ERR, prevDirection = characterToMove->getCurrentDirection();
		for (auto iter = ++(finalWinnerForm.begin()); iter != finalWinnerForm.end(); ++iter)
		{
			pIter = *iter;
			pIter->MoveToTile(pIter->getCurrentTile()->getNearTile(pIter->getCurrentDirection()));
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
		EventManager::getInstance()->AddHistory(HistoryEventDice::Create(attacker, attackerDice));
		EventManager::getInstance()->AddHistory(HistoryEventDice::Create(defender, defenderDice));
		return (attackerDice > defenderDice) ? true : false;
		//return false;
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

	for (int i = DIRECTION_DOWN_LEFT; i < DIRECTION_MAX; ++i)
	{
		Character* nearby = defender->GetNearCharacter((DirectionKind)i);
		if (nearby != nullptr && IsCharFacingMe(defender, nearby) && nearby->GetOwnerPlayer() == defender->GetOwnerPlayer())
			_CurrentDefenseFormation.push_back(nearby);
	}
}

int BattleManager::SearchGraphAndOverwriteAttackFormation(std::list<Character*> checkedNodes, Character* currentNode, int currentDepth, int maxDepth)
{
	checkedNodes.push_back(currentNode);

	if (maxDepth <= currentDepth)
	{
		this->_CurrentAttackFormation = checkedNodes;
		maxDepth = currentDepth;
	}

	//왼쪽 아래부터 반시계방향으로 모든 방향을 순회
	for (int i = DIRECTION_DOWN_LEFT; i < DIRECTION_MAX; ++i)
	{
		//i방향으로 인접한 캐릭터
		Character* compareNode = currentNode->GetNearCharacter(static_cast<DirectionKind>(i));

		if (compareNode != nullptr)
			//해당 캐릭터가 자신을 바라보고 있으면
			if (compareNode->GetNearCharacter(compareNode->getCurrentDirection()) == currentNode && compareNode->GetOwnerPlayer() == currentNode->GetOwnerPlayer())
				//이미 탐색했던 node가 아니면
				if (std::find(checkedNodes.begin(),checkedNodes.end(),compareNode) == checkedNodes.end())
					maxDepth = SearchGraphAndOverwriteAttackFormation(checkedNodes, compareNode, currentDepth + 1, maxDepth);
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