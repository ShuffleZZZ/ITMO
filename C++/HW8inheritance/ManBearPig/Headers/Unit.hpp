#include <string>

#include "Unit.h"

Unit::Unit(const int lvl, const int health, const int damage,
			const int armor, const bool isAlive) : 
			mLevel(lvl), mHealth(health), mDamage(damage),
			mArmor(armor), mIsAlive(isAlive)
{}


const std::string Unit::getTypeName() const
{
	return "Unit";
}

const int Unit::getLevel() const
{
	return mLevel;
}

const int Unit::getHealth() const
{
	return mHealth;
}

const int Unit::getDamage() const
{
	return mDamage;
}

const int Unit::getArmor() const
{
	return mArmor;
}

const bool Unit::isAlive() const
{
	return mIsAlive;
}


void Unit::armorUp(const int value)
{
	mArmor += value;
}

void Unit::heal(const int value)
{
	if (mHealth > 0)
	{
		mHealth += value;
	} else
	{
		mHealth += value >> 1;
	}
	if (mHealth > 0)
	{
		mIsAlive = 1;
	}
}

void Unit::receivePhysicalDmg(const int value)
{
	int pureValue = value;
	if (mArmor * 4 >= pureValue)
	{
		mArmor -= pureValue * 4;
	} else
	{
		pureValue -= mArmor * 4;
		mArmor = 0;
		mHealth -= pureValue;
		if (mHealth < 0)
		{
			mIsAlive = 0;
			mHealth = 0;
			levelDown();
		}
	}
}

void Unit::receiveMagicalDmg(const int value)
{
	mHealth -= value;
	if (mHealth < 0)
	{
		mIsAlive = 0;
		mHealth = 0;
		levelDown();
	}
}

void Unit::damageDebuff(const int value)
{
	mDamage -= value;
	if (mDamage < 0)
	{
		mDamage = 0;
	}
}

void Unit::levelUp()
{
	++mLevel;
	mHealth += mHealth >> 3;
	mDamage += mDamage >> 2;
	mArmor += mArmor;
}

void Unit::levelDown()
{
	--mLevel;
	mArmor -= mArmor >> 1;
	mDamage -= mDamage >> 2;
}
	
