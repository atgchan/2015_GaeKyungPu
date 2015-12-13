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

protected:
	void		SetDone(bool isDone);
	bool		_IsDone = false;

};