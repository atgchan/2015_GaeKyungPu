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
	static Character* create(const std::string colorInfo);
	void setRotate();
private:
	//getter, setter neeeeeeed
	CharacterAngle currentAngle;

};