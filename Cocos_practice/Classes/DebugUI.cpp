#include "pch.h"
#include "PopLayer.h"
#include "DebugUI.h"

void DebugUI::init()
{
	isActivated = true;
	CCDirector::sharedDirector()->pause();
}
