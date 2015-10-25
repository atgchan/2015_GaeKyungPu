USING_NS_CC;

class TileMap : public Layer
{
private:
	Self_Tile* _TileSet[9][8];
	static TileKind _MapData[9][8];
	
	TileMap();
	TileMap(const TileMap& other);
	static TileMap inst;

public:
	static TileMap* getInstance(){ return &inst; }
	bool createMap();
};