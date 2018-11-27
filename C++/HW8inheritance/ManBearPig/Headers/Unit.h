#pragma once

class Unit
{
	public:
		explicit Unit(const int lvl, const int health, const int damage,
			const int armor, const bool isAlive);
		
		virtual const std::string getTypeName() const;
		
		const int getLevel() const;
		const int getHealth() const;
		const int getDamage() const;
		const int getArmor() const;
		const bool isAlive() const;
		
		void armorUp(const int value);
		void heal(const int value);
		void receivePhysicalDmg(const int value);
		void receiveMagicalDmg(const int value);
		void damageDebuff(const int value);
		
		void levelUp();	
		void levelDown();	
	protected:
		int mLevel;
		int mHealth;
		int mDamage;
		int mArmor;
		bool mIsAlive;
};

#include "Unit.hpp"
