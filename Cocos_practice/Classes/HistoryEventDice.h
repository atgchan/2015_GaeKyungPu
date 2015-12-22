#pragma once
#include "HistoryEvent.h"

class Character;

class HistoryEventDice :
	public HistoryEvent
{
public:
	HistoryEventDice();
	~HistoryEventDice();
	static std::shared_ptr<HistoryEventDice> Create(Character* character, int num);
	void											Run();
private:
	Character*	_TargetCharacter = nullptr;
	int _Num; ///# 마찬가지로 초기화.
	Sprite* CreateDiceWithNumber();
};

