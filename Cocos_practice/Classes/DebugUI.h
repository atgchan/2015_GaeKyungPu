#pragma once
#include "definition.h"

class DebugUI : public PopLayer
{
public:
	virtual bool init();
private:
	bool	isActivated;
};