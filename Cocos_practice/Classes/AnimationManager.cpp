#include "pch.h"
#include "AnimationManager.h"


AnimationManager::AnimationManager()
{
}


AnimationManager::~AnimationManager()
{
}

std::shared_ptr<AnimationManager*> AnimationManager::getInsatnce()
{
	if (_Instance.get() == nullptr)
	{
		std::shared_ptr<AnimationManager*>	tempP(new AnimationManager(), Destruct);
		_Instance = tempP;
	}

	return _Instance;
}