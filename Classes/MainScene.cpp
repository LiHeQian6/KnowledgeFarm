#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Learn.h"
#include "Shop.h"
#include "Settings.h"
USING_NS_CC;

Scene* Main::createScene()
{
    return Main::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Main::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	auto learn = MenuItemImage::create(
		"learn.png",
		"learn.png",
		CC_CALLBACK_1(Main::intoLearnPageCallback, this));
	learn->setScale(visibleSize.width/6/ learn->getContentSize().width);
	float x = origin.x + visibleSize.width * 1 / 10;
	float y = origin.y + visibleSize.height/8;
	learn->setPosition(Vec2(x, y));

	auto shuihu = MenuItemImage::create(
		"shuihu.png",
		"shuihu.png",
		CC_CALLBACK_1(Main::menuCloseCallback, this));
	shuihu->setScale(visibleSize.width / 14 / shuihu->getContentSize().width);
	shuihu->setAnchorPoint(Vec2(0.4, 0.5));
	x = origin.x + visibleSize.width * 5/20;
	y = origin.y + visibleSize.height / 12;
	shuihu->setPosition(Vec2(x, y));

    auto huafei = MenuItemImage::create(
        "huafei.png",
        "huafei.png",
        CC_CALLBACK_1(Main::menuCloseCallback, this));
	huafei->setScale(visibleSize.width / 18 / huafei->getContentSize().width);
	x = origin.x + visibleSize.width *7/20;
	y = origin.y + visibleSize.height / 12;
	huafei->setPosition(Vec2(x,y));

	auto beibao = MenuItemImage::create(
		"beibao.png",
		"beibao.png",
		CC_CALLBACK_1(Main::menuCloseCallback, this));
	beibao->setScale(visibleSize.width / 18 /beibao->getContentSize().width);
	x = origin.x + visibleSize.width * 9/20;
	y = origin.y + visibleSize.height / 12;
	beibao->setPosition(Vec2(x, y));

	auto setting = MenuItemImage::create(
		"setting.png",
		"setting.png",
		CC_CALLBACK_1(Main::intoSettingsCallback, this));
	setting->setScale(visibleSize.width / 18 / setting->getContentSize().width);
	x = origin.x + visibleSize.width * 18 / 19;
	y = origin.y + visibleSize.height * 11 / 12;
	setting->setPosition(Vec2(x, y));

	auto pet = MenuItemImage::create(
		"chongwu.png",
		"chongwu.png",
		CC_CALLBACK_1(Main::menuCloseCallback, this));
	pet->setScale(visibleSize.width / 18 / pet->getContentSize().width);
	x = origin.x + visibleSize.width * 21 / 24;
	y = origin.y + visibleSize.height*11 / 12;
	pet->setPosition(Vec2(x, y));

	auto shop = MenuItemImage::create(
		"shop.png",
		"shop.png",
		CC_CALLBACK_1(Main::intoShopPageCallback, this));
	shop->setScale(visibleSize.width / 18 / shop->getContentSize().width);
	x = origin.x + visibleSize.width * 16 / 20;
	y = origin.y + visibleSize.height * 11 / 12;
	shop->setPosition(Vec2(x, y));

    auto menu = Menu::create(learn,shuihu,huafei,beibao,shop,pet,setting, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto background = Sprite::create("back.png");
    // position the sprite on the center of the screen
	background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	background->setContentSize(visibleSize);
    // add the sprite as a child to this layer
    this->addChild(background, 0);

	auto map = TMXTiledMap::create("land.tmx");
	map->setAnchorPoint(Vec2(0.45,0.5));
	map->setScale(visibleSize.height *0.38/ map->getContentSize().height);
	map->setPosition(origin.x+visibleSize.width*2/5,origin.y+ visibleSize.height*3/7);
	addChild(map,1);
	
	auto dog = Sprite::create("dog.png");
	dog->setScale(visibleSize.height * 1 / 5 / dog->getContentSize().height);
	dog->setPosition(origin.x+visibleSize.width*0.9, origin.y+visibleSize.height*0.15);
	addChild(dog,2);

	auto userInfo = Layer::create();
	auto photo = Sprite::create("photo.png");
	photo->setScale(visibleSize.height * 1 / 8 / photo->getContentSize().height);
	photo->setPosition(origin.x + visibleSize.width * 0.1, origin.y + visibleSize.height * 0.9);
	userInfo->addChild(photo);

	auto nickName = Label::createWithTTF("nickName", "fonts/arial.ttf", 16);
	nickName->setPosition(origin.x + visibleSize.width * 0.15, origin.y + visibleSize.height * 0.92);
	nickName->setAnchorPoint(Vec2(0, 0));
	nickName->setColor(Color3B::BLACK);
	userInfo->addChild(nickName);

	auto account = Label::createWithTTF("account:15246546", "fonts/arial.ttf", 10);
	account->setColor(Color3B::BLACK);
	account->setPosition(origin.x + visibleSize.width * 0.15, origin.y + visibleSize.height * 0.85);
	account->setAnchorPoint(Vec2(0, 0));
	userInfo->addChild(account);

	auto lv = Label::createWithTTF("lv: 60", "fonts/arial.ttf", 10);
	lv->setColor(Color3B::BLACK);
	lv->setPosition(origin.x + visibleSize.width * 0.15, origin.y + visibleSize.height * 0.88);
	lv->setAnchorPoint(Vec2(0, 0));
	userInfo->addChild(lv);

	auto money = Label::createWithTTF("money: 60", "fonts/arial.ttf", 10);
	money->setColor(Color3B::BLACK);
	money->setPosition(origin.x + visibleSize.width * 0.22, origin.y + visibleSize.height * 0.88);
	money->setAnchorPoint(Vec2(0, 0));
	userInfo->addChild(money);

	/*cocos2d::ui::LoadingBar* loadingBar = cocos2d::ui::LoadingBar::create("progress.png");
	loadingBar->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
	loadingBar->setPosition(Vec2(111,111));
	loadingBar->setScale(0.1f);
	loadingBar->setPercent(100);
	userInfo->addChild(loadingBar);*/

	addChild(userInfo);

    return true;
}

void Main::intoLearnPageCallback(Ref* pSender) {
	Director::getInstance()->pushScene(TransitionMoveInL::create(0.3, Learn::createScene()));
}

void Main::intoShopPageCallback(Ref* pSender) {
	Director::getInstance()->pushScene(TransitionMoveInL::create(0.3, Shop::createScene()));
}

void Main::intoSettingsCallback(cocos2d::Ref* pSender) {
	Director::getInstance()->pushScene(TransitionMoveInL::create(0.3, Settings::createScene()));
}

void Main::menuCloseCallback(Ref* pSender)
{

}
