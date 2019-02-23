#include "MainScene.h"
#include "TollgateScene.h"
#include "MyUtils.h"
#include "iostream"


using namespace std;
USING_NS_CC;

cocos2d::Scene * MainScene::createScene()
{
	return MainScene::create();
}

void MainScene::createUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto mBg1 = Sprite::create("img_bg_logo.jpg");
	Size bgSize1 = mBg1->getContentSize();
	float scaleX1 = visibleSize.width / bgSize1.width;
	float scaleY1 = visibleSize.height / bgSize1.height;
	mBg1->setScaleX(scaleX1);
	mBg1->setScaleY(scaleY1);
	mBg1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(mBg1, 0);

	ValueMap kvMap;
	MyUtils::parserXml("Strings.xml", kvMap);

	auto startBtn = MenuItemImage::create(
		"Button.png",
		"",
		CC_CALLBACK_1(MainScene::start, this));
	startBtn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 200));
	startBtn->setScale(2);
	auto label1 = Label::createWithTTF(kvMap.at("start").asString(), "fonts/msyh.ttc", 20);
	label1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 200));
	this->addChild(label1, 1);

	auto settingBtn = MenuItemImage::create(
		"Button.png",
		"",
		CC_CALLBACK_1(MainScene::setting, this));
	settingBtn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	settingBtn->setScale(2);
	auto label2 = Label::createWithTTF(kvMap.at("setting").asString(), "fonts/msyh.ttc", 20);
	label2->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(label2, 1);

	auto quitBtn = MenuItemImage::create(
		"Button.png",
		"",
		CC_CALLBACK_1(MainScene::quit, this));
	quitBtn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 200));
	quitBtn->setScale(2);
	auto label3 = Label::createWithTTF(kvMap.at("quit").asString(), "fonts/msyh.ttc", 20);
	label3->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 200));
	this->addChild(label3, 1);

	auto menu = Menu::create(startBtn, settingBtn, quitBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 0);
}

bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	createUI();

	return true;
}

void MainScene::start(Ref * pSender)
{
	auto sc = Tollgate::createScene();
	Director::getInstance()->replaceScene(sc);
}

void MainScene::quit(Ref * pSender)
{
	Director::getInstance()->end();
}

void MainScene::setting(Ref * pSender)
{
}
