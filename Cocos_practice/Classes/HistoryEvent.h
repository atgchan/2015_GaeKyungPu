#pragma once
#include "definition.h"

//구조체 용도로 사용한다.
class HistoryEvent
{
public:
	HistoryEvent();
	virtual ~HistoryEvent();
	virtual void		Run();
	virtual bool		IsDone();
	bool				setDone(bool isDone){ _Done = isDone; }
protected:
	bool				_Done = false;
};


