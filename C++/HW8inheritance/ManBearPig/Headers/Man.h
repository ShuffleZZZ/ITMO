#pragma once

#include "Unit.h"

class Man : virtual public Unit
{
	public:
		explicit Man(const int lvl, const int health, const int damage,
			const int armor, const bool isAlive, const std::string firstName, 
		const std::string lastName, const unsigned int age, 
		const std::string sex);
		
		const unsigned int getAge() const;
		const std::string getName() const;
		const std::string getSex() const;
		
		void marriage(const Man& love);
		void birthday();
		
		const std::string getTypeName() const override;
	private:
		const std::string mFirstName;
		std::string mLastName;
		unsigned int mAge;
		const bool mSex;
};

#include "Man.hpp"
