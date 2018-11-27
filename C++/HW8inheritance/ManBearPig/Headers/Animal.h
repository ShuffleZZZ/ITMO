#pragma once

#include "Unit.h"

class Animal : virtual public Unit
{
	public:
		explicit Animal(const int lvl, const int health, const int damage,
			const int armor, const bool isAlive, const int conquerLvl, 
			const bool isNeutral, const bool isToxic);
		
		virtual const bool isToxic() const;
		virtual const bool isNeutral() const;
		virtual const int getConquerLevel() const;
		
		virtual void conquer(const int summonerLvl);
		virtual void escape();
		
		virtual const std::string roar() const;
		const std::string getTypeName() const override;
	protected:
		const bool mIsToxic;
		bool mIsNeutral;
		int mConquerLevel;
};

#include "Animal.hpp"
