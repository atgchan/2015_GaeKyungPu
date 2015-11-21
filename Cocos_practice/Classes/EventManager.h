#pragma once
#include "definition.h"

class HistoryEvent;

/*
class Character;

typedef struct HistoryEvent{
	EventType									_EventType;
} HistoryEvent;

typedef struct BattleEvent :HistoryEvent{
	EventType									_EventType = HISTORY_EVENT_BATTLE;
	std::shared_ptr<Character*>					winner = nullptr;
	std::shared_ptr<Character*>					loser =	nullptr;
} BattleEvent;
*/

class EventManager
{
public:
	static EventManager* getInstance();
	bool										ThereIsMoreHistory();
	void										PlayHistory();
	void										AddHistory(std::shared_ptr<HistoryEvent> historyEvent);
	Node*										getNode(){ return _NodeForPlayingEvent; };
	void										ScheduleCallback();
private:
	EventManager();
	~EventManager();

	static	void								Destruct();

	static EventManager*					_Instance;

	//기록하고자 하는 액션을 담는 큐
	std::list<std::shared_ptr<HistoryEvent>>					*_HistoryQueue;
	
	std::list<std::shared_ptr<HistoryEvent>>::iterator			_IteratorHistory;
	unsigned													_HistoryCount = 0;

	Node*														_NodeForPlayingEvent = nullptr;

};

