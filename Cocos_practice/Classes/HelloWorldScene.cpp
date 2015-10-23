#include "pch.h"
#include "HelloWorldScene.h"

USING_NS_CC;

#define TILESIZE_W = 162
#define TILESIZE_H = 66
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(0,0,0,255) ))
    {
        return false;
    }
	auto winheight = Director::getInstance()->getWinSize().height;
	
	

	Sprite* tile[10];

	for (int i = 0; i < 10; ++i)
	{
		tile[i] =  Sprite::create("tile_plain.png");
		tile[i]->setAnchorPoint(Point(0, 1.0));
	}

	auto s = Director::getInstance()->getWinSize();
	
	

	//같은 라인에서 우측으로 한 칸 갈 때마다 x + 126포인트, y + 30이동한다.
	//아래로 2 라인 내려갈 때마다 66포인트 이동한다.
	//우측아래는 30포인트, 좌측아래는 36포인트로 해보자.
	//같은 라인에서 우측으로 한 칸 갈 때마다 
	tile[0]->setPosition(0, winheight / 2);
	this->addChild(tile[0]);
	for (int i = 1; i < 10; ++i)
	{
		tile[i]->setPosition(Point(tile[i-1]->getPositionX() + 126, tile[i-1]->getPositionY() + 27));
		this->addChild(tile[i]);
	}
	auto asdghesrhbaethbadtf = tile[0]->getPositionX();
	auto asdghesrhbaethbadasfasdfgasdtf = tile[1]->getPositionX();

	auto eorkrtjs = Sprite::create("45.png");
	this->addChild(eorkrtjs, 0, "a");
	
	eorkrtjs->setAnchorPoint(Point(0.5, 0.08));
	eorkrtjs->setPosition(Point(720, 550));


	this->schedule(schedule_selector(HelloWorld::Tick));
	

    return true;
}

void HelloWorld::Tick(float dt)
{
	
}