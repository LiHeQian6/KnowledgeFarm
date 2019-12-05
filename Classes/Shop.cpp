#include "Shop.h"
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "Learn.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include <iostream>
#include <ShopItem.h>
using namespace std;

USING_NS_CC;
std::vector<ShopItem> shopItem;
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

	auto map1 = TMXTiledMap::create("ShopMaptmx.tmx");
	map1->setScale(visibleSize.width * 0.87 / map1->getContentSize().width);
	map1->setAnchorPoint(Vec2(0, 0));
	map1->setPosition(Vec2(orgin.x + visibleSize.width * 0.05, orgin.y + visibleSize.height * 0.05));
	layer1->addChild(map1, 1);

	getShopItem(layer1, map1);

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
	ShowFlower(layer1, map1,map2,map3);
	return true;
}

void Shop::ShowFlower(Layer* layer1,TMXTiledMap* map1, TMXTiledMap* map2, TMXTiledMap* map3) {
	Vec2 orgin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int count;
	if (shopItem.size() <= 6) {
		auto layer = map1->getObjectGroup("flower");
		auto tileSize = map1->getTileSize();
		auto ob1 = layer->getObjects();
		count = 1;
		int i = 0;
		for (ValueVector::iterator it = ob1.begin(); it != ob1.end(); it++) {
			if (i < shopItem.size()) {
				Value obj = *it;
				ValueMap map = obj.asValueMap();
				CCLOG("%s", shopItem[i].getName().c_str());
				if (Director::getInstance()->getTextureCache()->getTextureForKey(shopItem[i].getName()) != NULL) {
					auto flower = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(shopItem[i++].getName()));
					flower->setScale(visibleSize.height * 0.15 / flower->getContentSize().height);
					flower->setAnchorPoint(Vec2(0, 0));
					flower->setPosition(Vec2(orgin.x + map.at("x").asFloat() * visibleSize.width * 0.3 / flower->getContentSize().width + visibleSize.height / 6, orgin.y + map.at("y").asFloat() * visibleSize.height * 0.15 / flower->getContentSize().height + visibleSize.height * 0.07 + visibleSize.height * 0.25 * (count - 1)));
					layer1->addChild(flower, 4);
					count++;
				}
			}
			else {
				break;
			}
		}
	}
	/*auto layer = map->getObjectGroup("flower");
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
	}*/

}

void Shop::menuJiantouCallback(Ref* pSender) {
	Director::sharedDirector()->popScene();
}

void Shop::getShopItem(Layer* layer1, TMXTiledMap* map) {
	auto* request = new cocos2d::network::HttpRequest();
	request->setUrl("http://10.7.87.222:8080/FarmKnowledge/crop/initCrop");
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(Shop::RequesetCallBack, this,layer1,map));
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

void Shop::RequesetCallBack(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response, Layer* layer1, TMXTiledMap* map) {
	if (!response->isSucceed()) {
		return;
	}
	std::vector<char>* vec = response->getResponseData();
	std::string str_json(vec->begin(), vec->end());
	CCLOG("%s\n", str_json.c_str());
	rapidjson::Document document;
	document.Parse<0>(str_json.c_str());
	if (document.HasParseError()) {
		CCLOG("GetParseError %s\n", document.GetParseError());
	}
	if (document.IsArray()) {
		auto doc = document.GetArray();
		for (int i = 0; i < doc.Size(); ++i) {
			ShopItem item(
				doc[i]["exist"].GetInt(),
				doc[i]["img3"].GetString(),
				doc[i]["matureTime"].GetInt(),
				doc[i]["price"].GetInt(),
				doc[i]["name"].GetString(),
				doc[i]["id"].GetInt(),
				doc[i]["experience"].GetInt(),
				doc[i]["value"].GetInt(),
				doc[i]["img2"].GetString(),
				doc[i]["img1"].GetString());
			shopItem.push_back(item);
		}
		getFlowerImage(layer1, map, shopItem);
	}
}

void Shop::getFlowerImage(Layer* layer1, TMXTiledMap* map, std::vector<ShopItem> shopItem) {
	auto request = new cocos2d::network::HttpRequest();
	if (Director::getInstance()->getTextureCache()->getTextureForKey(shopItem[0].getName()) == NULL) {
		request->setUrl(shopItem[0].getImage1());
		request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
		request->setResponseCallback(CC_CALLBACK_2(Shop::getFlowerImageCallBack, this, layer1, map, shopItem[0].getName()));
		cocos2d::network::HttpClient::getInstance()->send(request);
	}
	request->release();
}

void Shop::getFlowerImageCallBack(cocos2d::network::HttpClient* sender,cocos2d::network::HttpResponse* response,Layer* layer1, TMXTiledMap* map,std::string name) {
	if (!response->isSucceed())
		return;
	vector<char>* buffer = response->getResponseData();
	CCImage* img = new CCImage;
	img->initWithImageData((unsigned char*)buffer->data(), buffer->size());
	CCTexture2D* texture = new CCTexture2D();
	if (texture->initWithImage(img)) {
		Director::getInstance()->getTextureCache()->addImage(img, name);
	}
	img->release();
}