#include "pch.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "LoginLayer.h"
#include "definition.h"
#include "ui\UIEditBox\UIEditBox.h"
#include "Odbc.h"


#define SIGN_IN 1
#define SIGN_UP 0


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
	MenuItemLabel* menu_next = MenuItemLabel::create(labelNext, CC_CALLBACK_1(SelectScene::MenuCloseCallback, this));

	MenuItemLabel* menu_1P = MenuItemLabel::create(label1P, CC_CALLBACK_0(SelectScene::PopUpInputLayer, this));
	MenuItemLabel* menu_2P = MenuItemLabel::create(label2P, CC_CALLBACK_0(SelectScene::PopUpInputLayer, this));

	MenuItemLabel* menu_signUp = MenuItemLabel::create(labelSignUp, CC_CALLBACK_0(SelectScene::PopUpInputLayer, this));

	cocos2d::Menu* mainMenu = Menu::create(menu_prev, menu_next, menu_1P, menu_2P, menu_signUp, nullptr);
	
	mainMenu->alignItemsVertically();
	menu_prev->setPosition(visibleSize.width/4, visibleSize.height/2);
	menu_next->setPosition(visibleSize.width *3/4, visibleSize.height / 2);

	menu_1P->setPosition(visibleSize.width / 2, visibleSize.height* 1/ 4);
	menu_2P->setPosition(visibleSize.width / 2, visibleSize.height* 3/ 4);

	menu_signUp->setPosition(visibleSize.width * 5 / 6, visibleSize.height* 5/6);

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

void SelectScene::PopUpInputLayer(int type, int idnum = 0)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	LoginLayer* Signup = LoginLayer::create();
	Signup->setName("signupLayer");
	Signup->setPosition(Vec2::ZERO);
	this->addChild(Signup);

	Label* labelReturn = Label::createWithTTF("Return", FILENAME_FONT_MAINMENU, 50);
	MenuItemLabel* menu_return = MenuItemLabel::create(labelReturn, CC_CALLBACK_0(SelectScene::SignUp, this));

	if (type = SIGN_IN)
		menu_return = MenuItemLabel::create(labelReturn, CC_CALLBACK_0(SelectScene::SignIn, this, idnum));

	cocos2d::Menu* returnMenu = Menu::create(menu_return, nullptr);
	returnMenu->setPosition(visibleSize.width / 2, visibleSize.height * 1 / 4);
	returnMenu->setName("returnMenu");
	this->addChild(returnMenu);
}

void SelectScene::SignIn(int playerNum)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	cocos2d::ui::EditBox* idBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("signupLayer")->getChildByName("id"));
	cocos2d::ui::EditBox* pwBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("signupLayer")->getChildByName("pw"));
	std::string idValue = idBox->getText();
	std::string pwValue = pwBox->getText();

	if (idValue.empty() || pwValue.empty())
		return;

	while (this->getChildByName("statusReturn"))
		this->removeChildByName("statusReturn");

	while (this->getChildByName("resultReturn"))
		this->removeChildByName("resultReturn");

	//#	아이디가 존재하는지 query를 날려 확인
	//# 존재하지 않는다면 생성, 아니면 무반응

	Odbc* mysql = Odbc::GetInstance();
	std::string result = mysql->Connect(L"me", L"testudo", L"next!!@@##$$");
	Label* labelResult = Label::createWithTTF(result, FILENAME_FONT_MAINMENU, 20);
	labelResult->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 + 50);
	this->addChild(labelResult);

	std::string status = mysql->CheckDataExist("user", "name", idValue);

	if (status == "")
		return;

	else if (status == "sql no data")
	{
		Label* resultReturn = Label::createWithTTF(idValue + " : No Data", FILENAME_FONT_MAINMENU, 20);
		resultReturn->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 - 50);
		resultReturn->setName("resultReturn");
		this->addChild(resultReturn);

		return;
	}

	else
	{
		Label* statusReturn = Label::createWithTTF(status, FILENAME_FONT_MAINMENU, 20);
		statusReturn->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7);
		statusReturn->setName("statusReturn");
		this->addChild(statusReturn);

		Label* resultReturn = Label::createWithTTF(idValue + " is already exist", FILENAME_FONT_MAINMENU, 20);
		statusReturn->setName("resultReturn");
		resultReturn->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 - 50);
		this->addChild(resultReturn);

		std::wstring idWvalue = mysql->utf8_to_wstring(idValue);
		std::wstring pwWvalue = mysql->utf8_to_wstring(pwValue);

		bool result = mysql->PushQuery(L"INSERT INTO testudo.user(name, password) VALUES('" + idWvalue + L"','" + pwWvalue + L"')");
		if (result)
		{
			this->removeChildByName("signupLayer");
			this->removeChildByName("returnMenu");
		}

		return;
	}
}



void SelectScene::SignUp()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	cocos2d::ui::EditBox* idBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("signupLayer")->getChildByName("id"));
	cocos2d::ui::EditBox* pwBox = static_cast<cocos2d::ui::EditBox*>(this->getChildByName("signupLayer")->getChildByName("pw"));
	std::string idValue = idBox->getText();
	std::string pwValue = pwBox->getText();

	if (idValue.empty() || pwValue.empty())
		return;

	while (this->getChildByName("statusReturn"))
		this->removeChildByName("statusReturn");

	while (this->getChildByName("resultReturn"))
		this->removeChildByName("resultReturn");

//#	아이디가 존재하는지 query를 날려 확인
//# 존재하지 않는다면 생성, 아니면 무반응

	Odbc* mysql = Odbc::GetInstance();
	std::string result = mysql->Connect(L"me", L"testudo", L"next!!@@##$$");
	Label* labelResult = Label::createWithTTF(result, FILENAME_FONT_MAINMENU, 20);
	labelResult->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1/7 + 50);
	this->addChild(labelResult);
	
	std::string status = mysql->CheckDataExist("user", "name", idValue);

	if(status == "")
		return;

	else if (status == "sql no data")
	{
		Label* resultReturn = Label::createWithTTF(idValue + " is created", FILENAME_FONT_MAINMENU, 20);
		resultReturn->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 - 50);
		resultReturn->setName("resultReturn");
		this->addChild(resultReturn);

		std::wstring idWvalue = mysql->utf8_to_wstring(idValue);
		std::wstring pwWvalue = mysql->utf8_to_wstring(pwValue);

		bool result = mysql->PushQuery(L"INSERT INTO testudo.user(name, password) VALUES('" + idWvalue + L"','" + pwWvalue + L"')");
		if (result)
		{
			this->removeChildByName("signupLayer");
			this->removeChildByName("returnMenu");
		}
		return;
	}

	else
	{
		Label* statusReturn = Label::createWithTTF(status, FILENAME_FONT_MAINMENU, 20);
		statusReturn->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7);
		statusReturn->setName("statusReturn");
		this->addChild(statusReturn);

		Label* resultReturn = Label::createWithTTF(idValue + " is already exist", FILENAME_FONT_MAINMENU, 20);
		statusReturn->setName("resultReturn");
		resultReturn->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 7 - 50);
		this->addChild(resultReturn);

		return;
	}
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
	/*auto target = event->getCurrentTarget()->getChildByName("cursor");
	Vec2 loc = target->getPosition();

	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;

	case EventKeyboard::KeyCode::KEY_ENTER:
		target->setPosition(loc.x -= 15, loc.y);
		break;
	}*/
}

void SelectScene::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*auto target = event->getCurrentTarget()->getChildByName("cursor");
	Vec2 loc = target->getPosition();

	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ENTER:
		target->setPosition(loc.x += 15, loc.y);
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		target->setPosition(loc.x, loc.y += 30);
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		target->setPosition(loc.x, loc.y -= 30);
		break;
	}*/
}
