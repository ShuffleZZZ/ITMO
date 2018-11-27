#include <string>

#include "ManBearPig.h"

ManBearPig::ManBearPig(const int lvl, const int health, const int damage,
		const int armor, const bool isAlive, const std::string firstName, 
		const std::string lastName, const unsigned int age, 
		const std::string sex, const int conquerLvl, const bool isNeutral, 
		const bool isToxic, const std::string kind, const std::string mood, 
		const int mass, const bool isTusked, const std::string form) :
		Unit(lvl, health, damage, armor, isAlive), 
		Animal(lvl, health, damage, armor, isAlive, conquerLvl, isNeutral, isToxic),
		Man(lvl, health, damage, armor, isAlive, firstName, lastName, age, sex), 
		Bear(lvl, health, damage, armor, isAlive, conquerLvl, isNeutral, isToxic, kind, mood),
		Pig(lvl, health, damage, armor, isAlive, conquerLvl, isNeutral, isToxic, mass, isTusked),
		mForm(form)
{}


const std::string ManBearPig::getForm() const
{
	return mForm;
}


void ManBearPig::changeForm()
{
	if (mForm == "Man")
	{
		mForm = rand() % 2 == 1 ? "Bear" : "Pig";
	} else
	{
		mForm = "Man";
	}
}


const std::string ManBearPig::roar() const
{
	if (mForm == "Man")
	{
		return "FEEL the power of BEASTS";
	} else if (mForm == "Bear")
	{
		return "RWAAAR";
	} else if (mIsTusked)
	{
		return "WEEEE";
	} else
	{
		return "Oink";
	}
}

const std::string ManBearPig::getTypeName() const
{
	if (mForm == "Man")
	{
		return "Abomination";
	} else if (mForm == "Bear")
	{
		return "Bear";
	} else if (mForm == "Pig")
	{
		return "Pig";
	}
}
