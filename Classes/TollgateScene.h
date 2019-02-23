#ifndef __TOLLGATE_SCENE_H__
#define __TOLLGATE_SCENE_H__
#include "BackgroundLayer.h"
#include "MonsterLayer.h"
#include "Player.h"
#include "cocos2d.h"


class Tollgate : public cocos2d::Layer
{
public:
	enum {
		RUN,
		GAMEOVER,
		WIN
	};
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Tollgate);

	void createUI();
	void createUiWithCreator();
	void moveToRight(Ref* pSender);
	void moveToLeft(Ref* pSender);
	void quickMove(Ref* pSender);

	void restart(Ref* pSender);
	bool onContactBegin(PhysicsContact& contact);
	virtual void onExit() override;
	virtual void onEnter();
private:
	void logic(float dt);
	BackgroundLayer * mBgLayer;
	Player * mPlayer;
	MonsterLayer * mMonsterLayer;
	Label * mDispLabel;
	float gameState = RUN;
	ValueMap kvMap;
	float playTime = 0;
	

};

#endif // __TOLLGATE_SCENE_H__
