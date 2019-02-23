#pragma once
#include "cocos2d.h"
#include "Monster.h"
USING_NS_CC;

class MonsterLayer : public Layer
{
public:
	MonsterLayer();
	~MonsterLayer();
	CREATE_FUNC(MonsterLayer);
	virtual bool init();
	void logic(float dt);
	int gemNum = 0;
private:
	void loadMonstersFromTmxConf();
	Vector<Monster*> m_monsterVec;

	//¼ÆÊ±Æ÷
	float m_fTimeCounter;
};

