#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class Shop : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void ShowFlower(cocos2d::TMXTiledMap* map);
	// a selector callback
	void menuJiantouCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Shop);
};

#endif // __HELLOWORLD_SCENE_H__