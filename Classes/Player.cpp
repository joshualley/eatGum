#include "Player.h"
#include "ObjectTag.h"
#include "iostream"
using namespace std;

Player::Player()
{
	m_iHP = 50;
	m_iAtk = 1;
	m_iScore = 0;
}

Player::~Player()
{
}


bool Player::init()
{
	auto playerSp = Sprite::create("res/players/player_plane1.png");
	this->addChild(playerSp);

	auto body = PhysicsBody::createCircle(playerSp->getContentSize().width * 0.4f);
	body->getShape(0)->setFriction(0);
	body->getShape(0)->setRestitution(1.0f);
	body->setCategoryBitmask(1);
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);
	this->setPhysicsBody(body);

	this->getPhysicsBody()->applyImpulse(Vect(0, -40000));
	this->setTag(ObjectTag_Player);
	return true;
}

void Player::moveToLeft()
{
	this->getPhysicsBody()->applyImpulse(Vect(-50000, 0));
}

void Player::moveToRight()
{
	this->getPhysicsBody()->applyImpulse(Vect(50000, 0));
}

void Player::quickMove()
{
	this->getPhysicsBody()->applyImpulse(Vect(0, -200000));
}

void Player::beAtked(int iValue)
{
	if (iValue < 0) 
	{
		cure(-iValue);
	}
	else 
	{
		hurt(std::abs(iValue));
	}
}

void Player::hurt(int iValue)
{
	setiHP(getiHP() - iValue);
}

void Player::cure(int iValue)
{
	setiHP(getiHP() + iValue);
}

void Player::logic(float dt)
{
	
}
