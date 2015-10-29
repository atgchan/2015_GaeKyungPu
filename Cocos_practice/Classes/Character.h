enum CharacterAngle{
	ANGLE_DOWN_LEFT,
	ANGLE_DOWN,
	ANGLE_DOWN_RIGHT,
	ANGLE_UP_RIGHT,
	ANGLE_UP,
	ANGLE_UP_LEFT,
	ANGLE_ERR = -1
};


class Character : public cocos2d::Sprite
{
public:
	static Character* create(PlayerInfo currentPlayerInfo);
	void setRotate();
	bool isOnTile(TileKind);
private:
	//getter, setter neeeeeeed
	CharacterAngle currentAngle;

};