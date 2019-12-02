#include "Learn.h"
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"

USING_NS_CC;

Scene* Learn::createScene() {

	return Learn::create();
}

bool Learn::init() {

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 orgin = Director::getInstance()->getVisibleOrigin();
	auto vect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	auto glView = Director::getInstance()->getOpenGLView();
	auto frameSize = glView->getFrameSize();

	auto layer = Layer::create();
	layer->setAnchorPoint(Vec2::ZERO);
	addChild(layer, 1);

	auto layer1 = Layer::create();
	addChild(layer1, 2);

	auto learnBack = Sprite::create("learnBack.png");
	learnBack->setAnchorPoint(Vec2::ZERO);
	learnBack->setScaleX(visibleSize.width / learnBack->getContentSize().width);
	learnBack->setScaleY(visibleSize.height / learnBack->getContentSize().height);
	/*learnBack->setScale(vect.size.height / learnBack->getContentSize().height);*/
	learnBack->setPosition(Vec2(orgin.x, orgin.y));
	layer->addChild(learnBack, 1);

	auto mathImage = MenuItemImage::create("math.png", "math.png", CC_CALLBACK_1(Learn::onClickMathCallBack, this));
	mathImage->setAnchorPoint(Vec2(0, 0));
	mathImage->setScale(visibleSize.width * 0.1 / mathImage->getContentSize().width);
	mathImage->setPosition(Vec2((orgin.x + visibleSize.width * 0.6) / 2, (orgin.y + visibleSize.height ) / 2));
	layer1->addChild(mathImage, 1);
	auto chineseImage = MenuItemImage::create("chinese.png", "chinese.png", CC_CALLBACK_1(Learn::onClickChineseCallBack, this));
	chineseImage->setAnchorPoint(Vec2(0, 0));
	chineseImage->setScale(visibleSize.width * 0.1 / chineseImage->getContentSize().width);
	chineseImage->setPosition(Vec2((orgin.x + visibleSize.width * 1.245) / 2, (orgin.y + visibleSize.height) / 2));
	layer1->addChild(chineseImage, 3);

	auto englishImage = MenuItemImage::create("english.png", "chinese.png", CC_CALLBACK_1(Learn::onClickEnglishCallBack, this));
	englishImage->setAnchorPoint(Vec2::ZERO);
	englishImage->setScale(visibleSize.width * 0.1 / englishImage->getContentSize().width);
	englishImage->setPosition(Vec2((orgin.x + visibleSize.width * 0.92) / 2, (orgin.y + visibleSize.height) / 2));
	layer1->addChild(englishImage, 2);

	auto jiantou = MenuItemImage::create("jiantou.png", "jiantou.png", CC_CALLBACK_1(Learn::onClickJiantouCallBack, this));
	jiantou->setAnchorPoint(Vec2(0, 0));
	jiantou->setScale(visibleSize.width * 0.1 / jiantou->getContentSize().width);
	jiantou->setPosition(Vec2(orgin.x + visibleSize.width * 0.03, orgin.y + visibleSize.height * 0.80));

	auto menu = Menu::create(jiantou, NULL);
	menu->setPosition(Vec2::ZERO);
	layer1->addChild(menu, 2);

	return true;
}

void Learn::onClickJiantouCallBack(cocos2d::Ref* english) {
	Director::getInstance()->popScene();
}

void Learn::onClickMathCallBack(cocos2d::Ref* math) {

}

void Learn::onClickChineseCallBack(cocos2d::Ref* chinese) {

}

void Learn::onClickEnglishCallBack(cocos2d::Ref* english) {

}