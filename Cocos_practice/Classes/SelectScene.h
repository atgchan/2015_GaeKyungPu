#pragma once
#include <array>
#include "ui\UIEditBox\UIEditBox.h"

USING_NS_CC;

class SelectScene : public Layer
{
public:
	//다른 화면에서 해당 화면으로 전환할 때 등에 사용되는 전역 메소드
	static Scene* CreateScene();

	//Layer를 상속받은 클래스가 생성될 때 생성자 메소드 다음으로 가장 먼저 호출되는 메소드
	virtual bool init();

	//해당 클래스를 생성할 때 new 명령어가 아닌 코코스2d-x에서 제공하는 create()메소드를 사용할 수 있게 해주는 전역 메소드(매크로?)
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