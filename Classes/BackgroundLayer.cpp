#include "BackgroundLayer.h"
#include "ObjectTag.h"

BackgroundLayer::BackgroundLayer()
{
}
BackgroundLayer::~BackgroundLayer()
{
}

bool BackgroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//±³¾°Í¼Æ¬
	mBg1 = Sprite::create("res/bg/img_bg_level_1.jpg");
	Size bgSize1 = mBg1->getContentSize();
	float scaleX1 = visibleSize.width / bgSize1.width;
	float scaleY1 = visibleSize.height / bgSize1.height;
	mBg1->setScaleX(scaleX1);
	mBg1->setScaleY(scaleY1);
	mBg1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(mBg1);

	mBg2 = Sprite::create("res/bg/img_bg_level_1.jpg");
	Size bgSize2 = mBg2->getContentSize();
	float scaleX2 = visibleSize.width / bgSize2.width;
	float scaleY2 = visibleSize.height / bgSize2.height;
	mBg2->setScaleX(scaleX2);
	mBg2->setScaleY(scaleY2);
	mBg2->setPosition(Point(visibleSize.width / 2, visibleSize.height * 1.5f));
	this->addChild(mBg2);

	auto boder = Sprite::create("boder.png");
	Size boderSize = boder->getContentSize();
	auto boder1 = createBoder(Point(boderSize.width * 0.5f, visibleSize.height / 2));
	this->addChild(boder1);

	auto boder2 = createBoder(Point(visibleSize.width - boderSize.width * 0.5f, visibleSize.height * 0.5f));
	boder2->setFlippedX(true);
	this->addChild(boder2);

	auto boder3 = createBoder(Point(visibleSize.width * 0.5f, visibleSize.height * 0.15f));
	boderSize = boder3->getContentSize();
	boder3->setRotation(90.0f);
	this->addChild(boder3);

	return true;
}

Sprite * BackgroundLayer::createBoder(Point pos)
{
	auto boder = Sprite::create("boder.png");
	
	Size boderSize = boder->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float scaleY = visibleSize.height / boderSize.height;
	//boder->setScaleX(0.1f);
	boder->setScaleY(scaleY);
	auto body = PhysicsBody::createBox(boderSize);
	body->setDynamic(false);
	body->setCategoryBitmask(1);
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);
	boder->setPhysicsBody(body);
	boder->setPosition(pos);
	boder->setTag(ObjectTag_Border);
	return boder;
}

void BackgroundLayer::logic(float dt)
{
	int posY1 = mBg1->getPositionY();
	int posY2 = mBg2->getPositionY();
	int iSpeed = -1;
	posY1 += iSpeed;
	posY2 += iSpeed;

	int iVisibleHeight = Director::getInstance()->getVisibleSize().height;
	if (posY1 < iVisibleHeight * -0.5f) {
		posY2 = iVisibleHeight * 0.5f;
		posY1 = iVisibleHeight * 1.5f;
	}
	if (posY2 < iVisibleHeight * -0.5f) {
		posY1 = iVisibleHeight * 0.5f;
		posY2 = iVisibleHeight * 1.5f;
	}
	mBg1->setPositionY(posY1);
	mBg2->setPositionY(posY2);
}


