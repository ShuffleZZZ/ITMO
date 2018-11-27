#include <string>

#include "Animal.h"

Animal::Animal(const int lvl, const int health, const int damage,
	const int armor, const bool isAlive, const int conquerLvl, 
	const bool isNeutral, const bool isToxic) :
	Unit(lvl, health, damage, armor, isAlive),
	mConquerLevel(conquerLvl), mIsNeutral(isNeutral), mIsToxic(isToxic)		
{}


const bool Animal::isToxic() const
{
	return mIsToxic;
}

const bool Animal::isNeutral() const
{
	return mIsNeutral;
}

const int Animal::getConquerLevel() const
{
	return mConquerLevel;
}


void Animal::conquer(const int summonerLvl)
{
	if (mIsNeutral && summonerLvl >= mConquerLevel)
	{
		mIsNeutral = 0;
	}
}

void Animal::escape()
{
	mIsNeutral = rand() % 4 == 1 ? 1 : 0;
}

const std::string Animal::roar() const
{
	return "RRaghh";
}

const std::string Animal::getTypeName() const
{
	return "Animal";
}
