#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Player : public Node 
{
public:
	Player();
	~Player();
	virtual bool init();
	CREATE_FUNC(Player);

	void moveToLeft();
	void moveToRight();
	void quickMove();

	void beAtked(int iValue);
	void hurt(int iValue);
	void cure(int iValue);

	void logic(float dt);
private:
	CC_SYNTHESIZE(int, m_iHP, iHP);
	CC_SYNTHESIZE(int, m_iAtk, iAtk);
	CC_SYNTHESIZE(int, m_iScore, iScore);
};