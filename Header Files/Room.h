#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "Item.h"
#include <iostream>
#include "Enemy.h"
#include "Knight.h"

class Room
{
public:
	Room(std::string name);
	~Room();

	std::string getName();
	void setName(std::string name);

	std::vector<std::string> getDescription();
	void addToDescription(std::string description);
	void printDescription();

	void setRooms(Room* north, Room* south, Room* east, Room* west);
	Room* getRoom(std::string direction);

	Item* getItem();
	void setItem(Item* item);
	bool hasItem();
	void removeItem();

	bool isLocked();
	void setLockStatus(std::string status);

	bool hasEnemy();
	Enemy* getEnemy();
	void removeEnemy();
	void setEnemy(Enemy* enemy);

	bool hasGate();
	void setGate(bool gate);

private:
	bool enemyBool;
	bool gate;
	std::string locked;
	std::string name;
	std::vector<std::string> description;
	Item* item;

	Enemy* enemy;

	Room* north;
	Room* south;
	Room* east;
	Room* west;

	
};

