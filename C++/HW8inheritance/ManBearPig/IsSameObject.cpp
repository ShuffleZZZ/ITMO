#include <iostream>

#include "AllClasses.h"

template<class T>
bool isSameObject(const T* p, const T* q)
{
	return dynamic_cast <const void*>(p) == dynamic_cast<const void*>(q);
	return 0;
}

int main()
{
	ManBearPig a(0, 200, 15, 3, 1, "Mike", "Ivanov", 25, "Male", 7, 1, 0, "White", "Good", 100, 0, "Man");
	std::cout << a.getTypeName() << ' ' << a.getName() << ' ' << "Age: " << a.getAge() << ' ' << "Sex: " << a.getSex() << '\n';
	std::cout << "Health: " << a.getHealth() << ' ' << "Damage: " << a.getDamage() << ' ' << "Armor: " << a.getArmor() << '\n';
	std::cout << "Lvl: " << a.getLevel() << ' ' << "Is alive: " << a.isAlive() << ' ' << "Roar: " << a.roar() << '\n';
	std::cout << "Conquer lvl: " << a.getConquerLevel() << ' ' << "Is neutral: " << a.isNeutral() << ' ' << "Is toxic: " << a.isToxic() << '\n';
	std::cout << "Kind: " << a.getKind() << ' ' << "Mood: " << a.getMood() << ' ' << "Mass: " << a.getMass() << ' ' << "Is peaceful: " << a.isPeaceful() << '\n';
	std::cout << "Form: " << a.getForm() << '\n';
	a.levelUp();
	std::cout << "Health after lvl up: ";
	std::cout << a.getHealth() << '\n';
	std::cout << "New form: ";
	a.changeForm();
	std::cout << a.getForm() << '\n';
	Man finn(0, 350, 65, 7, 1, "Ivan", "Petrov", 15, "Male");
	std::cout << finn.getTypeName() << '\n';
	Pig* p = &a;
	Bear* b = &a;
	Animal* c = p;
	Animal* d = b;
	std::cout << a.getConquerLevel() << ' ' << p -> getConquerLevel() << ' ' << b -> getConquerLevel()
	<< ' ' << c -> getConquerLevel() << ' ' << d -> getConquerLevel() << '\n';
	std::cout << isSameObject(c, d) << '\n';
}
