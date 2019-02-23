
#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "cocos2d.h"
class MainScene : public cocos2d::Scene{

public:
	MainScene(){}
	~MainScene(){}
	static cocos2d::Scene * createScene();
	virtual bool init();
	void start(Ref* pSender);
	void quit(Ref* pSender);
	void setting(Ref* pSender);
	void createUI();
	CREATE_FUNC(MainScene);

};

#endif // !__MAINSCENE_H__
