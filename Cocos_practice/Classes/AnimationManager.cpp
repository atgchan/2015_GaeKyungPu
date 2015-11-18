#include "pch.h"
#include "AnimationManager.h"
#include "HistoryEvent.h"
#include "GameSceneManager.h"

AnimationManager* AnimationManager::_Instance = nullptr;

AnimationManager::AnimationManager()
{
	_HistoryQueue = new std::list<std::shared_ptr<HistoryEvent>>;
}


AnimationManager::~AnimationManager()
{
	delete(_HistoryQueue);
}


void AnimationManager::PlayHistory()
{

	if (_HistoryQueue->size() == _HistoryCount)
	{
		GM->setInputMode(true);
	}
	else
	{
		GM->setInputMode(false);
		_HistoryQueue->back().get()->Run();
		++_HistoryCount;
	}
}

void AnimationManager::AddHistory(std::shared_ptr<HistoryEvent> historyEvent)
{
	_HistoryQueue->push_back(historyEvent);
}


AnimationManager* AnimationManager::getInstance()
{
	if (_Instance == nullptr)
	{
		_Instance = new AnimationManager();
	}
	return _Instance;
}

bool AnimationManager::ThereIsMoreHistory()
{
	if (this->_HistoryQueue->size() == 0)
		return false;
	return true;
}
