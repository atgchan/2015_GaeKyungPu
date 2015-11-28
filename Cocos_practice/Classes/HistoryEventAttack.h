#pragma once
#include "definition.h"
#include "HistoryEvent.h"

class Character;

class HistoryEventAttack : public HistoryEvent
{
public:
	HistoryEventAttack();
	~HistoryEventAttack();

	static std::shared_ptr<HistoryEventAttack> HistoryEventAttack::Create(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender); 

	void	Run();
	bool	IsDone();

private:
	std::shared_ptr<Character>	_Attacker;
	std::shared_ptr<Character>	_Defender;
};

