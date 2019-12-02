#include "cocos2d.h"
#include "Settings.h"
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"

USING_NS_CC;

Scene* Settings::createScene() {
	return Settings::create();
}

bool Settings::init() {

	if (!Scene::create()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 orgin = Director::getInstance()->getVisibleOrigin();

	auto layer1 = Layer::create();
	addChild(layer1);
	auto layer2 = Layer::create();
	addChild(layer2);

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2(0, 0));
	//background->setContentSize(Size(frameSize.width, frameSize.height));
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	auto width = background->getContentSize().width;
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	background->setPosition(Vec2(orgin.x, +orgin.y));
	layer1->addChild(background);

	auto jiantou = MenuItemImage::create("jiantou.png", "jiantou.png", CC_CALLBACK_1(Settings::menuJiantouCallback, this));
	jiantou->setAnchorPoint(Vec2(0, 0));
	jiantou->setScale(visibleSize.width * 0.1 / jiantou->getContentSize().width);
	jiantou->setPosition(Vec2(orgin.x + visibleSize.width * 0.03, orgin.y + visibleSize.height * 0.81));

	auto menu = Menu::create(jiantou, NULL);
	menu->setPosition(Vec2::ZERO);
	layer2->addChild(menu, 2);
	return true;
}

void Settings::menuJiantouCallback(cocos2d::Ref* pSender) {
	Director::getInstance()->popScene();
}