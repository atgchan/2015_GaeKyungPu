#include "pch.h"
#include "LoginLayer.h"
#include "SelectScene.h"
#include "ui\UIEditBox\UIEditBox.h"

cocos2d::Scene* LoginLayer::scene()
{
	cocos2d::Scene *scene = Scene::create();
	LoginLayer* layer = LoginLayer::create();

	scene->addChild(layer);
	return scene;
}

bool LoginLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //투명하게
		return false;
	this->setName("LoginLayer");

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	//backLayer추가
	BackLayer = LayerColor::create(ccc4(0, 0, 0, 50), visibleSize.width, visibleSize.height);
	BackLayer->setAnchorPoint(Vec2(0, 0));
	BackLayer->setPosition(Vec2(0, 0));
	this->addChild(BackLayer);

	Sprite* resultPage = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_RESULT_WINDOW);
	resultPage->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(resultPage);

	Sprite* inputSprite = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_INPUT_BOX);
	inputSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(inputSprite);

	Sprite* inputSprite2 = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_INPUT_BOX);
	inputSprite2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3/7));
	this->addChild(inputSprite2);

//#	http://www.cocos2d-x.org/wiki/EditBox#How-to-use

	cocos2d::Size editSize(200.0f, 50.0f);
	cocos2d::ui::EditBox* _editName = ui::EditBox::create(editSize, ui::Scale9Sprite::create(FILENAME_IMG_UI_INPUT_BOX));
	_editName->setName("id");
	_editName->setFontSize(20);
	_editName->setPlaceHolder("input name");
	_editName->setMaxLength(16);
	_editName->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(_editName);

	cocos2d::ui::EditBox* _editPw = ui::EditBox::create(editSize, ui::Scale9Sprite::create(FILENAME_IMG_UI_INPUT_BOX));
	_editPw->setName("pw");
	_editPw->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	_editPw->setFontSize(20);
	_editPw->setPlaceHolder("input password");
	_editPw->setMaxLength(16);
	_editPw->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3/7));
	this->addChild(_editPw);

	return true;
}

void LoginLayer::ReturnToMenu()
{
	
}

void LoginLayer::SetValue(PlayerData* pData1, PlayerData* pData2)
{

}