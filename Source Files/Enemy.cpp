#include "Enemy.h"

Enemy::Enemy()
{
	name = "";
	health = 0;
	alive = true;
	blockValue = 0;
	item = nullptr;
	hasImmunity = false;

}

Enemy::Enemy(std::string name, int health)
{
	this->name = name;
	this->health = health;
	alive = true;
	blockValue = 0;
	item = nullptr;
	hasImmunity = false;
}

Enemy::~Enemy()
{
}

/*
This returns the entire moves vector for the enemy
*/
std::vector<Attack*> Enemy::getAttacks()
{
	return attacks;
}

/*
Adds an Attack to the attack vector
*/
void Enemy::setAttack(std::string name, std::string type, int value)
{
	attacks.push_back(new Attack(name, type, value));
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

void Enemy::attacked(Item * item, Attack* attack)
{
	subHealth(attack->getValue());
}
