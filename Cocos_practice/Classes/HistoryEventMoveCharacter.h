#pragma once

#include "definition.h"
#include "HistoryEvent.h"

class Character;
class Self_Tile;

class HistoryEventMoveCharacter :
	public HistoryEvent
{
public:
	HistoryEventMoveCharacter();
	static std::shared_ptr<HistoryEventMoveCharacter> Create(std::shared_ptr<Character> characterToMove, std::shared_ptr<Self_Tile> TargetTile);
	~HistoryEventMoveCharacter();
	void							Run();
private:
	std::shared_ptr<Character>		_CharacterToMove = nullptr;
	std::shared_ptr<Self_Tile>		_TargetTile = nullptr;
};

