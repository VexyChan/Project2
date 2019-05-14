<<<<<<< 0c0961c5983cb4005218fd73e9963b5aaa004c30:Header Files/Enemy.h
#pragma once
#include <string>
#include <vector>
#include <map>
#include "Item.h"
#include "Player.h"

class Enemy:public Player
{
public:
	/*
	CONSTRUCTORS
	*/
	Enemy();
	Enemy(std::string name, int health);
	~Enemy();

	/*
	Adds an Attack to the attack vector
	*/
	void addToAttacks(std::string name, std::string type, int value);
	std::vector<struct Attack*> getAttacks();

	/*
	WARNINGS THAT ENEMY SHOWS WHEN IN A ROOM
	*/
	void printWarning();
	void setWarning(std::string warning);

	/*
	THE ITEM AN ENEMY IS HOLDING
	*/
	Item* getItem();
	void setItem(Item* item);
	bool hasItem();

	/*
	TAKES IN AN ATTACK AND PERFORMS OPERATIONS ON ENEMY HEALTH/STATUS
	NOT YET COMPLETED
	*/
	void attacked(struct Attack attack);

protected:

	std::string name;
	std::vector<std::string> warning;
	int health;
	int blockValue;

	std::vector<struct Attack*> attacksVector;

	bool alive;

	Item* item;

	struct status {
		std::string statusName;
		int statusValue;
		int statusTurns;
	};

	std::vector<struct status> statusVector;
};
=======
#pragma once
#include <string>
#include <vector>
#include <map>
#include "Item.h"
#include "Player.h"



class Enemy :public Player
{
public:
	/*
	CONSTRUCTORS
	*/
	Enemy();
	Enemy(std::string name, int health);
	~Enemy();


	/*
	Adds an Attack to the attack vector
	*/
	void addToAttacks(std::string name, std::string type, int value);
	std::vector<Attack*> getAttacks();

	/*
	WARNINGS THAT ENEMY SHOWS WHEN IN A ROOM
	*/
	void printWarning();
	void setWarning(std::string warning);

	/*
	THE ITEM AN ENEMY IS HOLDING
	*/
	Item* getItem();

	void setItem(Item* item);
	bool hasItem();
	/*
	TAKES IN AN ATTACK AND PERFORMS OPERATIONS ON ENEMY HEALTH/STATUS
	NOT YET COMPLETED
	*/
	void attacked(int value);

	struct Attack
	{
		std::string name;
		std::string type;
		int value;
	};

protected:

	std::string name;
	std::vector<std::string> warning;
	int health;
	int blockValue;

	std::vector<Attack*> attacksVector;

	bool alive;

	Item* item;

	struct status {
		std::string statusName;
		int statusValue;
		int statusTurns;
	};

	std::vector<status> statusVector;
};

>>>>>>> Vs Code Try 1 [1error]:RPG2/Enemy.h
