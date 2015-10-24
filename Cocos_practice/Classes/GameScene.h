#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

USING_NS_CC;
//using namespace cocos2d

class GameScene : public Layer
{
public:
	//�ٸ� ȭ�鿡�� �ش� ȭ������ ��ȯ�� �� � ���Ǵ� ���� �޼ҵ�
    static Scene* createScene();
	//Layer�� ��ӹ��� Ŭ������ ������ �� ������ �޼ҵ� �������� ���� ���� ȣ��Ǵ� �޼ҵ�
    virtual bool init();
	//�ش� Ŭ������ ������ �� new ��ɾ �ƴ� ���ڽ�2d-x���� �����ϴ� create()�޼ҵ带 ����� �� �ְ� ���ִ� ���� �޼ҵ�(��ũ��?)
	CREATE_FUNC(GameScene);

	void menuClickCallback(Ref* pSender);
	void menuCloseCallback(Ref* pSender);

	void setUnitByClick(Event* event);
	void rotateUnitByClick(Ref* pSender);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

#endif
