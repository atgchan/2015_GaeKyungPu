#pragma once
#include "HistoryEvent.h"

class Character;

class HistoryEventRotateCharacter : public HistoryEvent
{
public:
	HistoryEventRotateCharacter();
	~HistoryEventRotateCharacter();
	static std::shared_ptr<HistoryEventRotateCharacter> Create(std::shared_ptr<Character> targetCharacter, DirectionKind targetDirection);

	void	Run();
	bool	IsDone();

private:
	std::shared_ptr<Character>		_CharacterToRotate = nullptr;
	DirectionKind	_DirectionToRotate = DIRECTION_ERR;
	bool			_IsDone = false;
};

