#pragma once
#include "definition.h"

class HistoryEvent;

class EventManager
{
public:
	static EventManager* getInstance();

	bool	ThereIsMoreHistory();
	void	AddHistory(std::shared_ptr<HistoryEvent> historyEvent); 
	
	///# 이 부분 확인했으면 지우고, 이슈로 만들어 놓고 추후에 처리 바람.

	///# 히스토리이벤트를 전반적으로 shared_ptr형태로 쓰고 있는데, 꼭 그래야 하는 이유가 있는지?
	///# shared_ptr을 쓰려면 다른 RAW포인터들과 섞어 쓰기 시작하면 반드시 실수하는 경우가 나온다.
	///# 즉, 쓰려면 RAW포인터 없이 다 써야 한다. (물론 프로그램 내내 떠있어서 delete될 일 없는 포인터는 예외)
	///# 추가로 shared_ptr을 쓰게 되면 꼭 대상 클래스(HistoryEvent)의 소멸자에 브레이크 포인트를 찍고 제대로 소멸되는지 확인하기 바란다. 그게 안되면 쓸 이유가 없지 않은가?

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