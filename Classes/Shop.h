#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"
#include "json/rapidjson.h"
#include "ShopItem.h"

class Shop : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void ShowFlower(cocos2d::Layer* layer,cocos2d::TMXTiledMap* map1, cocos2d::TMXTiledMap* map2, cocos2d::TMXTiledMap* map3);
	// a selector callback
	void menuJiantouCallback(cocos2d::Ref* pSender);

	void getShopItem(cocos2d::Layer* layer, cocos2d::TMXTiledMap* map);

	void RequesetCallBack(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response, cocos2d::Layer* layer, cocos2d::TMXTiledMap* map);

	void getFlowerImage(cocos2d::Layer* layer, cocos2d::TMXTiledMap* map, std::vector<ShopItem> shopItem);

	void getFlowerImageCallBack(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response,cocos2d::Layer* layer1, cocos2d::TMXTiledMap* map,std::string name);

	// implement the "static create()" method manually
	CREATE_FUNC(Shop);
};

#endif // __HELLOWORLD_SCENE_H__