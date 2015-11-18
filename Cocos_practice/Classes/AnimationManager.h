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
	
	//기록하고자 하는 액션을 담는 큐
	std::queue<HistoryEvent>			_HistoryQueue;

};