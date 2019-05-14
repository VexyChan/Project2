<<<<<<< 0c0961c5983cb4005218fd73e9963b5aaa004c30:Source Files/Enemy.cpp
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(std::string name, int health)
{
	this->name = name;
	this->health = health;
	alive = true;
	blockValue = 0;
	item = nullptr;
}

Enemy::~Enemy()
{
}

void Enemy::addToAttacks(std::string name, std::string type, int value)
{
	struct Attack tempAttack;
	tempAttack.name = name;
	tempAttack.type = type;
	tempAttack.value = value;
	attacksVector.push_back(&tempAttack);
}

std::vector<struct Attack*> Enemy::getAttacks()
{
	return attacksVector;
}

void Enemy::printWarning()
{
	for (std::string warn : warning) {
		std::cout << warn << std::endl;
	}
}

void Enemy::setWarning(std::string warning)
{
	this->warning.push_back(warning);
}

Item * Enemy::getItem()
{
	return this->item;
}

void Enemy::setItem(Item * item)
{
	this->item = item;
}

bool Enemy::hasItem()
{
	if (item == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

void Enemy::attacked(struct Attack attack)
{
	subHealth(attack.value);
}


=======
#include "Enemy.h"

Enemy::Enemy():Player()
{
	name = "";
	health = 0;
	alive = true;
	blockValue = 0;
	item = nullptr;

}

Enemy::Enemy(std::string name, int health):Player(name)
{
	this->name = name;
	this->health = health;
	alive = true;
	blockValue = 0;
	item = nullptr;
}

Enemy::~Enemy()
{
}

void Enemy::addToAttacks(std::string name, std::string type, int value)
{
	struct Attack tempAttack {name, type, value};
	this->attacksVector.emplace_back(tempAttack);
}

std::vector<Attack*> Enemy::getAttacks()
{
	return attacksVector; 
	/* the type is wrong// c2440a.cpp
	struct Base { }; // Defined

	struct Derived; // Forward declaration, not defined

	Base * func(Derived * d) {
		return static_cast<Base *>(d); // error C2440: 'static_cast' : cannot convert from 'Derived *' to 'Base *'
	}*/
}

void Enemy::printWarning()
{
	for (std::string warn : warning) {
		std::cout << warn << std::endl;
	}
}

void Enemy::setWarning(std::string warning)
{
	this->warning.push_back(warning);
}

Item * Enemy::getItem()
{
	return this->item;
}
void Enemy::setItem(Item * item)
{
	this->item = item;
}

bool Enemy::hasItem()
{
	if (item == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

void Enemy::attacked(int value) /// there is an issue with the player attacks vs enemy attacks
{
	Player::subHealth(value); // this is not an issu
}
>>>>>>> Vs Code Try 1 [1error]:RPG2/Enemy.cpp
