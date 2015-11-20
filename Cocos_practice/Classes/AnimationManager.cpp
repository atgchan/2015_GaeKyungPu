#include "pch.h"
#include "AnimationManager.h"
#include "HistoryEvent.h"
#include "GameSceneManager.h"

AnimationManager* AnimationManager::_Instance = nullptr;

AnimationManager::AnimationManager()
{
	_HistoryQueue = new std::list<std::shared_ptr<HistoryEvent>>;
	_NodeForPlayingEvent = Node::create();
	GM->AddChild(_NodeForPlayingEvent);

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
		if (_HistoryCount == 0)
			_IteratorHistory = _HistoryQueue->begin();
		else
			++_IteratorHistory;
		GM->setInputMode(false);
		++_HistoryCount;
		_IteratorHistory->get()->Run();
		//_HistoryQueue->back().get()->Run();
	}
}

void AnimationManager::AddHistory(std::shared_ptr<HistoryEvent> historyEvent)
{
	_HistoryQueue->push_back(historyEvent);
}


void AnimationManager::ScheduleCallback()
{
	/*
	������ �������� �����Ѵ�.
	�������� ���������� ������ ������ �ȴ�.
	ù��° ���� �������� ��� ������ �����Ƿ� �ٷ� ������ �ȴ�.
	*/
	if (_HistoryQueue->size() == _HistoryCount)
		GM->setInputMode(true);
	else
	{
		static bool once = true;
		GM->setInputMode(false);

		if (_HistoryCount == 0 && once == true)
		{
			_IteratorHistory = _HistoryQueue->begin();
			once = false;
			_IteratorHistory->get()->Run();
			++_HistoryCount;
		}
		else if (_IteratorHistory->get()->IsDone())
		{
			++_IteratorHistory;
			_IteratorHistory->get()->Run();
			++_HistoryCount;
		}
	}
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

