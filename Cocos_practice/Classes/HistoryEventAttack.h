#pragma once
#include "definition.h"
#include "HistoryEvent.h"

class Character;

class HistoryEventAttack : public HistoryEvent
{
public:
	HistoryEventAttack();
	~HistoryEventAttack();

	static std::shared_ptr<HistoryEventAttack> HistoryEventAttack::Create(Character* attacker, Character* defender); 

	void	Run();

private:
	Character*	_Attacker;
	Character*	_Defender;
	int							_CurrentX;
	int							_CurrentY;
	bool						_FirstTime = true;
	void						PlaySwordSound();
	int							_AttackPowerToShow_attacker = 0;
	int							_AttackPowerToShow_defender = 0;
};

