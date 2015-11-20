#pragma once
#include "definition.h"
#include "HistoryEvent.h"

class Character;
class HistoryEventBattle :
	public HistoryEvent
{
public:
	HistoryEventBattle();
	HistoryEventBattle(std::shared_ptr<Character*>	winner, std::shared_ptr<Character*>	loser);
	~HistoryEventBattle();
	void						Run();
	bool						IsDone();
private:
	std::shared_ptr<Character*>	_Winner;
	std::shared_ptr<Character*>	_Loser;
};

