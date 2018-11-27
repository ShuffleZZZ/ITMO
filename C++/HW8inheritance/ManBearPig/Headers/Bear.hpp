#include <string>

#include "Bear.h"

Bear::Bear(const int lvl, const int health, const int damage,
	const int armor, const bool isAlive, const int conquerLvl, 
	const bool isNeutral, const bool isToxic, const std::string kind, 
	const std::string mood) :
	Unit(lvl, health, damage, armor, isAlive), 
	Animal(lvl, health, damage, armor, isAlive, conquerLvl, isNeutral, isToxic),
	mKind(kind), mMood(mood)
{}



const std::string Bear::getKind() const
{
	return mKind;
}

const std::string Bear::getMood() const
{
	return mMood;
}


void Bear::hunger()
{
	mMood = "Bad";
	mDamage *= 2;
	mArmor *=2;
	mConquerLevel += 5;
}

void Bear::eat()
{
	mMood = "Good";
	mDamage -= mDamage >> 2;
	mArmor -= mArmor >> 2;
	mConquerLevel -= 10;
}


const std::string Bear::roar() const
{
	return "RWAAAR";
}

const std::string Bear::getTypeName() const
{
	return "Bear";
}

	
