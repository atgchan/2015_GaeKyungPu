#pragma once
#include "HistoryEvent.h"

class Self_Tile;

class HistoryEventChangeTile :
	public HistoryEvent
{
public:
	HistoryEventChangeTile();
	~HistoryEventChangeTile();
	static std::shared_ptr<HistoryEventChangeTile> Create(Self_Tile* targetTile, TileKind targetType);
	void											Run();
private:
	Self_Tile*	_TargetTile = nullptr;
	TileKind	_TargetType = TILE_NULL;
};

