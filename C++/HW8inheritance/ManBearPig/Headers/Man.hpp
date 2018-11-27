#include <string>

#include "Man.h"

Man::Man(const int lvl, const int health, const int damage, const int armor,
		const bool isAlive, const std::string firstName, 
		const std::string lastName, const unsigned int age, 
		const std::string sex) : 
		Unit(lvl, health, damage, armor, isAlive), mFirstName(firstName),
		mLastName(lastName), mAge(age), mSex((sex == "Male") ? 1 : 0)
{}


const unsigned int Man::getAge() const
{
	return mAge;
}

const std::string Man::getName() const
{
	return mFirstName + ' ' + mLastName;
}

const std::string Man::getSex() const
{
	return mSex ? "Male" : "Female";
}


void Man::marriage(const Man& love)
{
	if (!mSex)
	{
		mLastName = love.mLastName;
	}
}

void Man::birthday()
{
	++mAge;
}

const std::string Man::getTypeName() const
{
	return "Man";
}

