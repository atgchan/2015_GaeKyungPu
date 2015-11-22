#pragma once
#include "definition.h"

class HistoryEvent;

class EventManager
{
public:
	static EventManager* getInstance();

	bool	ThereIsMoreHistory();
	void	PlayHistory();
	void	AddHistory(std::shared_ptr<HistoryEvent> historyEvent);
	Node*	getNode(){ return _NodeForPlayingEvent; };
	void	ScheduleCallback();

private:
	EventManager();
	~EventManager();

	static void	Destruct();
	static EventManager* _Instance;

	unsigned	_HistoryCount = 0;
	Node*		_NodeForPlayingEvent = nullptr;

	//기록하고자 하는 액션을 담는 큐
	std::list<std::shared_ptr<HistoryEvent>>					*_HistoryQueue;
	std::list<std::shared_ptr<HistoryEvent>>::iterator			_IteratorHistory;
};

