#pragma once

#include "definition.h"
#include "HistoryEvent.h"

class Character;
class Self_Tile;

class HistoryEventMoveCharacter : public HistoryEvent
{
public:
	HistoryEventMoveCharacter();
	~HistoryEventMoveCharacter();
	static std::shared_ptr<HistoryEventMoveCharacter> Create(std::shared_ptr<Character> characterToMove, Self_Tile* TargetTile);

	void	Run();
	bool	IsDone();

private:
	std::shared_ptr<Character>		_CharacterToMove = nullptr;
	Self_Tile*		_TargetTile = nullptr;
};



