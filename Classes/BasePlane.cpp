#include "BasePlane.h"

cocos2d::Layer * BasePlane::createObject()
{
	return BasePlane::create();
}

bool BasePlane::init()
{
	if (!Layer::init()) {
		return false;
	}

	sprite = Sprite::create();
	return true;
}