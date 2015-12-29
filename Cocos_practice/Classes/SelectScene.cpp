#include "pch.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "LoginLayer.h"
#include "definition.h"
#include "ui\UIEditBox\UIEditBox.h"
#include "Odbc.h"


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

	Label* title = Label::createWithTTF("color Select", FILENAME_FONT_MAINMENU, 80);
	title->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);
	this->addChild(title);

	Label* labelPrev = Label::createWithTTF("prev", FILENAME_FONT_MAINMENU, 40);
	Label* labelNext = Label::createWithTTF("next", FILENAME_FONT_MAINMENU, 40);
	Label* label1P = Label::createWithTTF("1P sign in", FILENAME_FONT_MAINMENU, 50);
	Label* label2P = Label::createWithTTF("2P sign in", FILENAME_FONT_MAINMENU, 50);
	Label* labelSignUp = Label::createWithTTF("sign up", FILENAME_FONT_MAINMENU, 50);

	MenuItemLabel* menu_prev = MenuItemLabel::create(labelPrev, CC_CALLBACK_1(SelectScene::MenuClickCallback, this));
	menu_prev->setPosition(visibleSize.width / 4, visibleSize.height / 2);

	MenuItemLabel* menu_next = MenuItemLabel::create(labelNext, CC_CALLBACK_1(SelectScene::MenuCloseCallback, this));
	menu_next->setPosition(visibleSize.width * 3 / 4, visibleSize.height / 2);

	MenuItemLabel* signIn_1P = MenuItemLabel::create(label1P, CC_CALLBACK_0(SelectScene::PopUpLayer, this, SIGN_IN));
	signIn_1P->setPosition(visibleSize.width / 2, visibleSize.height * 1 / 4);

	MenuItemLabel* signIn_2P = MenuItemLabel::create(label2P, CC_CALLBACK_0(SelectScene::PopUpLayer, this, SIGN_IN));
	signIn_2P->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);

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
		labelReturn->setPosition(visibleSize.width * 2 / 5, visibleSize.height * 1 / 4);
		signBtn = MenuItemLabel::create(labelReturn, CC_CALLBACK_0(SelectScene::SignIn, this));
		signBtn->setEnabled(true);
	}
	if (type == SIGN_UP)
	{
		Label* labelReturn = Label::createWithTTF("[ Sign Up ]", FILENAME_FONT_MAINMENU, 30);
		labelReturn->setPosition(visibleSize.width * 2 / 5, visibleSize.height * 1 / 4);
		signBtn = MenuItemLabel::create(labelReturn, CC_CALLBACK_0(SelectScene::SignUp, this));
		signBtn->setEnabled(true);
	}
	
	Label* labelClose = Label::createWithTTF("[ CLOSE ]", FILENAME_FONT_MAINMENU, 30);
	labelClose->setPosition(visibleSize.width * 3 / 5, visibleSize.height * 1 / 4);
	MenuItemLabel* closeBtn = MenuItemLabel::create(labelClose, CC_CALLBACK_0(SelectScene::CloseLayer, this));

	cocos2d::Menu* returnMenu = Menu::create(signBtn, closeBtn, nullptr);
	returnMenu->setPosition(Vec2::ZERO);
	returnMenu->setName("returnMenu");
	returnMenu->setEnabled(true);
	this->addChild(returnMenu);
}

void SelectScene::PopUpSignInLayer()
{
	dynamic_cast<cocos2d::Menu*>(getChildByName("mainMenu"))->setEnabled(false);

	while (getChildByName("popUpLayer"))
		removeChildByName("popUpLayer");

	Size visibleSize = Director::getInstance()->getVisibleSize();

	LoginLayer* layer = LoginLayer::create();
	layer->setName("popUpLayer");
	layer->setPosition(Vec2::ZERO);
	this->addChild(layer);
	
	Label* labelReturn = Label::createWithTTF("[ Sign In ]", FILENAME_FONT_MAINMENU, 30);
	labelReturn->setPosition(visibleSize.width * 2 / 5, visibleSize.height * 1 / 4);
	MenuItemLabel* signUpBtn = MenuItemLabel::create(labelReturn, CC_CALLBACK_0(SelectScene::SignIn, this));

	Label* labelClose = Label::createWithTTF("[ CLOSE ]", FILENAME_FONT_MAINMENU, 30);
	labelClose->setPosition(visibleSize.width * 3 / 5, visibleSize.height * 1 / 4);
	MenuItemLabel* closeBtn = MenuItemLabel::create(labelClose, CC_CALLBACK_0(SelectScene::CloseLayer, this));
	
	cocos2d::Menu* returnMenu = Menu::create(signUpBtn, closeBtn, nullptr);
	returnMenu->setPosition(Vec2::ZERO);
	returnMenu->setName("returnMenu");
	this->addChild(returnMenu);
}

void SelectScene::PopUpSignUpLayer()
{
	dynamic_cast<cocos2d::Menu*>(getChildByName("mainMenu"))->setEnabled(false);

	while (getChildByName("popUpLayer"))
		removeChildByName("popUpLayer");

	Size visibleSize = Director::getInstance()->getVisibleSize();

	LoginLayer* layer = LoginLayer::create();
	layer->setName("popUpLayer");
	layer->setPosition(Vec2::ZERO);
	this->addChild(layer);

	Label* labelReturn = Label::createWithTTF("[ Sign Up ]", FILENAME_FONT_MAINMENU, 30);
	labelReturn->setPosition(visibleSize.width * 2 / 5, visibleSize.height * 1 / 4);
	MenuItemLabel* signUpBtn = MenuItemLabel::create(labelReturn, CC_CALLBACK_0(SelectScene::SignUp, this));

	Label* labelClose = Label::createWithTTF("[ CLOSE ]", FILENAME_FONT_MAINMENU, 30);
	labelClose->setPosition(visibleSize.width * 3 / 5, visibleSize.height * 1 / 4);
	MenuItemLabel* closeBtn = MenuItemLabel::create(labelClose, CC_CALLBACK_0(SelectScene::CloseLayer, this));

	cocos2d::Menu* returnMenu = Menu::create(signUpBtn, closeBtn, nullptr);
	returnMenu->setPosition(Vec2::ZERO);
	returnMenu->setName("returnMenu");
	this->addChild(returnMenu);
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
	Label* labelResult;
	labelResult->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 + 50);
	this->addChild(labelResult);

	if (!result)
	{
		labelResult = Label::createWithTTF("[ERROR::Connect FAIL]", FILENAME_FONT_MAINMENU, 20);
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
	else
	{
		Label* resultReturn = Label::createWithTTF(idValue + " is already exist", FILENAME_FONT_MAINMENU, 20);
		resultReturn->setName("resultReturn");
		resultReturn->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 - 50);
		this->addChild(resultReturn);

		std::wstring idWvalue = mysql->utf8_to_wstring(idValue);
		std::wstring pwWvalue = mysql->utf8_to_wstring(pwValue);


		bool result = mysql->PushQuery(L"INSERT INTO testudo.user(name, password) VALUES('" + idWvalue + L"','" + pwWvalue + L"')");
		
		if (result)
			CloseLayer();
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

	bool exist = mysql->CheckDataExist("user", "name", idValue);

	if (!exist)
	{
		Label* resultReturn = Label::createWithTTF(idValue + " is created", FILENAME_FONT_MAINMENU, 20);
		resultReturn->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 - 50);
		resultReturn->setName("resultReturn");
		this->addChild(resultReturn);

		std::wstring idWvalue = mysql->utf8_to_wstring(idValue);
		std::wstring pwWvalue = mysql->utf8_to_wstring(pwValue);

		bool result = mysql->PushQuery(L"INSERT INTO testudo.user(name, password) VALUES('" + idWvalue + L"','" + pwWvalue + L"')");
		if (result)
			CloseLayer();
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
