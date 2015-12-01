#include "pch.h"
#include "HistoryEventKillCharacter.h"
#include "CharacterAnimation.h"
#include "Character.h"
#include "GameSceneManager.h"
#include "EventManager.h"
#include "SimpleAudioEngine.h"

HistoryEventKillCharacter::HistoryEventKillCharacter()
{
}

std::shared_ptr<HistoryEventKillCharacter> HistoryEventKillCharacter::Create(std::shared_ptr<Character> characterToKill)
{
	///# 마찬가지로 순환참조 유의
	std::shared_ptr<HistoryEventKillCharacter> newInst = std::make_shared<HistoryEventKillCharacter>();
	newInst->_CharacterToKill = characterToKill;

	return newInst;
}

HistoryEventKillCharacter::~HistoryEventKillCharacter()	
{
}

void HistoryEventKillCharacter::Run()
{	
	TileMap::getInstance()->removeChild(_CharacterToKill.get());
	_Done = true;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Hit_03.wav");
}

bool HistoryEventKillCharacter::IsDone()
{
	return true;
}
