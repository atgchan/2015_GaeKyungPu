#pragma once
#include "definition.h"

class HistoryEvent;

class EventManager
{
public:
	static EventManager* getInstance();

	bool	ThereIsMoreHistory();
	void	AddHistory(std::shared_ptr<HistoryEvent> historyEvent); 
	
	///# �� �κ� Ȯ�������� �����, �̽��� ����� ���� ���Ŀ� ó�� �ٶ�.

	///# �����丮�̺�Ʈ�� ���������� shared_ptr���·� ���� �ִµ�, �� �׷��� �ϴ� ������ �ִ���?
	///# shared_ptr�� ������ �ٸ� RAW�����͵�� ���� ���� �����ϸ� �ݵ�� �Ǽ��ϴ� ��찡 ���´�.
	///# ��, ������ RAW������ ���� �� ��� �Ѵ�. (���� ���α׷� ���� ���־ delete�� �� ���� �����ʹ� ����)
	///# �߰��� shared_ptr�� ���� �Ǹ� �� ��� Ŭ����(HistoryEvent)�� �Ҹ��ڿ� �극��ũ ����Ʈ�� ��� ����� �Ҹ�Ǵ��� Ȯ���ϱ� �ٶ���. �װ� �ȵǸ� �� ������ ���� ������?

	void	ScheduleCallback();
	
	~EventManager();
private:
	EventManager();

	static void	Destruct();
	static EventManager* _Instance;

	unsigned	_HistoryCount = 0;

	//����ϰ��� �ϴ� �׼��� ��� ť
	
	std::list<std::shared_ptr<HistoryEvent>>					*_HistoryQueue;
	std::list<std::shared_ptr<HistoryEvent>>::iterator			_IteratorHistory;
};