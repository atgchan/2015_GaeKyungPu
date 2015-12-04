#include "pch.h"
#include "EventManager.h"
#include "HistoryEvent.h"
#include "GameSceneManager.h"

EventManager* EventManager::_Instance = nullptr;

EventManager::EventManager()
{
	_HistoryQueue = new std::list<std::shared_ptr<HistoryEvent>>;
	_NodeForPlayingEvent = Node::create();
	GM->AddChild(_NodeForPlayingEvent);
	_HistoryQueue->push_back(std::make_shared<HistoryEvent>());
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
	*//*
	static std::list<std::shared_ptr<HistoryEvent>>::iterator cIter;
	cIter = _HistoryQueue->begin();
	std::advance(cIter, _HistoryCount);*/
	if (_HistoryQueue->back()->IsDone()/*_HistoryQueue->size() == _HistoryCount*/)
		GM->setInputMode(true);
	else
	{
		static bool once = true;
		GM->setInputMode(false);

		/*if (_HistoryCount == 0 && once == true)
		{
			_IteratorHistory = _HistoryQueue->begin();
			once = false;
			_IteratorHistory->get()->Run();
			//++_HistoryCount;
		}
		else*/ if (_IteratorHistory->get()->IsDone())
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
	{
		_Instance = new EventManager();
	}
	return _Instance;
}

bool EventManager::ThereIsMoreHistory()
{
	if (this->_HistoryQueue->size() == 0)
		return false;
	return true;
}