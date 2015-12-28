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
	int							_AttackerPower = 0;
	int							_DefenderPower = 0;
	int							_CurrentX; ///# 멤버 초기화를 쓰려면 다 쓸 것~ 어떤거는 하고 어떤거는 초기화 안하면 나중에 버그로 돌아옴
	int							_CurrentY;
	bool						_FirstTime = true;
	void						PlaySwordSound();
};

