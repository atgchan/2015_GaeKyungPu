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
	bool						_IsDone = false; ///# 부모 클래스에도 같은 이름의 멤버가 있다.. 일종의 덮어쓰기인데.. 나중에 버그의 온상이 됨.
};

