#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Learn.h"
#include "Shop.h"
#include "Settings.h"
#include "network/HttpClient.h"
#include "Math.h"
USING_NS_CC;

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma execution_character_set("utf-8")
#endif
#include <cocos\editor-support\spine\extension.h>
using namespace ui;
using namespace cocos2d::network;
using namespace std;


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

	menuLayer(visibleSize,origin);
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
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);
	auto dog = Sprite::create("dog.png");
	dog->setScale(visibleSize.height * 1 / 5 / dog->getContentSize().height);
	dog->setPosition(origin.x+visibleSize.width*0.9, origin.y+visibleSize.height*0.15);
	addChild(dog,2);
	createUserInfoLayer(visibleSize, origin);
    return true;
}

//void Main::sendHttpRequest() {
//	auto request = new HttpRequest();
//	string str = "你好！";
//	string info = string_To_UTF8(str);
//	request->setUrl("http://10.7.87.219:8080/COCOTest/TestServlet?info=123");
//	request->setRequestType(HttpRequest::Type::GET);
//	request->setResponseCallback(CC_CALLBACK_2(Main::HttpRequestCallBack, this));
//	HttpClient::getInstance()->sendImmediate(request);
//	request->release();
//}


// string Main::string_To_UTF8(const std::string& str)
//{
//	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
//	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
//	ZeroMemory(pwBuf, nwLen * 2 + 2);
//	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
//	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
//	char* pBuf = new char[nLen + 1];
//	ZeroMemory(pBuf, nLen + 1);
//	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
//	std::string retStr(pBuf);
//	delete[]pwBuf;
//	delete[]pBuf;
//	pwBuf = NULL;
//	pBuf = NULL;
//	return retStr;
//}
//
//void Main::HttpRequestCallBack(HttpClient* client, HttpResponse* response) {
//	if (!response) {
//		return;
//	}
//	auto info = response->getResponseData();
//	for (unsigned int i = 0; i < info->size(); i++)
//	{
//		log("% c", (*info)[i]);
//	}
//}

bool Main::OnTouch(Touch* touch, Event* event,TMXTiledMap* map) {
	Size visiblesize = Director::sharedDirector()->getVisibleSize();
	//// 获取点击的openGL坐标
	auto touchPos = touch->getLocation();
	//CCLOG("TOUCH");
	TMXLayer* layer1 = map->getLayer("map1");
	////cocos是默认用opengl 坐标（左下角开始） tmx 用的是格子坐标(左上角开始) 这里做转换(重点)
	//Size mapSize = map->getMapSize();//获取地图总大小
	//Size tileSize = map->getTileSize();//获取格子大小
	//auto size = tileSize.width * visiblesize.height * 0.38 / map->getContentSize().height;
	//int x = (touchPos.x-visiblesize.width*0.4) / (tileSize.width / 1.2);//格子坐标x
	////int y = (mapSize.height * tileSize.height - touchPos.y) / tileSize.height;//格子坐标y
	//int y = (visiblesize.height - touchPos.y) / tileSize.height * visiblesize.height * 0.38 / map->getContentSize().height;
	//// 计算当前缩放下，每块瓦片的长宽

	/*CCTMXTiledMap* map = (CCTMXTiledMap*)getChildByTag();*/
	//int tilewidth = map->getTileSize().width * visiblesize.height * 0.38 / map->getContentSize().height / 1.2;
	//int tilehigh = map->getTileSize().height * visiblesize.height * 0.38 / map->getContentSize().height / 1.2;
	auto a = map->getPosition().x;
	auto b = touchPos.x;
	auto my = map->getPosition().y;
	auto py = touchPos.y;
	//float mapOrginX = (map->getContentSize().width / 2) *visiblesize.height * 0.38 / map->getContentSize().height- visiblesize.width * 2 / 5;
	//float mapOrginy = visiblesize.height * 3 / 7 - (map->getContentSize().height / 2)* visiblesize.height * 0.38 / map->getContentSize().height;
	////O为地图的原点，A是要求的点，oa向量的值  
	//float OA_x = touchPos.x - mapOrginX;
	//float OA_y = touchPos.y - mapOrginy;
	////假设以地图的原点为初始坐标（正上方那个点），对应的所示点的坐标值为m,n  
	////将地图坐标(m,n)转为标准坐标，则有：  
	////(x,y)-(mapOrginX,mapOrginy)=m(tilewidth/2,-tilehigh/2)+n(-tilewidth/2,-tilehigh/2)  
	////因此m=(OA_x/(tilewidth/2)+OA_y/(-tilehigh/2)/2=OA_x/tilewidth-OA_y/tilehigh  
	////n=(OA_y/(-tilehigh/2)-OA_x/(tilewidth/2))/2=-(OA_y/tilehigh+OA_x/tilewidth)  
	//float m = OA_x / tilewidth;
	//float n = OA_y / tilehigh;
	//if (m < 0) m = 0;
	//if (n < 0) n = 0;
	//if (m > map->getMapSize().width - 1) m = map->getMapSize().width - 1;
	//if (n > map->getMapSize().height - 1) n = map->getMapSize().height - 1;
	//layer1->setTileGID(0, Vec2((int)m, (int)n));//设置为0就置空了
	//log("%d  %d", (int)m, (int)n);
	//log("%f  %f", a, b);
	log("%f  %f", a, my);
	Point react = ccp(map->getPosition().x, map->getPosition().y);
	CCPoint pos = ccpSub(touchPos, react);
	log("%f  %f", react.x, react.y);
	float halfMapWidth = map->getMapSize().width * 0.5f;
	float mapHeight = map->getMapSize().height;
	float tileWidth = map->getTileSize().width;
	float tileHeight = map->getTileSize().height;

	CCPoint tilePasDiv = ccp(pos.x / tileWidth, pos.y / tileHeight);
	float inverseTileY = mapHeight - tilePasDiv.y;
	float posX = (int)(inverseTileY + tilePasDiv.x - halfMapWidth);
	float posY = (int)(inverseTileY - tilePasDiv.x + halfMapWidth);

	posX = MAX(0, posX);
	posX = MIN(map->getMapSize().width - 1, posX);
	posY = MAX(0, posY);
	posY = MIN(map->getMapSize().height - 1, posY);
	 
	//getPositionForStaggeredAt(pos);
	layer1->setTileGID(0, Vec2(posX, posY));
	return true;
}

void Main::ShowFlowerInBag(TMXTiledMap *map,Layer* layer) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto maplayer = map->getObjectGroup("flower");
	auto ob1 = maplayer->getObject("flower1");
	auto flower = Button::create("meigui.png");
	auto mapScale = visibleSize.height * 0.94 / map->getContentSize().height;
	auto scale = visibleSize.height * 0.15 / flower->getContentSize().height;
	flower->setAnchorPoint(Vec2(0, 0));
	flower->setScale(scale);
	auto width = visibleSize.width;
	auto mapc = map->getContentSize().width* mapScale;
	auto x = origin.x+visibleSize.width - map->getContentSize().width * mapScale * 0.9;
	auto y = origin.y + map->getContentSize().height * 0.7;
	flower->setPosition(Vec2(
		origin.x+ visibleSize.width - map->getContentSize().width*mapScale*0.95, 
		origin.y+ map->getContentSize().height * mapScale *0.86));
	layer->addChild(flower, 12);
}

/*创建背包层*/
void Main::CreateBagLayer(Size visibleSize, Vec2 origin,Layer * layer) {
	//sendHttpRequest();
	auto BagMap = TMXTiledMap::create("bag.tmx");
	auto Close = Button::create("close.png");
	auto scale = visibleSize.height*0.94 / BagMap->getContentSize().height;
	auto CloaseScale = visibleSize.height*0.25 / Close->getContentSize().height;
	BagMap->setAnchorPoint(Vec2(0, 0));
	BagMap->setScale(scale);
	BagMap->setPosition(origin.x + visibleSize.width- BagMap->getContentSize().width * scale, origin.y+visibleSize.height*0.04);
	Close->setAnchorPoint(Vec2(0, 0));
	Close->setScale(CloaseScale);
	Close->setPosition(Vec2(origin.x + visibleSize.width - BagMap->getContentSize().width * scale*1.055, origin.y + visibleSize.height * 0.42));
	Close->addClickEventListener(CC_CALLBACK_1(Main::onclickCloseCallBack,this, layer));
	layer->addChild(BagMap, 10);
	layer->addChild(Close, 11);
	ShowFlowerInBag(BagMap,layer);
}

/*创建用户信息层*/
void Main::createUserInfoLayer(Size visibleSize, Vec2 origin) {
	auto userInfo = Layer::create();
	//头像
	auto photo = Sprite::create("photo.png");
	photo->setScale(visibleSize.height * 1 / 8 / photo->getContentSize().height);
	photo->setPosition(origin.x + visibleSize.width * 0.05, origin.y + visibleSize.height * 0.9);
	userInfo->addChild(photo);
	//昵称
	auto nickName = Label::createWithTTF(u8"昵称 ", "fonts/font.ttf", 16);
	nickName->setPosition(origin.x + visibleSize.width * 0.1, origin.y + visibleSize.height * 0.92);
	nickName->setAnchorPoint(Vec2(0, 0));
	nickName->setColor(Color3B::BLACK);
	userInfo->addChild(nickName);
	//id
	auto account = Label::createWithTTF(u8"id:15246546", "fonts/font.ttf", 10);
	account->setColor(Color3B::BLACK);
	account->setPosition(origin.x + visibleSize.width * 0.1, origin.y + visibleSize.height * 0.83);
	account->setAnchorPoint(Vec2(0, 0));
	userInfo->addChild(account);
	//等级
	auto lv = Label::createWithTTF("lv: 60", "fonts/font.ttf", 10);
	lv->setColor(Color3B::BLACK);
	lv->setPosition(origin.x + visibleSize.width * 0.1, origin.y + visibleSize.height * 0.9);
	lv->setAnchorPoint(Vec2(0, 0));
	userInfo->addChild(lv);
	//金币
	auto money = Label::createWithTTF(u8"金币:60 ", "fonts/font.ttf", 10);
	money->setColor(Color3B::BLACK);
	money->setPosition(origin.x + visibleSize.width * 0.17, origin.y + visibleSize.height * 0.9);
	money->setAnchorPoint(Vec2(0, 0));
	userInfo->addChild(money);
	//经验条框
	auto progress = Sprite::create("progressempty.png");
	progress->setPosition(origin.x + visibleSize.width * 0.1, origin.y + visibleSize.height * 0.86);
	progress->setAnchorPoint(Vec2(0, 0));
	progress->setScale(visibleSize.width * 1 / 8 / progress->getContentSize().width);
	userInfo->addChild(progress);
	//经验条
	cocos2d::ui::LoadingBar* experienceBar = cocos2d::ui::LoadingBar::create("progressfull.png");
	experienceBar->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
	experienceBar->setPosition(Vec2(visibleSize.width * 0.1, origin.y + visibleSize.height * 0.86));
	experienceBar->setAnchorPoint(Vec2(0,0));
	experienceBar->setScale(origin.x + visibleSize.width * 1 /8 / experienceBar->getContentSize().width);
	experienceBar->setPercent(100);
	userInfo->addChild(experienceBar);
	//经验值
	auto experience = Label::createWithTTF(u8"20/100 ", "fonts/font.ttf", 8);
	experience->setColor(Color3B::BLACK);
	experience->setPosition(Vec2(origin.x + visibleSize.width * 0.14, origin.y + visibleSize.height * 0.865));
	experience->setAnchorPoint(Vec2(0, 0));
	userInfo->addChild(experience);

	addChild(userInfo);
}

/*菜单层*/
void Main::menuLayer(Size visibleSize, Vec2 origin)
{
	auto bagLayer = Layer::create();
	this->addChild(bagLayer, 5);

	auto learn = MenuItemImage::create(
		"learn.png",
		"learn.png",
		CC_CALLBACK_1(Main::intoLearnPageCallback, this));
	learn->setScale(visibleSize.width / 6 / learn->getContentSize().width);
	float x = origin.x + visibleSize.width * 1 / 10;
	float y = origin.y + visibleSize.height / 8;
	learn->setPosition(Vec2(x, y));

	auto kettle = MenuItemImage::create(
		"shuihu.png",
		"shuihu.png",
		CC_CALLBACK_1(Main::menuCloseCallback, this));
	kettle->setScale(visibleSize.width / 14 / kettle->getContentSize().width);
	kettle->setAnchorPoint(Vec2(0.4, 0.5));
	x = origin.x + visibleSize.width * 5 / 20;
	y = origin.y + visibleSize.height / 12;
	kettle->setPosition(Vec2(x, y));
	//水壶角标
	auto kettleNum = Label::createWithTTF("16", "fonts/font.ttf",5);
	kettleNum->setAnchorPoint(Vec2(0,1));
	kettleNum->setTextColor(Color4B::BLACK);
	kettleNum->setPosition(Vec2(kettle->getContentSize().width*2/3, kettle->getContentSize().height*1.2));
	kettle->addChild(kettleNum,5);


	auto fertilizer = MenuItemImage::create(
		"huafei.png",
		"huafei.png",
		CC_CALLBACK_1(Main::menuCloseCallback, this));
	fertilizer->setScale(visibleSize.width / 18 / fertilizer->getContentSize().width);
	x = origin.x + visibleSize.width * 7 / 20;
	y = origin.y + visibleSize.height / 12;
	fertilizer->setPosition(Vec2(x, y));
	//化肥角标
	auto fertilizerNum = Label::createWithTTF("16", "fonts/font.ttf", 6);
	fertilizerNum->setAnchorPoint(Vec2(0, 1));
	fertilizerNum->setTextColor(Color4B::BLACK);
	fertilizerNum->setPosition(Vec2(fertilizer->getContentSize().width * 2 / 3, fertilizer->getContentSize().height*1.1));
	fertilizer->addChild(fertilizerNum, 5);


	auto beibao = MenuItemImage::create(
		"beibao.png",
		"beibao.png",
		CC_CALLBACK_1(Main::onclickBagCallback, this, visibleSize, origin, bagLayer));
	beibao->setScale(visibleSize.width / 18 / beibao->getContentSize().width);
	x = origin.x + visibleSize.width * 9 / 20;
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
	y = origin.y + visibleSize.height * 11 / 12;
	pet->setPosition(Vec2(x, y));

	auto shop = MenuItemImage::create(
		"shop.png",
		"shop.png",
		CC_CALLBACK_1(Main::intoShopPageCallback, this));
	shop->setScale(visibleSize.width / 18 / shop->getContentSize().width);
	x = origin.x + visibleSize.width * 16 / 20;
	y = origin.y + visibleSize.height * 11 / 12;
	shop->setPosition(Vec2(x, y));

	auto menu = Menu::create(learn, kettle, fertilizer, beibao, shop, pet, setting, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

/*点击背包回调函数*/
void Main::onclickBagCallback(cocos2d::Ref* pSender,Size visibleSize, Vec2 origin,Layer* layer) {
	if (layer->getChildrenCount() == 0)
		CreateBagLayer(visibleSize, origin, layer);
	else
		layer->removeAllChildren();
}

/*点击关闭回调函数*/
void Main::onclickCloseCallBack(Ref* pSender,Layer* layer) {
	layer->removeAllChildren();
}

/*进入学习入口页面*/
void Main::intoLearnPageCallback(Ref* pSender) {
	Director::getInstance()->pushScene(Learn::createScene());
}

/*进入商店页面*/
void Main::intoShopPageCallback(Ref* pSender) {
	Director::getInstance()->pushScene(Shop::createScene());
}

/*进入设置页面*/
void Main::intoSettingsCallback(cocos2d::Ref* pSender) {
	Director::getInstance()->pushScene(Settings::createScene());
}
void Main::menuCloseCallback(cocos2d::Ref* pSender) {
	
}