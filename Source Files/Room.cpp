#include "Room.h"

Room::Room(std::string name)
{
	this->name = name;
	this->enemyBool = false;
	this->enemy = nullptr;
	this->item = nullptr;
	gate = false;
}

Room::~Room()
{
}

std::string Room::getName()
{
	return this->name;
}

void Room::setName(std::string name)
{
	this->name = name;
}

std::vector<std::string> Room::getDescription()
{
	return this->description;
}

void Room::addToDescription(std::string description)
{
	this->description.push_back(description);
}

void Room::printDescription()
{
	for (std::string desc : this->description) {
		std::cout << desc << std::endl;
	}
}

void Room::setRooms(Room * north, Room * south, Room * east, Room * west)
{
	this->north = north;
	this->south = south;
	this->east = east;
	this->west = west;
}

Room * Room::getRoom(std::string direction)
{
	std::transform(direction.begin(), direction.end(), direction.begin(), ::tolower); //changes direction string to lowercase, hopefully

	if (direction == "north" && this->north != nullptr) {
		return this->north;
	}
	else if (direction == "south" && this->south != nullptr) {
		return this->south;
	}
	else if (direction == "east" && this->east != nullptr) {
		return this->east;
	}
	else if (direction == "west" && this->west != nullptr) {
		return this->west;
	}
	else {
		return this;
	}
}

Item* Room::getItem()
{
	return this->item;
}

void Room::setItem(Item* item)
{
	this->item = item;
}

bool Room::hasItem()
{
	if (this->item == nullptr) {
		return false;
	}
	else {
		return true;
	}
	
}

void Room::removeItem()
{
	this->item = nullptr;
}

bool Room::isLocked()
{
	if (this->locked == "locked") {
		return true;
	}
	else {
		return false;
	}
}

void Room::setLockStatus(std::string status)
{
	this->locked = status;
}

bool Room::hasEnemy()
{
	return this->enemyBool;
}

Enemy* Room::getEnemy()
{
	return this->enemy;
}

void Room::removeEnemy()
{
	this->enemy = nullptr;
	this->enemyBool = false;
}

void Room::setEnemy(Enemy* enemy)
{
	this->enemy = enemy;
	this->enemyBool = true;
}

bool Room::hasGate()
{
	return gate;
}

void Room::setGate(bool gate)
{
	this->gate = gate;
}
