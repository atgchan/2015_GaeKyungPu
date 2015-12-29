#pragma once
#include <array>

USING_NS_CC;

class SelectScene : public Layer
{
public:
	//�ٸ� ȭ�鿡�� �ش� ȭ������ ��ȯ�� �� � ���Ǵ� ���� �޼ҵ�
	static Scene* CreateScene();

	//Layer�� ��ӹ��� Ŭ������ ������ �� ������ �޼ҵ� �������� ���� ���� ȣ��Ǵ� �޼ҵ�
	virtual bool init();

	//�ش� Ŭ������ ������ �� new ��ɾ �ƴ� ���ڽ�2d-x���� �����ϴ� create()�޼ҵ带 ����� �� �ְ� ���ִ� ���� �޼ҵ�(��ũ��?)
	CREATE_FUNC(SelectScene);

private:
	void	MenuClickCallback(Ref* pSender);
	void	MenuCloseCallback(Ref* pSender);

	void	PopUpLayer(LayerType type);
	void	PopUpSignInLayer();
	void	PopUpSignUpLayer();
	void	CloseLayer();

	void	SignUp();
	void	SignIn();

	void	OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void	OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	int			_Id1P;
	int			_Id2P;

	std::array<std::string, 10> _ColorList;
	std::array<std::string, 10> _UnitList;
};