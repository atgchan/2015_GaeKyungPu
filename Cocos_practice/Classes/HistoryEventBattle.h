#pragma once
#include "definition.h"
#include "HistoryEvent.h"

class Character;

class HistoryEventBattle : public HistoryEvent
{
public:
	HistoryEventBattle();
	HistoryEventBattle(std::shared_ptr<Character*>	winner, std::shared_ptr<Character*>	loser); ///# shared_ptr의 템플릿 인자로 왜 포인터가??
	~HistoryEventBattle();

	void	Run();
	bool	IsDone();

private:
	std::shared_ptr<Character*>	_Winner;
	std::shared_ptr<Character*>	_Loser;
};

