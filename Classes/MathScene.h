
#ifndef __MATH_SCENE_H__
#define __MATH_SCENE_H__

#include "cocos2d.h"
#include "cocos2d/cocos/network/HttpClient.h"
USING_NS_CC;
class MathScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void getQuestions();
	void onClickJiantouCallBack(cocos2d::Ref* english);
	// implement the "static create()" method manually
	void setQuestion(std::string str);
	void HttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
	CREATE_FUNC(MathScene);
};

#endif // __MATH_SCENE_H__
