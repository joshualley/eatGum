#include "TollgateScene.h"
#include "MyUtils.h"
#include "SimpleAudioEngine.h"
#include "BackgroundLayer.h"
#include "ui/CocosGUI.h"
#include "ObjectTag.h"
//#include "reader/CreatorReader.h"
#include "MainScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* Tollgate::createScene()
{
	auto scene = Scene::createWithPhysics();
	Vect gravity(0, -0.5f);
	scene->getPhysicsWorld()->setGravity(gravity);
	//开启测试模式
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//创建一个边界
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*
	创建一个空心盒子刚体，作为游戏世界的边界
	参数为刚体大小，材质，边线厚度
	*/
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height));
	auto node = Node::create();
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	scene->addChild(node);

	//添加背景
	auto bgLayer = BackgroundLayer::create();
	scene->addChild(bgLayer, 0);

	//添加怪物
	auto monsterLayer = MonsterLayer::create();
	scene->addChild(monsterLayer, 1);

	
	auto layer = Tollgate::create();
	layer->mBgLayer = bgLayer;
	layer->mMonsterLayer = monsterLayer;
	scene->addChild(layer, 10);
    return scene;
}

void Tollgate::createUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 orgin = Director::getInstance()->getVisibleOrigin();
	
	MyUtils::parserXml("Strings.xml", kvMap);

	//设置按钮菜单
	auto leftBtn = MenuItemImage::create(
							"left.png",
							"",
							CC_CALLBACK_1(Tollgate::moveToLeft, this));
	leftBtn->setPosition(Vec2(orgin.x + 70, 60));
	auto rightBtn = MenuItemImage::create(
		"right.png",
		"",
		CC_CALLBACK_1(Tollgate::moveToRight, this));
	rightBtn->setPosition(Vec2(orgin.x + 140, 60));
	auto quickMoveBtn = MenuItemImage::create(
		"quick_move.png",
		"",
		CC_CALLBACK_1(Tollgate::quickMove, this));
	Size bSize = quickMoveBtn->getContentSize();
	quickMoveBtn->setPosition(Vec2(orgin.x + visibleSize.width - bSize.width - 70, 60));

	auto menu = Menu::create(leftBtn, rightBtn, quickMoveBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//设置计分标签
	std::string disp = "Life:" + std::to_string(mPlayer->getiHP()) + "  Score:" + std::to_string(mPlayer->getiScore());
	mDispLabel = Label::createWithSystemFont(disp, "Arial", 20);
	Size csize = mDispLabel->getContentSize();
	mDispLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - csize.height - 50));
	this->addChild(mDispLabel, 9);
}

void Tollgate::createUiWithCreator()
{
	//creator::CreatorReader* reader = creator::CreatorReader::createWithFilename("creator/scene/ui.ccreator");
	//reader->setup();
	//Scene * ui = reader->getSceneGraph();
	//this->addChild(ui);

	//auto leftBtn = (Button *)ui->getChildByName("left");
	//auto rightBtn = (Button *)ui->getChildByName("right");
	//auto quickMoveBtn = (Button *)ui->getChildByName("down");

	//leftBtn->addTouchEventListener(this, toucheventselector(Tollgate::moveToLeft));
	//rightBtn->addTouchEventListener(this, toucheventselector(Tollgate::moveToRight));
	//quickMoveBtn->addTouchEventListener(this, toucheventselector(Tollgate::quickMove));
}

void Tollgate::moveToRight(Ref * pSender)
{
	mPlayer->moveToRight();
}

void Tollgate::moveToLeft(Ref * pSender)
{
	mPlayer->moveToLeft();
}

void Tollgate::quickMove(Ref * pSender)
{
	mPlayer->quickMove();
}

void Tollgate::restart(Ref * pSender)
{
	//重新开始游戏
	auto sc = MainScene::createScene();
	Director::getInstance()->replaceScene(sc);
}

bool Tollgate::onContactBegin(PhysicsContact & contact)
{
	auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	if (nodeA == NULL || nodeB == NULL) 
	{
		return true;
	}

	Node* playerNode = NULL;
	Node* other = NULL;
	
	if (nodeA->getTag() == ObjectTag_Player)
	{
		playerNode = nodeA;
		other = nodeB;
	}
	else if (nodeB->getTag() == ObjectTag_Player)
	{
		playerNode = nodeB;
		other = nodeA;
	}
	else {
		return true;
	}

	Player * player = (Player*)playerNode;
	if (other->getTag() == ObjectTag_Border)
	{
		//碰到墙加1点血
		player->beAtked(-1);
		//log("player cur HP: %d", player->getiHP());
	}
	else if(other->getTag() == ObjectTag_Monster)
	{
		Monster * monster = (Monster*)other;
		
		player->beAtked(monster->getiAtk());
			
		if (monster->getiHP() > 0)
		{
			monster->setiHP(monster->getiHP() - player->getiAtk());
		}
		else 
		{
			if (monster->getID() == 2)
			{
				mMonsterLayer->gemNum--;
			}
			player->setiScore(player->getiScore() + monster->getiAward());
			monster->removeFromParent();
		}
		
	}
	if (player->getiHP() < 0) player->setiHP(0);
	
	if (mMonsterLayer->gemNum == 0 && playTime > 3)
	{
		gameState = WIN;
		std::string disp = "YOU WIN! TIME IS " + std::to_string(int(playTime));
		mDispLabel->setString(disp);
		auto win = Sprite::create("win.jpg");
		Size visibleSize = Director::getInstance()->getVisibleSize();
		win->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		//win->setOpacity(100);
		this->addChild(win);
		//取消事件监听
		_eventDispatcher->removeEventListenersForTarget(this);

		auto restartBtn = MenuItemImage::create(
			"Button.png",
			"",
			CC_CALLBACK_1(Tollgate::restart, this));
		restartBtn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 220));
		restartBtn->setScale(2);
		auto label1 = Label::createWithTTF(kvMap.at("next").asString(), "fonts/msyh.ttc", 20);
		label1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 220));
		this->addChild(label1, 11);
		auto menu = Menu::create(restartBtn, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 10);
	}
	if (player->getiHP() == 0)
	{
		gameState = GAMEOVER;
		std::string disp = "YOU ARE DEFEATED!";
		mDispLabel->setString(disp);
		auto gameover = Sprite::create("gameover.jpg");
		Size visibleSize = Director::getInstance()->getVisibleSize();
		gameover->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		gameover->setOpacity(80);
		this->addChild(gameover);
		//取消事件监听
		_eventDispatcher->removeEventListenersForTarget(this);
		auto restartBtn = MenuItemImage::create(
			"Button.png",
			"",
			CC_CALLBACK_1(Tollgate::restart, this));
		restartBtn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 220));
		restartBtn->setScale(2);
		auto label1 = Label::createWithTTF(kvMap.at("restart").asString(), "fonts/msyh.ttc", 20);
		label1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 220));
		this->addChild(label1, 11);
		auto menu = Menu::create(restartBtn, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 10);
	}
	return true;
}


bool Tollgate::init()
{
	if (!Layer::init()) 
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	mPlayer = Player::create();
	mPlayer->setPosition(Point(visibleSize.width*0.5f, visibleSize.height*0.85f));
	this->addChild(mPlayer, 5);
	this->createUI();
	//碰撞监听
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Tollgate::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->schedule(schedule_selector(Tollgate::logic));
    return true;
}

void Tollgate::logic(float dt)
{
	if (gameState == RUN) {
		playTime += dt;
		std::string disp = "Life:" + std::to_string(mPlayer->getiHP()) +
			"  Score:" + std::to_string(mPlayer->getiScore()) + "  Time:" + std::to_string(int(playTime));
		mDispLabel->setString(disp);
		mBgLayer->logic(dt);
		mMonsterLayer->logic(dt);
	}
	
}

void Tollgate::onExit()
{
	Layer::onExit();
	_eventDispatcher->removeEventListenersForTarget(this);
}

void Tollgate::onEnter()
{
	Layer::onEnter();
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event * event){
		if (keyCode == EventKeyboard::KeyCode::KEY_A) {
			mPlayer->moveToLeft();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_D) {
			mPlayer->moveToRight();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_S) {
			mPlayer->quickMove();
		}
	};
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

