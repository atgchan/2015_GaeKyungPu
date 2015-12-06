#include "pch.h"
#include "EventManager.h"
#include "HistoryEvent.h"
#include "GameSceneManager.h"
#include "HistoryEventEmpty.h"

EventManager* EventManager::_Instance = nullptr;

EventManager::EventManager()
{
	_HistoryQueue = new std::list<std::shared_ptr<HistoryEvent>>;
	_NodeForPlayingEvent = Node::create();
	GM->AddChild(_NodeForPlayingEvent);
	_HistoryQueue->push_back(std::make_shared<HistoryEventEmpty>());
	_IteratorHistory = _HistoryQueue->begin();
}

EventManager::~EventManager()
{
	delete _HistoryQueue;
}

void EventManager::AddHistory(std::shared_ptr<HistoryEvent> historyEvent)
{
	_HistoryQueue->push_back(historyEvent);
}

void EventManager::ScheduleCallback()
{
	/*
	������ �������� �����Ѵ�.
	�������� ���������� ������ ������ �ȴ�.
	ù��° ���� �������� ��� ������ �����Ƿ� �ٷ� ������ �ȴ�.
	*/
	if (_HistoryQueue->back()->IsDone())
	{
		while (_HistoryQueue->size() != 1)
		{
			_HistoryQueue->pop_back();
		}
		_IteratorHistory = _HistoryQueue->begin();
		GM->setInputMode(true);
	}
	else
	{
		static bool once = true;
		GM->setInputMode(false);

		if (_IteratorHistory->get()->IsDone())
		{
			++_IteratorHistory;
			_IteratorHistory->get()->Run();
			++_HistoryCount;
		}
	}
}

EventManager* EventManager::getInstance()
{
	if (_Instance == nullptr)
		_Instance = new EventManager();
	return _Instance;
}

bool EventManager::ThereIsMoreHistory()
{
	if (this->_HistoryQueue->size() == 0)
		return false;
	return true;
}