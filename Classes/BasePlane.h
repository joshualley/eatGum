#ifndef __BASEPLANE_H__
#define __BASEPLANE_H__
#include "cocos2d.h"
using namespace cocos2d;

class BasePlane : public cocos2d::Layer {

public:
	static cocos2d::Layer * createObject();
	virtual bool init();
	virtual void walk()=0;
	virtual void shoot()=0;
private:
	Sprite * sprite;

};

#endif // !__BASEPLANE_H__