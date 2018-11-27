#pragma once

#include "Man.h"
#include "Bear.h"
#include "Pig.h"

class ManBearPig : public Man, public Bear, public Pig
{
	public:
		explicit ManBearPig(const int lvl, const int health, const int damage,
		const int armor, const bool isAlive, const std::string firstName, 
		const std::string lastName, const unsigned int age, 
		const std::string sex, const int conquerLvl, const bool isNeutral, 
		const bool isToxic, const std::string kind, const std::string mood, 
		const int mass, const bool isTusked, const std::string form);
		
		const std::string getForm() const;
		
		void changeForm();
		
		const std::string roar() const override;
		const std::string getTypeName() const override;
	private:
		std::string mForm;
};

#include "ManBearPig.hpp"
