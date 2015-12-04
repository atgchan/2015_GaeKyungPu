#pragma once
#include "HistoryEvent.h"
class HistoryEventEmpty :
	public HistoryEvent
{
public:
	HistoryEventEmpty();
	~HistoryEventEmpty();
	bool	IsDone();
};

