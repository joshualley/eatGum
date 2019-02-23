#include "Monster.h"
#include "ObjectTag.h"
#include "document.h"
#include "writer.h"
#include "reader.h"
#include "stringbuffer.h"

Monster::Monster()
{
	//m_iHP = (int)CCRANDOM_0_1() * 40 + 5;
	//m_iAward = m_iHP * 10;
}


Monster::~Monster()
{
}

Monster * Monster::create(int ID)
{
	auto monster = new Monster();
	if (monster && monster->init(ID))
	{
		monster->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monster);
	}
	return monster;
}

bool Monster::init(int ID)
{
	this->m_ID = ID;
	if (ID == 1) 
	{
		m_iHP = 5;
		m_iAward = 0;
	}else if(ID == 2)
	{
		//log("I am a gem.");
		m_iHP = 1;
		m_iAward = 50;
	}

	//解析JSON
	std::string data = FileUtils::getInstance()->getStringFromFile("monsterConf.json");
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	int size = document.Size();
	for (int i = 0; i < size; ++i)
	{
		const rapidjson::Value &conf = document[i];
		int id = conf["id"].GetInt();
		if (id == ID) 
		{
			m_sModelPath = conf["model"].GetString();
			m_iAtk = conf["atk"].GetInt();
			break;
		}
	}
	return true;
}

void Monster::joinToWorld(Node * parent)
{
	//log("picture's path: %s, ID: %d", m_sModelPath.asString().c_str(), this->m_ID);
	Sprite * sp = Sprite::createWithSpriteFrameName(m_sModelPath.asString().c_str());

	//创建刚体
	PhysicsBody * body = PhysicsBody::createBox(sp->getContentSize());
	body->setCategoryBitmask(1);
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);
	//精灵居中
	sp->setPosition(Point(sp->getContentSize().width*0.5f, sp->getContentSize().height*0.5f));
	this->addChild(sp);
	this->setTag(ObjectTag_Monster);

	this->setContentSize(sp->getContentSize());
	this->setPhysicsBody(body);

	this->setPosition(Point(getiPosX(), getiPosY()));

	parent->addChild(this);
}
