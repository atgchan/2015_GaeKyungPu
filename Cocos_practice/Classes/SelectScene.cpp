#include "pch.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "LoginLayer.h"
#include "definition.h"
#include "Odbc.h"
#include <locale>

Scene* SelectScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = SelectScene::create();
	scene->addChild(layer);

	return scene;
}

bool SelectScene::init()
{
	if (!Layer::init())
		return false;

	this->setName("SelectScene");
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Label* labelPrev = Label::createWithTTF("Exit", FILENAME_FONT_MAINMENU, 40);
	Label* labelNext = Label::createWithTTF("GameStart", FILENAME_FONT_MAINMENU, 40);
	Label* label1P = Label::createWithTTF("1P sign in", FILENAME_FONT_MAINMENU, 50);
	Label* label2P = Label::createWithTTF("2P sign in", FILENAME_FONT_MAINMENU, 50);
	Label* labelSignUp = Label::createWithTTF("sign up", FILENAME_FONT_MAINMENU, 50);


	MenuItemLabel* menu_prev = MenuItemLabel::create(labelPrev, CC_CALLBACK_1(SelectScene::MenuCloseCallback, this));
	menu_prev->setPosition(visibleSize.width / 4, visibleSize.height / 4);

	MenuItemLabel* menu_next = MenuItemLabel::create(labelNext, CC_CALLBACK_1(SelectScene::MenuClickCallback, this));
	menu_next->setPosition(visibleSize.width * 3 / 4, visibleSize.height / 4);

	//MenuItemLabel* signIn_1P = MenuItemLabel::create(label2P, CC_CALLBACK_0(SelectScene::PopUpLayer, this, SIGN_IN));
	MenuItemLabel* signIn_1P = MenuItemLabel::create(label1P, CC_CALLBACK_0(SelectScene::SignInLayerPlayer1, this));
	signIn_1P->setPosition(visibleSize.width / 4, visibleSize.height * 1 / 2);

	//MenuItemLabel* signIn_2P = MenuItemLabel::create(label2P, CC_CALLBACK_0(SelectScene::PopUpLayer, this, SIGN_IN));
	MenuItemLabel* signIn_2P = MenuItemLabel::create(label2P, CC_CALLBACK_0(SelectScene::SignInLayerPlayer2, this));
	signIn_2P->setPosition(visibleSize.width * 3 / 4, visibleSize.height * 1 / 2);

	MenuItemLabel* menu_signUp = MenuItemLabel::create(labelSignUp, CC_CALLBACK_0(SelectScene::PopUpLayer, this, SIGN_UP));
	menu_signUp->setPosition(visibleSize.width * 5 / 6, visibleSize.height* 5/6);




	cocos2d::Menu* mainMenu = Menu::create(menu_prev, menu_next, signIn_1P, signIn_2P, menu_signUp, nullptr);
	mainMenu->setName("mainMenu");
	mainMenu->setPosition(Vec2::ZERO);
	this->addChild(mainMenu);

//	Keyboard Event
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(SelectScene::OnKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(SelectScene::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FILENAME_SOUND_MAIN_BGM,true);

	return true;
}

void SelectScene::CreateLayer()
{
	dynamic_cast<cocos2d::Menu*>(getChildByName("mainMenu"))->setEnabled(false);

	while (getChildByName("popUpLayer"))
		removeChildByName("popUpLayer");

	LoginLayer* layer = LoginLayer::create();
	layer->setName("popUpLayer");
	layer->setPosition(Vec2::ZERO);
	this->addChild(layer);
}

//이 짓까지는 하고싶지 않았는데
void SelectScene::SignInLayerPlayer1()
{
	CreateLayer();

	MenuItemLabel* signBtn;

	Label* labelReturn = Label::createWithTTF("[ Sign In ]", FILENAME_FONT_MAINMENU, 30);
	signBtn = MenuItemLabel::create(labelReturn, CC_CALLBACK_0(SelectScene::SignInPlayer1, this));

	Label* labelClose = Label::createWithTTF("[ CLOSE ]", FILENAME_FONT_MAINMENU, 30);
	MenuItemLabel* closeBtn = MenuItemLabel::create(labelClose, CC_CALLBACK_0(SelectScene::CloseLayer, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();

	signBtn->setPosition(visibleSize.width * 2 / 5, visibleSize.height * 1 / 4);
	closeBtn->setPosition(visibleSize.width * 3 / 5, visibleSize.height * 1 / 4);

	cocos2d::Menu* returnMenu = Menu::create(signBtn, closeBtn, nullptr);
	returnMenu->setPosition(Vec2::ZERO);
	returnMenu->setName("returnMenu");
	this->addChild(returnMenu);

	return;
}

void SelectScene::SignInLayerPlayer2()
{
	CreateLayer();

	MenuItemLabel* signBtn;

	Label* labelReturn = Label::createWithTTF("[ Sign In ]", FILENAME_FONT_MAINMENU, 30);
	signBtn = MenuItemLabel::create(labelReturn, CC_CALLBACK_0(SelectScene::SignInPlayer2, this));

	Label* labelClose = Label::createWithTTF("[ CLOSE ]", FILENAME_FONT_MAINMENU, 30);
	MenuItemLabel* closeBtn = MenuItemLabel::create(labelClose, CC_CALLBACK_0(SelectScene::CloseLayer, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();

	signBtn->setPosition(visibleSize.width * 2 / 5, visibleSize.height * 1 / 4);
	closeBtn->setPosition(visibleSize.width * 3 / 5, visibleSize.height * 1 / 4);

	cocos2d::Menu* returnMenu = Menu::create(signBtn, closeBtn, nullptr);
	returnMenu->setPosition(Vec2::ZERO);
	returnMenu->setName("returnMenu");
	this->addChild(returnMenu);

	return;
}

void SelectScene::SignInPlayer1()
{
	SignIn();
	Odbc* mysql = Odbc::GetInstance();

	cocos2d::ui::EditBox* idBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("popUpLayer")->getChildByName("id"));
	cocos2d::ui::EditBox* pwBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("popUpLayer")->getChildByName("pw"));

	std::string idValue = idBox->getText();
	std::string pwValue = pwBox->getText();
	
	std::string result = mysql->GetPassword(idValue);
	
	if (result == pwValue)
	{
		CloseLayer();
		_Id1P = mysql->GetUserId(idValue);
		Label* player1Name = Label::createWithTTF(idValue, FILENAME_FONT_PIXEL, 120);

		while (getChildByName("player1_name"))
			removeChildByName("player1_name");

		Size visibleSize = Director::getInstance()->getVisibleSize();
		player1Name->setPosition(visibleSize.width * 1 / 4, visibleSize.height * 3 /5 + 20);
		player1Name->setName("player1_name");
		addChild(player1Name);



		Label* labelChangePW = Label::createWithTTF("Change PW", FILENAME_FONT_PIXEL, 30);
		Label* labelShowInfo = Label::createWithTTF("Show Info", FILENAME_FONT_PIXEL, 30);

		MenuItemLabel* menu_changePW = MenuItemLabel::create(labelChangePW, CC_CALLBACK_0(SelectScene::PopUpPWChange, this, _Id1P));
		menu_changePW->setAnchorPoint(Vec2(0, 0));
		menu_changePW->setPosition(visibleSize.width * 1 / 4 - 200, visibleSize.height * 3 / 5 - 50);

		MenuItemLabel* menu_showInfo = MenuItemLabel::create(labelShowInfo, CC_CALLBACK_0(SelectScene::ShowUserInfo, this, _Id1P, "user1", 0.25));
		menu_showInfo->setAnchorPoint(Vec2(0, 0));
		menu_showInfo->setPosition(visibleSize.width * 1 / 4 + 50, visibleSize.height * 3 / 5 - 50);

		cocos2d::Menu* userMenu = Menu::create(menu_changePW, menu_showInfo, nullptr);
		userMenu->setName("userMenu_1");
		userMenu->setPosition(Vec2::ZERO);
		this->addChild(userMenu);
	}
}

void SelectScene::ShowUserInfo(int userid, std::string name, float posx)
{
	while (getChildByName(name))
		removeChildByName(name);

	Odbc* mysql = Odbc::GetInstance();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	std::string strUserInfo = mysql->GetUserInfo(userid);
	cocos2d::Label* labelUserInfo = Label::createWithTTF(strUserInfo, FILENAME_FONT_PIXEL, 40);

	labelUserInfo->setName(name);
	labelUserInfo->setPosition(visibleSize.width * posx, visibleSize.height * 3 / 5 + 70);
	addChild(labelUserInfo);
}

void SelectScene::PopUpPWChange(int userid)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	cocos2d::Size editSize(200.0f, 50.0f);
	cocos2d::ui::EditBox* _NewPW = ui::EditBox::create(editSize, ui::Scale9Sprite::create(FILENAME_IMG_UI_INPUT_BOX));
	_NewPW->setName("changePW_");
	_NewPW->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	_NewPW->setFontSize(20);
	_NewPW->setPlaceHolder("input password");
	_NewPW->setMaxLength(16);
	_NewPW->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3 / 7));

	cocos2d::ui::EditBox* _NewPWConfirm = ui::EditBox::create(editSize, ui::Scale9Sprite::create(FILENAME_IMG_UI_INPUT_BOX));
	_NewPWConfirm->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	_NewPWConfirm->setName("changePW_");
	_NewPWConfirm->setFontSize(20);
	_NewPWConfirm->setPlaceHolder("input ONE MORE");
	_NewPWConfirm->setMaxLength(16);
	_NewPWConfirm->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3 / 7 - 50));

	this->addChild(_NewPW);
	this->addChild(_NewPWConfirm);

	Label* btnChange = Label::createWithTTF("Change", FILENAME_FONT_PIXEL, 40);
	MenuItemLabel* menu_change = MenuItemLabel::create(btnChange, CC_CALLBACK_0(SelectScene::ChangePassword, this, userid, _NewPW->getText(), _NewPWConfirm->getText()));
	menu_change->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 7 - 100);

	Menu* changeMenu = Menu::create(menu_change, nullptr);
	changeMenu->setPosition(Vec2(Vec2::ZERO));
	changeMenu->setName("changePW_");
	addChild(changeMenu);
}

void SelectScene::ChangePassword(int userid, std::string pw1, std::string pw2)
{
	Odbc* mysql = Odbc::GetInstance();

	if (pw1 != pw2)
		return;

	bool result = mysql->UpdatePlayerPassword(userid, pw1);
	
	if (result == true)
	{
		while (getChildByName("changePW_"))
			removeChildByName("changePW_");
	}
}


void SelectScene::SignInPlayer2()
{
	SignIn();
	Odbc* mysql = Odbc::GetInstance();

	cocos2d::ui::EditBox* idBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("popUpLayer")->getChildByName("id"));
	cocos2d::ui::EditBox* pwBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("popUpLayer")->getChildByName("pw"));

	std::string idValue = idBox->getText();
	std::string pwValue = pwBox->getText();

	std::string result = mysql->GetPassword(idValue);

	if (result == pwValue)
	{
		CloseLayer();
		_Id2P = mysql->GetUserId(idValue);

		Label* playerName = Label::createWithTTF(idValue, FILENAME_FONT_PIXEL, 120);

		while (getChildByName("player2_name"))
			removeChildByName("player2_name");

		Size visibleSize = Director::getInstance()->getVisibleSize();
		playerName->setPosition(visibleSize.width * 3 / 4, visibleSize.height * 3 / 5 + 20);
		playerName->setName("player2_name");
		addChild(playerName);



		Label* labelChangePW = Label::createWithTTF("Change PW", FILENAME_FONT_PIXEL, 30);
		Label* labelShowInfo = Label::createWithTTF("Show Info", FILENAME_FONT_PIXEL, 30);

		MenuItemLabel* menu_changePW = MenuItemLabel::create(labelChangePW, CC_CALLBACK_0(SelectScene::PopUpPWChange, this, _Id2P));
		menu_changePW->setAnchorPoint(Vec2(0, 0));
		menu_changePW->setPosition(visibleSize.width * 3 / 4 - 200, visibleSize.height * 3 / 5 - 50);

		MenuItemLabel* menu_showInfo = MenuItemLabel::create(labelShowInfo, CC_CALLBACK_0(SelectScene::ShowUserInfo, this, _Id2P, "user2", 0.75));
		menu_showInfo->setAnchorPoint(Vec2(0, 0));
		menu_showInfo->setPosition(visibleSize.width * 3 / 4 + 50, visibleSize.height * 3 / 5 - 50);

		cocos2d::Menu* userMenu = Menu::create(menu_changePW, menu_showInfo, nullptr);
		userMenu->setName("userMenu_2");
		userMenu->setPosition(Vec2::ZERO);
		this->addChild(userMenu);
	}
}





//	여기부터 정상 코드

void SelectScene::PopUpLayer(LayerType type)
{
	dynamic_cast<cocos2d::Menu*>(getChildByName("mainMenu"))->setEnabled(false);

	while (getChildByName("popUpLayer"))
		removeChildByName("popUpLayer");

	Size visibleSize = Director::getInstance()->getVisibleSize();

	LoginLayer* layer = LoginLayer::create();
	layer->setName("popUpLayer");
	layer->setPosition(Vec2::ZERO);
	this->addChild(layer);

	MenuItemLabel* signBtn;

	if (type == SIGN_IN)
	{
		Label* labelReturn = Label::createWithTTF("[ Sign In ]", FILENAME_FONT_MAINMENU, 30);
		signBtn = MenuItemLabel::create(labelReturn, CC_CALLBACK_0(SelectScene::SignIn, this));
	}
	if (type == SIGN_UP)
	{
		Label* labelReturn = Label::createWithTTF("[ Sign Up ]", FILENAME_FONT_MAINMENU, 30);
		signBtn = MenuItemLabel::create(labelReturn, CC_CALLBACK_0(SelectScene::SignUp, this));
	}
	
	Label* labelClose = Label::createWithTTF("[ CLOSE ]", FILENAME_FONT_MAINMENU, 30);
	MenuItemLabel* closeBtn = MenuItemLabel::create(labelClose, CC_CALLBACK_0(SelectScene::CloseLayer, this));

	signBtn->setPosition(visibleSize.width * 2 / 5, visibleSize.height * 1 / 4);
	closeBtn->setPosition(visibleSize.width * 3 / 5, visibleSize.height * 1 / 4);

	cocos2d::Menu* returnMenu = Menu::create(signBtn, closeBtn, nullptr);
	returnMenu->setPosition(Vec2::ZERO);
	returnMenu->setName("returnMenu");
	this->addChild(returnMenu);

	return;
}

void SelectScene::CloseLayer()
{
	this->removeChildByName("popUpLayer");
	this->removeChildByName("returnMenu");
	dynamic_cast<cocos2d::Menu*>(getChildByName("mainMenu"))->setEnabled(true);
}

void SelectScene::SignIn()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	cocos2d::ui::EditBox* idBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("popUpLayer")->getChildByName("id"));
	cocos2d::ui::EditBox* pwBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("popUpLayer")->getChildByName("pw"));
	
	std::string idValue = idBox->getText();
	std::string pwValue = pwBox->getText();

	if (idValue.empty() || pwValue.empty())
		return;

	while (this->getChildByName("statusReturn"))
		this->removeChildByName("statusReturn");

	while (this->getChildByName("resultReturn"))
		this->removeChildByName("resultReturn");

	Odbc* mysql = Odbc::GetInstance();
	bool result = mysql->Connect(L"me", L"testudo", L"next!!@@##$$");
	if (!result)
	{
		cocos2d::Label* labelResult = Label::createWithTTF("[ERROR::Connect FAIL]", FILENAME_FONT_MAINMENU, 20);
		labelResult->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 + 50);
		this->addChild(labelResult);
		return;
	}

	bool exist = mysql->CheckDataExist("user", "name", idValue);

	if (!exist)
	{
		Label* resultReturn = Label::createWithTTF(idValue + " : No Data", FILENAME_FONT_MAINMENU, 20);
		resultReturn->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 - 50);
		resultReturn->setName("resultReturn");
		this->addChild(resultReturn);
	}

	return;
}

void SelectScene::SignUp()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	cocos2d::ui::EditBox* idBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("popUpLayer")->getChildByName("id"));
	cocos2d::ui::EditBox* pwBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("popUpLayer")->getChildByName("pw"));
	std::string idValue = idBox->getText();
	std::string pwValue = pwBox->getText();

	if (idValue.empty() || pwValue.empty())
		return;

	while (this->getChildByName("statusReturn"))
		this->removeChildByName("statusReturn");

	while (this->getChildByName("resultReturn"))
		this->removeChildByName("resultReturn");

	Odbc* mysql = Odbc::GetInstance();
	if (mysql->IsConnect() == false)
	{
		bool result = mysql->Connect(L"me", L"testudo", L"next!!@@##$$");
		if (!result)
		{
			cocos2d::Label* labelResult = Label::createWithTTF("[ERROR::Connect FAIL]", FILENAME_FONT_MAINMENU, 20);
			labelResult->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 + 50);
			this->addChild(labelResult);
			return;
		}
	}

	if (IsStringAlnum(idValue))
		return;

	bool exist = mysql->CheckDataExist("user", "name", idValue);

	if (!exist)
	{
		std::wstring idWValue = mysql->utf8_to_wstring(idValue);
		std::wstring pwWValue = mysql->utf8_to_wstring(pwValue);

		bool result = mysql->InsertData("user", "name, password", "'"+idValue+"','"+pwValue+"'");

		if (result)
		{
			Label* resultReturn = Label::createWithTTF(idValue + " is created", FILENAME_FONT_MAINMENU, 20);
			resultReturn->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 - 50);
			resultReturn->setName("resultReturn");
			this->addChild(resultReturn);
			
			CloseLayer();
			return;
		}
	}
	else
	{
		Label* resultReturn = Label::createWithTTF(idValue + " is already exist", FILENAME_FONT_MAINMENU, 20);
		resultReturn->setName("resultReturn");
		resultReturn->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 - 50);
		this->addChild(resultReturn);
	}
	return;
}

void SelectScene::MenuClickCallback(cocos2d::Ref* pSender)
{
	GameSceneManager* gmInstance = GameSceneManager::getInstance();
	gmInstance->InitializeGame();
	gmInstance->InitPlayerData(_Id1P, _Id2P);

	cocos2d::Scene* gameScene = GameScene::CreateScene();
	Director::getInstance()->pushScene(gameScene);
}

void SelectScene::MenuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void SelectScene::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	
}

void SelectScene::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	
}

bool SelectScene::IsStringAlnum(std::string str)
{
	for (int i = 0; i < str.length();++i)
	{
		if (str[i] < -1)
			return false;
	}
	return true;
}