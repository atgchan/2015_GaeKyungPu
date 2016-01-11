#pragma once
#include <array>
#include "ui\UIEditBox\UIEditBox.h"

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

	bool	IsStringAlnum(std::string str);
	
private:
	void	MenuClickCallback(Ref* pSender);
	void	MenuCloseCallback(Ref* pSender);

	void	PopUpLayer(LayerType type);
	void	SignInLayerPlayer1();
	void	SignInLayerPlayer2();

	void	ShowUserInfo(int userid, std::string name, float posx);
	void	ChangePassword(int userid, std::string pw1, std::string pw2);
	void	PopUpPWChange(int userid);

	void	CreateLayer();
	void	CloseLayer();

	void	SignUp();
	void	SignIn();
	void	SignInPlayer1();
	void	SignInPlayer2();

	void	OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void	OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	int		_Id1P;
	int		_Id2P;

	std::array<std::string, 10> _ColorList;
	std::array<std::string, 10> _UnitList;
};