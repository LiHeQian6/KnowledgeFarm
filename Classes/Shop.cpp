#include "Shop.h"
#include "SimpleAudioEngine.h"
#include <iostream>
using namespace std;

USING_NS_CC;

Scene* Shop::createScene() {
	return Shop::create();
}

bool Shop::init() {

	if (!Scene::init())
	{
		return false;
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 orgin = Director::getInstance()->getVisibleOrigin();
	auto glView = Director::getInstance()->getOpenGLView();
	auto frameSize = glView->getFrameSize();

	auto width = frameSize.width;
	auto height = frameSize.height;

	auto text = Label::createWithTTF("Shop", "fonts/Marker Felt.ttf", 24);
	text->setTextColor(Color4B::BLUE);
	text->setAnchorPoint(Vec2(0, 0));
	text->setPosition(Vec2(orgin.x+visibleSize.width/2, orgin.y+visibleSize.height/2));
	addChild(text,1);

	auto background = Sprite::create("shopBackground.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setContentSize(Size(visibleSize.width,visibleSize.height));
	background->setPosition(Vec2(orgin.x, +orgin.y));
	addChild(background);

	auto map = TMXTiledMap::create("shopMap.tmx");
	map->setScale(0.4f);
	map->setAnchorPoint(Vec2(0,0));
	map->setPosition(Vec2(orgin.x+(frameSize.width - map->getMapSize().width*404*map->getScale())/2, orgin.y+(frameSize.height - map->getMapSize().height*map->getScale()*404) /2));
	addChild(map);
	return true;
}