#include "pch.h"
#include "HistoryEvent.h"


HistoryEvent::HistoryEvent()
{
}


HistoryEvent::~HistoryEvent()
{
	///# 반드시 소멸 되는지 확인
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


