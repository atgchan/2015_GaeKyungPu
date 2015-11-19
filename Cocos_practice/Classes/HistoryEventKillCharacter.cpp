#include "pch.h"
#include "HistoryEventKillCharacter.h"
#include "CharacterAnimation.h"
#include "Character.h"
#include "GameSceneManager.h"
#include "AnimationManager.h"

HistoryEventKillCharacter::HistoryEventKillCharacter()
{
}


std::shared_ptr<HistoryEventKillCharacter> HistoryEventKillCharacter::Create(std::shared_ptr<Character> characterToKill)
{
	std::shared_ptr<HistoryEventKillCharacter> newInst = std::make_shared<HistoryEventKillCharacter>();
	newInst->_CharacterToKill = characterToKill;

	return newInst;
}

HistoryEventKillCharacter::~HistoryEventKillCharacter()
{
}

void HistoryEventKillCharacter::Run()
{	
	auto removeCall = CallFunc::create(CC_CALLBACK_0(TileMap::removeChild, TileMap::getInstance(), _CharacterToKill.get(), true));
	auto nextCall = CallFunc::create(CC_CALLBACK_0(AnimationManager::PlayHistory, AnimationManager::getInstance()));
	

	FiniteTimeAction* seq = Sequence::create(removeCall,nextCall, NULL);

	_CharacterToKill->runAction(seq);

}
