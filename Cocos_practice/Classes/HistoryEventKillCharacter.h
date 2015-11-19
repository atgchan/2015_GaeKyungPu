#pragma once

#include "definition.h"
#include "HistoryEvent.h"

class Character;
class Self_Tile;

class HistoryEventKillCharacter :
	public HistoryEvent
{
public:
	HistoryEventKillCharacter();
	static std::shared_ptr<HistoryEventKillCharacter> Create(std::shared_ptr<Character> characterToKill);
	~HistoryEventKillCharacter();
	void							Run();
private:
	std::shared_ptr<Character>		_CharacterToKill = nullptr;
};



