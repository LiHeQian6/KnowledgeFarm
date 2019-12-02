#ifndef _Learn_
#define _Learn_

#pragma once
#include "cocos2d.h"

class Learn : public cocos2d::Scene {

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void onClickMathCallBack(cocos2d::Ref* math);

	void onClickChineseCallBack(cocos2d::Ref* chinese);

	void onClickEnglishCallBack(cocos2d::Ref* english);
	CREATE_FUNC(Learn);
};
#endif
