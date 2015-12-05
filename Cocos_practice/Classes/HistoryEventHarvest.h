#pragma once
#include "HistoryEvent.h"

class Character;
class HistoryEventHarvest :
	public HistoryEvent
{
public:
	HistoryEventHarvest();
	~HistoryEventHarvest();
	static std::shared_ptr<HistoryEventHarvest> Create(Character* characterHarvest);

	void	Run();

private:
	Character*		_CharacterHarvest = nullptr;
};