/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* Main::createScene()
{
    return Main::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Main::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	auto learn = MenuItemImage::create(
		"learn.png",
		"learn.png",
		CC_CALLBACK_1(Main::menuCloseCallback, this));
	learn->setScale(visibleSize.width/6/ learn->getContentSize().width);
	float x = origin.x + visibleSize.width * 1 / 10;
	float y = origin.y + visibleSize.height/8;
	learn->setPosition(Vec2(x, y));

	auto shuihu = MenuItemImage::create(
		"shuihu.png",
		"shuihu.png",
		CC_CALLBACK_1(Main::menuCloseCallback, this));
	shuihu->setScale(visibleSize.width / 14 / shuihu->getContentSize().width);
	shuihu->setAnchorPoint(Vec2(0.4, 0.5));
	x = origin.x + visibleSize.width * 5/20;
	y = origin.y + visibleSize.height / 12;
	shuihu->setPosition(Vec2(x, y));

    auto huafei = MenuItemImage::create(
        "huafei.png",
        "huafei.png",
        CC_CALLBACK_1(Main::menuCloseCallback, this));
	huafei->setScale(visibleSize.width / 18 / huafei->getContentSize().width);
	x = origin.x + visibleSize.width *7/20;
	y = origin.y + visibleSize.height / 12;
	huafei->setPosition(Vec2(x,y));

	auto beibao = MenuItemImage::create(
		"beibao.png",
		"beibao.png",
		CC_CALLBACK_1(Main::menuCloseCallback, this));
	beibao->setScale(visibleSize.width / 18 /beibao->getContentSize().width);
	x = origin.x + visibleSize.width * 9/20;
	y = origin.y + visibleSize.height / 12;
	beibao->setPosition(Vec2(x, y));

    auto menu = Menu::create(learn,shuihu,huafei,beibao, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto background = Sprite::create("back.png");
    // position the sprite on the center of the screen
	background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	background->setContentSize(visibleSize);
    // add the sprite as a child to this layer
    this->addChild(background, 0);

	auto map = TMXTiledMap::create("land.tmx");
	map->setAnchorPoint(Vec2(0.5,0.5));
	map->setScale(visibleSize.width*4/5/ map->getContentSize().width);
	map->setPosition(origin.x+visibleSize.width*2/5,origin.y+ visibleSize.height*3/7);
	addChild(map,1);
	
	auto pet = Sprite::create("dog.png");
	pet->setScale(visibleSize.height * 1 / 5 / pet->getContentSize().height);
	pet->setPosition(origin.x+visibleSize.width*0.9, origin.y+visibleSize.height*0.15);
	addChild(pet,2);
    return true;
}


void Main::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
