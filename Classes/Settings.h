#ifndef __Settings__
#define __Settings__

#include "cocos2d.h"

class Settings : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuJiantouCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Settings);
};

#endif // __HELLOWORLD_SCENE_H__