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
	static std::shared_ptr<HistoryEventKillCharacter> Create(Character* characterToKill, bool hitEffect = false);

	void	Run();

private:
	void		RemoveCharacterToKill();
	Character*	_CharacterToKill = nullptr;
	bool		_ShowHitEffect = false;
	Sprite*		_HitEffect = nullptr;
	ActionInterval* _ActionHitEffect = nullptr;
};