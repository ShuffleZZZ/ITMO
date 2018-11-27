#pragma once

#include "Animal.h"

class Pig : virtual public Animal
{
	public:
		explicit Pig(const int lvl, const int health, const int damage,
			const int armor, const bool isAlive, const int conquerLvl, 
			const bool isNeutral, const bool isToxic, const int mass, 
			const bool isTusked);
		
		const bool isPeaceful() const;
		const int getMass() const;
		
		void breakTusks();
		void feed(const int value);
		void chase(const int hours);
		
		const std::string roar() const override;
		const std::string getTypeName() const override;
	protected:
		bool mIsTusked;
		int mMass;
};

#include "Pig.hpp"
