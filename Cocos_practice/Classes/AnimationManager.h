#pragma once
#include "definition.h"

class HistoryEvent;

class AnimationManager
{
public:
	static std::shared_ptr<AnimationManager*>	getInsatnce();

	


private:
	AnimationManager();
	~AnimationManager();

	static	void								Destruct();

	static std::shared_ptr<AnimationManager*>	_Instance;
	
	//����ϰ��� �ϴ� �׼��� ��� ť
	std::queue<HistoryEvent>			_HistoryQueue;

};