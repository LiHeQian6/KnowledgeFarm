
#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class Main : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void createUserInfoLayer(cocos2d::Size visibleSize, cocos2d::Vec2 origin);
	void menuLayer(cocos2d::Size visibleSize, cocos2d::Vec2 origin);
	void CreateBagLayer(cocos2d::Size visibleSize, cocos2d::Vec2 origin,cocos2d::Layer* layer);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void onclickCloseCallBack(cocos2d::Ref* pSender,cocos2d::Layer* layer);

	void intoLearnPageCallback(cocos2d::Ref* pSender);

	void intoShopPageCallback(cocos2d::Ref* pSender);

	void intoSettingsCallback(cocos2d::Ref* pSender);

	void onclickBagCallback(cocos2d::Ref* pSender,cocos2d::Size size,cocos2d::Vec2 orign,cocos2d::Layer* layer);
    // implement the "static create()" method manually
    CREATE_FUNC(Main);
};

#endif // __MAIN_SCENE_H__
