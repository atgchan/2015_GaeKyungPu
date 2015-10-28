#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

USING_NS_CC;
//using namespace cocos2d

class GameScene : public Layer
{
private:
	static int turn;

	void	menuClickCallback(Ref* pSender);
	void	menuCloseCallback(Ref* pSender);

	void	eventByClick(Event* event);
	
	cocos2d::Sprite* getClickedUnit(Event* event);
	void rotateUnitToLeft(cocos2d::Sprite* sprite);
public:
	//�ٸ� ȭ�鿡�� �ش� ȭ������ ��ȯ�� �� � ���Ǵ� ���� �޼ҵ�
    static Scene* createScene();

	//Layer�� ��ӹ��� Ŭ������ ������ �� ������ �޼ҵ� �������� ���� ���� ȣ��Ǵ� �޼ҵ�
    virtual bool init();

	//�ش� Ŭ������ ������ �� new ��ɾ �ƴ� ���ڽ�2d-x���� �����ϴ� create()�޼ҵ带 ����� �� �ְ� ���ִ� ���� �޼ҵ�(��ũ��?)
	CREATE_FUNC(GameScene);
};
#endif
