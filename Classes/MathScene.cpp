#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "MathScene.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "Questions.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "extensions\cocos-ext.h"
USING_NS_CC;

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma execution_character_set("utf-8")
#endif
#include <cocos\ui\UIScale9Sprite.cpp>

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

	auto backGround = Sprite::create("mathbg.png");
	backGround->setAnchorPoint(Vec2::ZERO);
	backGround->setScaleX(visibleSize.width / backGround->getContentSize().width);
	backGround->setScaleY(visibleSize.height / backGround->getContentSize().height);
	backGround->setPosition(Vec2(orgin.x, orgin.y));
	addChild(backGround, 0);

	auto goBack = MenuItemImage::create("jiantou.png", "jiantou.png", CC_CALLBACK_1(MathScene::onClickJiantouCallBack, this));
	goBack->setAnchorPoint(Vec2(0, 0));
	goBack->setScale(visibleSize.width * 0.06 / goBack->getContentSize().width);
	goBack->setPosition(Vec2(orgin.x + visibleSize.width * 0.03, orgin.y + visibleSize.height * 0.90));
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
	// 通过访问地址，得到返回值在改label
		// 设置网络请求的一个对象（开始整理一个请求）
	auto* request = new cocos2d::network::HttpRequest;
	// 给对象设置url地址
	request->setUrl("http://10.7.87.222:8080/FarmKnowledge/answer/OneUpMath"); // 必须把http://协议写上，但是cocos不支持http，这里需要改设置，下面会详细说
	// 设置网络请求类型，get仅仅得到数据，post是发送表单数据
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	// 第一个参数为网络请求的对象, 第二个参数为网络请求的回执，被打包成HttpResponse类型
	request->setResponseCallback(CC_CALLBACK_2(MathScene::HttpRequestCompleted,this));
	cocos2d::network::HttpClient::getInstance()->send(request);
}
void MathScene::HttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response) {
	// 网络请求是否正常返回数据
	if (!response->isSucceed()) return;
	std::vector <char>* vec = response->getResponseData();
	std::string str_json(vec->begin(), vec->end());
	CCLOG("%s\n", str_json.c_str());
	rapidjson::Document document;
	document.Parse<0>(str_json.c_str());
	if (document.HasParseError()) { //打印解析错误
		CCLOG("GetParseError %u\n", document.GetParseError());
	}
	if (document.IsArray()) {
		auto doc = document.GetArray();
		for (int i = 0; i<doc.Size(); i++)
		{
			Questions q(doc[i]["num1"].GetInt(), doc[i]["signal1"].GetString(), doc[i]["num2"].GetInt(), doc[i]["signal2"].GetString(), doc[i]["num3"].GetInt(), doc[i]["result"].GetInt());
			MathScene::q.push_back(q);
		};
	}
	showQuestion();
}
void MathScene::showQuestion() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 orgin = Director::getInstance()->getVisibleOrigin();
	auto text = Label::createWithTTF("", "fonts/font.ttf", 50);
	text->setString(q.at(i).getQuestion());
	text->setTag(1);
	auto textField = cocos2d::extension::EditBox::create(Size(200, 35), Scale9Sprite::create("editbox.png"));
	textField->setTag(2);
	text->setPosition(orgin.x + visibleSize.width*4/7,orgin.y + visibleSize.height*3/5);
	text->setAnchorPoint(Vec2(1,0.5));
	textField->setPosition(Vec2(orgin.x + visibleSize.width *4/7, orgin.y + visibleSize.height*3 /5));
	textField->setAnchorPoint(Vec2(0,0.5));
	textField->setFont("fonts/font.ttf",50);
	textField->setContentSize(Size(80,50));
	textField->setMaxLength(3);
	textField->setInputMode(EditBox::InputMode::DECIMAL);
	this->addChild(text,10);
	this->addChild(textField,15); 

	auto next = Button::create();
	next->setTitleLabel(Label::createWithTTF("NEXT","fonts/font.ttf", 30));
	next->setPosition(Vec2(orgin.x + visibleSize.width*2/3, orgin.y + visibleSize.height *2/ 5));
	next->setTitleFontName("fonts/font.ttf");
	next->setTag(3);
	this->addChild(next);
	next->addClickEventListener(CC_CALLBACK_0(MathScene::nextQuestion,this));
}
void MathScene::nextQuestion() {
	Label* text=(Label*)getChildByTag(1);
	EditBox* rs = (EditBox*)getChildByTag(2);
	int r=String::createWithFormat("%s", rs->getText())->intValue(); 
	if (q.at(i).getAnswer() != r) {
		rs->setFontColor(Color3B::RED);
		Sleep(2000);
		rs->setText("");
		rs->setFontColor(Color3B::WHITE);
	}
	else {
		rs->setFontColor(Color3B::GREEN);
		Sleep(2000);
		rs->setText("");
		rs->setFontColor(Color3B::WHITE);
	}
	if (i != q.size() - 1) {
		i++;
		text->setString(q.at(i).getQuestion());
	}
	else {
		i = 0;
		removeChildByTag(1);
		removeChildByTag(3);
		getQuestions();
	}
	
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