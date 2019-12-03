#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "MathScene.h"
USING_NS_CC;

Scene* MathScene::createScene() {
	return MathScene::create();
}

bool MathScene::init() {

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 orgin = Director::getInstance()->getVisibleOrigin();

	/*auto jiantou = MenuItemImage::create("jiantou.png", "jiantou.png", CC_CALLBACK_1(Learn::onClickJiantouCallBack, this));
	jiantou->setAnchorPoint(Vec2(0, 0));
	jiantou->setScale(visibleSize.width * 0.1 / jiantou->getContentSize().width);
	jiantou->setPosition(Vec2(orgin.x + visibleSize.width * 0.03, orgin.y + visibleSize.height * 0.80));

	auto menu = Menu::create(jiantou, mathImage, chineseImage, englishImage, NULL);
	menu->setPosition(Vec2::ZERO);*/
	return true;
}

void MathScene::onClickJiantouCallBack(cocos2d::Ref* english) {
	Director::getInstance()->popScene();
}