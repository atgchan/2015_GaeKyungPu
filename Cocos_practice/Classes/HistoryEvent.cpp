#include "pch.h"
#include "HistoryEvent.h"


HistoryEvent::HistoryEvent()
{
}


HistoryEvent::~HistoryEvent()
{
}

void HistoryEvent::Run()
{

}

bool HistoryEvent::IsDone()
{
	return false;
}

void HistoryEvent::setDone(bool isDone)
{
	_Done = isDone; 
}


