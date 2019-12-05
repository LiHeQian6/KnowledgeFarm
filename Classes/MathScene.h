
#ifndef __MATH_SCENE_H__
#define __MATH_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "Questions.h"
USING_NS_CC;
class MathScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	int i=0;//当前是第几道题
	std::vector<Questions> q;//题目列表
	virtual bool init();
	void getQuestions();
	void onClickJiantouCallBack(cocos2d::Ref* english);
	// implement the "static create()" method manually
	void showQuestion();
	void nextQuestion();
	void HttpRequestCompleted(network::HttpClient* sender, network::HttpResponse* response);
	CREATE_FUNC(MathScene);
};

#endif // __MATH_SCENE_H__
