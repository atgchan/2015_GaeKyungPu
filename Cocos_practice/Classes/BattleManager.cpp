#include "pch.h"
#include "BattleManager.h"
#include "GameSceneManager.h"
#include "DiceDice.h"
#include "EventManager.h"
#include "HistoryEventAttack.h"
#include "DiceDice.h"

void BattleManager::BattleBetween(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender)
{
	//�̰͵� ���� �����غ���
	//GM->getPlayerDataByPlayerInfo(attacker->GetOwnerPlayer())->AddFood(defender->getCurrentTile()->getFoodToConsume() * -1);

	SetAttackFormation(attacker);
	SetDefenseFormation(defender);
	bool firstTime = true;

	int flankBonus = std::abs(std::abs((attacker->getCurrentDirection() - defender->getCurrentDirection())) - 3);
	
	attacker->setAttackPower(flankBonus + attacker->getAttackPower());
	defender->RotateToDirection((DirectionKind)((attacker->getCurrentDirection() + 3) % 6));

	PlayerInfo playerAttacker = attacker->GetOwnerPlayer();
	PlayerInfo playerDefender = defender->GetOwnerPlayer();

	while (_CurrentAttackFormation.size() && _CurrentDefenseFormation.size())
	{
		GiveForestBonus(_CurrentAttackFormation.front());
		GiveForestBonus(_CurrentDefenseFormation.back());

		std::list<std::shared_ptr<Character>> *winner = nullptr;
		std::list<std::shared_ptr<Character>> *loser = nullptr;

		if (IsAttackerWin(_CurrentAttackFormation.front(), _CurrentDefenseFormation.front()))
			winner = &_CurrentAttackFormation;
		else
			winner = &_CurrentDefenseFormation;

		EventManager::getInstance()->AddHistory(HistoryEventAttack::Create(_CurrentAttackFormation.front(), _CurrentDefenseFormation.front()));

		loser = (winner == &_CurrentAttackFormation) ? &_CurrentDefenseFormation : &_CurrentAttackFormation;
		
		if (firstTime)
			attacker->setAttackPower(2);
		std::shared_ptr<Character> pIter = nullptr;
		DirectionKind tempDirection = DIRECTION_ERR;
		DirectionKind prevDirection = loser->front()->getCurrentDirection();
		GM->KillCharacter(loser->front());

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

	std::list<std::shared_ptr<Character>> finalWinnerForm = (_CurrentAttackFormation.size()) ? _CurrentAttackFormation : _CurrentDefenseFormation;
	PlayerInfo finalWinnerPlayer = finalWinnerForm.front()->GetOwnerPlayer();

	if (finalWinnerPlayer == playerAttacker)
	{
		std::shared_ptr<Character> pIter = nullptr;
		std::shared_ptr<Character>characterToMove = finalWinnerForm.front();

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
	//AnimationManager::getInstance()->PlayHistory();
}

bool BattleManager::IsAttackerWin(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender)
{
	int attackerDice = 0;
	int defenderDice = 0;
	
	while (true)
	{
		attackerDice = DiceDice::getInstance()->RollDiceBetween(1, attacker->_AttackPower);
		defenderDice = DiceDice::getInstance()->RollDiceBetween(1, defender->_AttackPower);

		if (attackerDice == defenderDice)
			continue;
		return (attackerDice > defenderDice) ? true : false;
	}
}

void BattleManager::SetAttackFormation(std::shared_ptr<Character> attacker)
{
	std::list<std::shared_ptr<Character>> tempList;
	int max_depth = 0;
	_CurrentAttackFormation.clear();
	SearchGraphAndOverwriteAttackFormation(tempList, attacker, 1,0);

}

void BattleManager::SetDefenseFormation(std::shared_ptr<Character> defender)
{
	std::shared_ptr<Character> nearby = nullptr; ///# �̰� �ۿ� ����Ǿ� ���� ������ ����.
	_CurrentDefenseFormation.clear();

	_CurrentDefenseFormation.push_back(defender);
	for (int i = DIRECTION_DOWN_LEFT; i <= DIRECTION_UP_LEFT; i++)
	{
		nearby = defender->GetNearCharacter((DirectionKind)i);
		///# shared_ptr�� isnull() �����ŷ� �� üũ.
		if (nearby != nullptr && IsCharFacingMe(defender, nearby) && nearby->GetOwnerPlayer() == defender->GetOwnerPlayer())
		{
			_CurrentDefenseFormation.push_back(nearby);
		}
	}
}

bool isHave(std::list<std::shared_ptr<Character>> *checkedNode, std::shared_ptr<Character> node)
{
	for (auto iter : *checkedNode)
	{
		if (iter == node)
			return true;
	}
	return false;
}
int BattleManager::SearchGraphAndOverwriteAttackFormation(std::list<std::shared_ptr<Character>> checkedNode, std::shared_ptr<Character> currentNode, int currentDepth, int maxDepth)
{
	
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
		std::shared_ptr<Character> compareNode = currentNode->GetNearCharacter(static_cast<DirectionKind>(i));

		
		if (compareNode != nullptr)
			//�ش� ĳ���Ͱ� �ڽ��� �ٶ󺸰� ������
			if (compareNode->GetNearCharacter(compareNode->getCurrentDirection()) == currentNode && compareNode->GetOwnerPlayer() == currentNode->GetOwnerPlayer())
				//�̹� Ž���ߴ� node�� �ƴϸ�
				if (!isHave(&checkedNode, compareNode))
					maxDepth = SearchGraphAndOverwriteAttackFormation(checkedNode, compareNode, currentDepth + 1, maxDepth);
	}

	return maxDepth;
}

void BattleManager::GiveForestBonus(std::shared_ptr<Character> target)
{
	if (target->getCurrentTile()->getTypeOfTile() == TILE_FOREST)
		target->setAttackPower(target->getAttackPower() + 1);
}

bool BattleManager::IsCharFacingMe(std::shared_ptr<Character> me, std::shared_ptr<Character> other)
{
	if (other->GetNearCharacter(other->getCurrentDirection()) == me)
		return true;
	else
		return false;
		
}