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
	return _IsDone;
}

void HistoryEvent::SetDone(bool isDone)
{
	_IsDone = isDone; 
}