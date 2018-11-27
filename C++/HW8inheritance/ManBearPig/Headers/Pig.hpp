#include "Pig.h"

Pig::Pig(const int lvl, const int health, const int damage,
			const int armor, const bool isAlive, const int conquerLvl, 
			const bool isNeutral, const bool isToxic, const int mass, 
			const bool isTusked) :
		Unit(lvl, health, damage, armor, isAlive), 
		Animal(lvl, health, damage, armor, isAlive, conquerLvl, isNeutral, isToxic),
		mMass(mass), mIsTusked(isTusked)
{}


const bool Pig::isPeaceful() const
{
	return !mIsTusked;
}

const int Pig::getMass() const
{
	return mMass;
}


void Pig::breakTusks()
{
	mIsTusked = 0;
}

void Pig::feed(const int value)
{
	mMass += value;
}

void Pig::chase(const int hours)
{
	mMass -= (mMass >> 4) * hours;
	if (mMass < 0)
	{
		mHealth += mMass >> 1;
		mMass = 0;
		if (mHealth < 0)
		{
			mIsAlive = 0;
			mHealth = 0;
			levelDown();
		}
	}
}


const std::string Pig::roar() const
{
	if (mIsTusked)
	{
		return "WEEEE";
	} else
	{
		return "Oink";
	}
}

const std::string Pig::getTypeName() const
{
	return "Pig";
}
