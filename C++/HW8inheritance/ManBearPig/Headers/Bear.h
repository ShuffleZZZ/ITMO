#pragma once

#include "Animal.h"

class Bear : virtual public Animal
{
	public:
		explicit Bear(const int lvl, const int health, const int damage,
			const int armor, const bool isAlive, const int conquerLvl, 
			const bool isNeutral, const bool isToxic, const std::string kind, 
			const std::string mood);
		
		const std::string getKind() const;
		const std::string getMood() const;
		
		void hunger();
		void eat();
		
		const std::string roar() const override;
		const std::string getTypeName() const override;
	private:
		const std::string mKind;
		std::string mMood;
};

#include "Bear.hpp"
