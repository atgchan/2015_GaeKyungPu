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
	void				setDone(bool isDone);

protected:
	bool				_IsDone = false;
};


