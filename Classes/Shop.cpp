#include "Shop.h"
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "Learn.h"
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
	auto layer = Layer::create();
	addChild(layer, 1);
	auto layer1 = Layer::create();
	addChild(layer1, 2);
	auto layer2 = Layer::create();
	addChild(layer2, 3);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 orgin = Director::getInstance()->getVisibleOrigin();

	auto jiantou = MenuItemImage::create("jiantou.png", "jiantou.png", CC_CALLBACK_1(Shop::menuJiantouCallback, this));
	jiantou->setAnchorPoint(Vec2(0, 0));
	jiantou->setScale(visibleSize.width * 0.1 / jiantou->getContentSize().width);
	jiantou->setPosition(Vec2(orgin.x + visibleSize.width * 0.03, orgin.y + visibleSize.height * 0.81));

	auto menu = Menu::create(jiantou, NULL);
	menu->setPosition(Vec2::ZERO);
	layer2->addChild(menu, 2);

	auto text = Label::createWithTTF("Shop", "fonts/Marker Felt.ttf", 24);
	text->setTextColor(Color4B::BLUE);
	text->setAnchorPoint(Vec2(0.5, 0.5));
	text->setPosition(Vec2(orgin.x + visibleSize.width / 2, orgin.y + visibleSize.height * 0.92));
	layer2->addChild(text, 1);

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2(0, 0));
	//background->setContentSize(Size(frameSize.width, frameSize.height));
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	auto width = background->getContentSize().width;
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	background->setPosition(Vec2(orgin.x, +orgin.y));
	layer->addChild(background);

	auto map1 = TMXTiledMap::create("ShopMaptmx.tmx");
	map1->setScale(visibleSize.width *0.87/ map1->getContentSize().width);
	map1->setAnchorPoint(Vec2(0, 0));
	map1->setPosition(Vec2(orgin.x + visibleSize.width * 0.05, orgin.y + visibleSize.height * 0.05));
	layer1->addChild(map1, 1);

	auto map2 = TMXTiledMap::create("ShopMaptmx.tmx");
	map2->setScale(visibleSize.width *0.87 / map2->getContentSize().width);
	map2->setAnchorPoint(Vec2(0, 0));
	map2->setPosition(Vec2(orgin.x + visibleSize.width * 0.05, orgin.y + visibleSize.height * 0.3));
	layer1->addChild(map2, 2);

	auto map3 = TMXTiledMap::create("ShopMaptmx.tmx");
	map3->setScale(visibleSize.width *0.87/ map3->getContentSize().width);
	map3->setAnchorPoint(Vec2(0, 0));
	map3->setPosition(Vec2(orgin.x + visibleSize.width * 0.05, orgin.y + visibleSize.height * 0.55));
	layer1->addChild(map3, 3);

	ShowFlower(layer1,map3,1);
	ShowFlower(layer1,map2,2);
	ShowFlower(layer1,map1,3);
	return true;
}

void Shop::ShowFlower(Layer* layer1,TMXTiledMap* map,int count) {
	Vec2 orgin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto layer = map->getObjectGroup("flower");
	auto tileSize = map->getTileSize();
	auto ob1 = layer->getObjects();
	for (ValueVector::iterator it = ob1.begin(); it != ob1.end(); it++) {
		Value obj = *it;
		ValueMap map = obj.asValueMap();
		auto flower = Sprite::create("meigui.png");
		flower->setScale(visibleSize.height * 0.15 / flower->getContentSize().height);
		flower->setAnchorPoint(Vec2(0, 0));
		flower->setPosition(Vec2(orgin.x + map.at("x").asFloat()* visibleSize.width * 0.3 / flower->getContentSize().width+ visibleSize.height / 6, orgin.y + map.at("y").asFloat()*visibleSize.height * 0.15 / flower->getContentSize().height + visibleSize.height *0.07+ visibleSize.height *0.25*(count-1)));
		layer1->addChild(flower,4);
	}

}

void Shop::menuJiantouCallback(Ref* pSender) {
	Director::sharedDirector()->popScene();
}