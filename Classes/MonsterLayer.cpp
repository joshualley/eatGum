#include "MonsterLayer.h"



MonsterLayer::MonsterLayer()
{
	m_fTimeCounter = 0.0f;
}


MonsterLayer::~MonsterLayer()
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("monster.plist");
}

bool MonsterLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("monster.plist");
	loadMonstersFromTmxConf();

	return true;
}

void MonsterLayer::logic(float dt)
{
	m_fTimeCounter += dt;
	Vector<Monster*> deleteVec;
	for (auto monster : m_monsterVec)
	{
		if (m_fTimeCounter >= monster->getfShowTime())
		{
			monster->joinToWorld(this);
			deleteVec.pushBack(monster);
			if (monster->getID() == 2)
			{
				gemNum++;
			}
		}
	}
	
	for (auto monster : deleteVec)
	{
		m_monsterVec.eraseObject(monster);
	}
}

void MonsterLayer::loadMonstersFromTmxConf()
{
	TMXTiledMap * map = TMXTiledMap::create("tag.tmx");
	this->addChild(map);

	TMXObjectGroup * objGroup = map->getObjectGroup("monsters");
	ValueVector objects = objGroup->getObjects();

	for(const auto v: objects)
	{
		const ValueMap dict = v.asValueMap();
		int id = dict.at("id").asInt();
		float fShowTime = dict.at("showtime").asFloat();
		int iPosX = dict.at("x").asInt()*2;
		int iPosY = dict.at("y").asInt()*2;

		//创建怪物对象
		Monster * monster = Monster::create(id);
		monster->setID(id);
		monster->setfShowTime(fShowTime);
		monster->setiPosX(iPosX);
		monster->setiPosY(iPosY);

		m_monsterVec.pushBack(monster);
	}
}
