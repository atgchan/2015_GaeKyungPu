#pragma once
#include "definition.h"

//����ü �뵵�� ����Ѵ�.
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


