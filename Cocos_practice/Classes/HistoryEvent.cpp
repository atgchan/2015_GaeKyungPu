#include "pch.h"
#include "HistoryEvent.h"


HistoryEvent::HistoryEvent()
{
}


HistoryEvent::~HistoryEvent()
{
	///# �ݵ�� �Ҹ� �Ǵ��� Ȯ��
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


