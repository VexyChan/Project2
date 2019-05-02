#include "Player.h"



Player::Player(std::string name)
{
	this->name = name;
	this->health = 100;
	this->alive = true;
	this->blockValue = 0;
}


Player::~Player()
{
}

std::string Player::getName()
{
	return this->name;
}

void Player::setName(std::string name)
{
	this->name = name;
}

void Player::addToInv(Item* item)
{
	if (item->getType() == "melee" || item->getType() == "ranged" || item->getType() == "magic") {
		std::vector<Item*> tempWeapons;
		for (Item* it : weapons) {
			if (it->getType() != item->getType()) {
				tempWeapons.push_back(it);
			}
		}
		tempWeapons.push_back(item);
		weapons = tempWeapons;
	}
	else {
		this->items.push_back(item);
	}
}

void Player::removeFromInv(Item* item)
{
	std::vector<Item*> temp;
	if (item->getType() == "item" || item->getType() == "health") {
		for (Item* it : this->items) {
			if (it != item) {
				temp.push_back(it);
			}
		}
		this->items = temp;
	}
	else {
		for (Item* it : this->weapons) {
			if (it != item) {
				temp.push_back(it);
			}
		}
		this->weapons = temp;
	}
}

bool Player::searchInv(Item* item)
{
	if (item->getType() == "item") {
		for (Item* it : this->items) {
			if (it == item) {
				return true;
			}
		}
	}
	else {
		for (Item* it : this->weapons) {
			if (it == item) {
				return true;
			}
		}
	}
	return false;
}

std::vector<Item*> Player::getWeapons()
{
	return this->weapons;
}

void Player::printWeapons()
{
	int i = 1;
	for (Item* it : this->weapons) {
		std::cout << i << ".) " << it->getName() << " | Type: " << it->getType() << std::endl;
		++i;
	}
}

std::vector<Item*> Player::getItems()
{
	return this->items;
}

void Player::printItems()
{
	int i = 1;
	for (Item* it : this->items) {
		std::cout << i << ".) " << it->getName() << std::endl;
		++i;
	}
}

/*
Returns true if inventory IS NOT empty
Returns false if inventory IS empty
*/
bool Player::hasInventory()
{
	if (this->weapons.size() == 0 && this->items.size() == 0) {
		return false;
	}
	else {
		return true;
	}
}

int Player::numOfKeys()
{
	int i = 0;
	for (Item* it : items) {
		if (it->getName() == "key") {
			++i;
		}
	}
	return i;
}

int Player::getHealth()
{
	return this->health;
}

void Player::setHealth(int health)
{
	this->health = health;
}

/*
Adds Health
*/
void Player::addHealth(int value)
{
	this->health = this->health + value;
}

void Player::subHealth(int value)
{
	int newVal;
	if ((value - this->blockValue) <= 0) {
		newVal = 0;
	}
	else {
		newVal = value - this->blockValue;
	}
	this->health = this->health - newVal;
	this->blockValue = 0;
	if (this->health <= 0)
		this->alive = false;
	

}

int Player::getBlockValue()
{
	return this->blockValue;
}

void Player::setBlockValue(int blockValue)
{
	this->blockValue = blockValue;
}

bool Player::isAlive()
{
	return this->alive;
}

void Player::printStatus()
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

void Player::setStatus(std::string statusName, int statusValue)
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

void Player::checkStatus()
{
	std::vector<status> tempStatus;
	for (status stat : statusVector) {
		if (stat.statusTurns > 0) {
			this->subHealth(stat.statusValue);
			--stat.statusTurns;
			tempStatus.push_back(stat);
		}
	}
	this->statusVector = tempStatus;
}

void Player::resetStatus()
{
	statusVector.clear();
}
