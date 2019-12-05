#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "MathScene.h"
#include "cocos2d/cocos/network/HttpRequest.h"
#include "cocos2d/cocos/network/HttpClient.h"
#include "cocos2d/cocos/network/HttpResponse.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "Questions.h"
#include <iostream>
USING_NS_CC;

Scene* MathScene::createScene() {
	return MathScene::create();
}

bool MathScene::init() {

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 orgin = Director::getInstance()->getVisibleOrigin();

	auto backGround = Sprite::create("background.png");
	backGround->setAnchorPoint(Vec2::ZERO);
	backGround->setScaleX(visibleSize.width / backGround->getContentSize().width);
	backGround->setScaleY(visibleSize.height / backGround->getContentSize().height);
	backGround->setPosition(Vec2(orgin.x, orgin.y));
	addChild(backGround, 0);

	auto goBack = MenuItemImage::create("jiantou.png", "jiantou.png", CC_CALLBACK_1(MathScene::onClickJiantouCallBack, this));
	goBack->setAnchorPoint(Vec2(0, 0));
	goBack->setScale(visibleSize.width * 0.1 / goBack->getContentSize().width);
	goBack->setPosition(Vec2(orgin.x + visibleSize.width * 0.03, orgin.y + visibleSize.height * 0.80));
	auto menu = Menu::create(goBack,NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu,10);
	getQuestions();
	return true;
}

void MathScene::onClickJiantouCallBack(cocos2d::Ref* english) {
	Director::getInstance()->popScene();
}
void MathScene::getQuestions() {
	// ͨ�����ʵ�ַ���õ�����ֵ�ڸ�label
		// �������������һ�����󣨿�ʼ����һ������
	auto* request = new cocos2d::network::HttpRequest;
	// ����������url��ַ
	request->setUrl("http://10.7.87.220:8080/FarmKnowledge/answer/OneUpMath"); // �����http://Э��д�ϣ�����cocos��֧��http��������Ҫ�����ã��������ϸ˵
	// ���������������ͣ�get�����õ����ݣ�post�Ƿ��ͱ�����
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	// ��һ������Ϊ��������Ķ���, �ڶ�������Ϊ��������Ļ�ִ���������HttpResponse����
	request->setResponseCallback(CC_CALLBACK_2(MathScene::HttpRequestCompleted,this));
	cocos2d::network::HttpClient::getInstance()->send(request);
}
void MathScene::HttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response) {
	// ���������Ƿ�������������
	if (!response->isSucceed()) return;
	std::vector<Questions> questions;
	std::vector <char>* vec = response->getResponseData();
	std::string str_json(vec->begin(), vec->end());
	CCLOG("%s\n", str_json.c_str());
	rapidjson::Document document;
	document.Parse<0>(str_json.c_str());
	if (document.HasParseError()) { //��ӡ��������
		CCLOG("GetParseError %s\n", document.GetParseError());
	}
	if (document.IsArray()) {
		auto doc = document.GetArray();
		for (int i = 0; i<doc.Size(); i++)
		{
			Questions q(doc[i]["num1"].GetInt(), doc[i]["signal1"].GetString(), doc[i]["num2"].GetInt(), doc[i]["signal2"].GetString(), doc[i]["num3"].GetInt(), doc[i]["result"].GetInt());
			
			questions.push_back(q);
		};
	}
	std::string str = questions.at(0).getQuestion();
	showQuestion(str);
}
void MathScene::showQuestion(std::string str) {
	auto q = Label::createWithTTF(str, "fonts/font.ttf", 10);
	q->setPosition(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2);
	this->addChild(q,10);

}
std::string Questions::getQuestion() {
	std::string str = std::to_string(num1) + signal1 + std::to_string(num2);
	if (signal2!="") {
		str = str + signal2 + std::to_string(num3);
	}
	str += "=";
	return str;
}
int Questions::getAnswer() {
	return result;
}