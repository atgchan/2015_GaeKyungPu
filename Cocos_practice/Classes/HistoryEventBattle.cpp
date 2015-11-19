#include "pch.h"
#include "HistoryEventBattle.h"
#include "Character.h"
#include "CharacterAnimation.h"

HistoryEventBattle::HistoryEventBattle()
{
}


HistoryEventBattle::HistoryEventBattle(std::shared_ptr<Character*> winner, std::shared_ptr<Character*> loser)
{
	_Winner = winner;
	_Loser = loser;
}

HistoryEventBattle::~HistoryEventBattle()
{
}

void HistoryEventBattle::Run()
{

}


