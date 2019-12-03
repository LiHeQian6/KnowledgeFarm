
#ifndef __MATH_SCENE_H__
#define __MATH_SCENE_H__

#include "cocos2d.h"

class MathScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onClickJiantouCallBack(cocos2d::Ref* english);
	// implement the "static create()" method manually
	CREATE_FUNC(MathScene);
};

#endif // __MATH_SCENE_H__
