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

int Enemy::getHealth()
{
	return this->health;
}

void Enemy::setHealth(int health)
{
	this->health = health;
}

/*
Adds health to enemy
*/
void Enemy::addHealth(int value)
{
	health = health + value;
}

void Enemy::subHealth(int value)
{
	int newVal;
	if ((value - blockValue) <= 0) {
		newVal = 0;
	}
	else {
		newVal = value - blockValue;
	}
	health = health - newVal;
	blockValue = 0;
	if (health <= 0) {
		alive = false;
	}
}

int Enemy::getBlockValue()
{
	return blockValue;
}

void Enemy::setBlockValue(int blockValue)
{
	this->blockValue = blockValue;
}

std::string Enemy::getName()
{
	return name;
}

void Enemy::setName(std::string name)
{
	this->name = name;
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

bool Enemy::isAlive()
{
	return alive;
}

void Enemy::printStatus()
{
	if (statusVector.size() > 0) {
		std::cout << "Current statuses are: " << std::endl;
		for (status stat : statusVector) {
			std::cout << "Status type: " << stat.statusName << " | Damage: " << stat.statusValue << " | Turns Remaining: " << stat.statusTurns << std::endl;
		}
	}
	else {
		std::cout << "No current statuses." << std::endl;
	}

}

void Enemy::setStatus(std::string statusName, int statusValue)
{
	int newVal;
	if ((statusValue - this->blockValue) <= 0) {
		newVal = 0;
	}
	else {
		newVal = statusValue - this->blockValue;
	}

	status temp;
	temp.statusName = statusName;
	temp.statusValue = newVal;
	temp.statusTurns = 3;
	this->statusVector.push_back(temp);
}

void Enemy::checkStatus()
{
	std::vector<status> tempStatus;
	for (status stat : statusVector) {
		if (stat.statusTurns > 0) {
			subHealth(stat.statusValue);
			--stat.statusTurns;
			tempStatus.push_back(stat);
		}
	}
	statusVector = tempStatus;
}

void Enemy::resetStatus()
{
	statusVector.clear();
}

void Enemy::attacked(Item * item, Attack* attack)
{
	subHealth(attack->getValue());
}
