#pragma once
#include <string>
#include <vector>
#include <map>
#include "Item.h"
#include "Attack.h"
class Enemy
{
public:
	Enemy();
	Enemy(std::string name, int health);
	~Enemy();

	int getHealth();
	void setHealth(int health);
	void addHealth(int value);
	void subHealth(int value);

	int getBlockValue();
	void setBlockValue(int blockValue);

	std::string getName();
	void setName(std::string name);

	std::vector<Attack*> getAttacks();

	/*
	Adds an Attack to the attack vector
	*/
	void setAttack(std::string name, std::string type, int value);

	void printWarning();
	void setWarning(std::string warning);

	Item* getItem();
	void setItem(Item* item);
	bool hasItem();

	bool isAlive();

	void printStatus();
	void setStatus(std::string statusName, int statusValue);
	void checkStatus();
	void resetStatus();

	void attacked(Item* item, Attack* attack);

protected:
	std::string name;
	std::vector<std::string> warning;
	int health;
	int blockValue;

	std::vector<Attack*> attacks;

	bool alive;

	Item* item;

	struct status {
		std::string statusName;
		int statusValue;
		int statusTurns;
	};

	std::vector<struct status> statusVector;

	bool hasImmunity;
};

