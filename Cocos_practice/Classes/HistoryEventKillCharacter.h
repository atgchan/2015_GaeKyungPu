#pragma once

#include "definition.h"
#include "HistoryEvent.h"

class Character;
class Self_Tile;

class HistoryEventKillCharacter : public HistoryEvent
{
public:
	HistoryEventKillCharacter();
	~HistoryEventKillCharacter();
	static std::shared_ptr<HistoryEventKillCharacter> Create(Character* characterToKill);

	void	Run();

private:
	Character*		_CharacterToKill = nullptr;
};



