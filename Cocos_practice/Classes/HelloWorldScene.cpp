#include "pch.h"
#include "HelloWorldScene.h"
#include "Self_Tile.h"
#include "TileMap.h"

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
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255)))
	{
		return false;
	}
	/*auto tile = Self_Tile::create(TILE_PLAIN, "Map/tile_plain.png");
	tile->setPosition(Point(400, 400));
	tile->setTypeOfTile(TILE_PLAIN);
	CCLOG("%d", tile->getTypeOfTile());

	this->addChild(tile);*/

	TileMap::getInstance()->createMap();
	//TileMap::getInstance()->setAnchorPoint(Point(0.5f, 0.5f));
	//TileMap::getInstance()->setPosition(Point((Director::getInstance()->getWinSize().width) / 2, (Director::getInstance()->getWinSize().height) / 2));

	this->addChild(TileMap::getInstance());
	
    return true;
}