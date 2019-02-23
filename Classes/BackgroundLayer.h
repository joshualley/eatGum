#pragma once
#include "cocos2d.h"
USING_NS_CC;

class BackgroundLayer : public Layer
{
public:
	BackgroundLayer();
	~BackgroundLayer();
	CREATE_FUNC(BackgroundLayer);
	virtual bool init();
	void logic(float dt);
private:
	Sprite * mBg1;
	Sprite * mBg2;
	Sprite * createBoder(Point pos);

};



