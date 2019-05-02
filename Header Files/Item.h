#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Attack.h"
class Item
{
public:
	Item(std::string name, std::string type);
	~Item();

	/*
	returns the name of the item EX: "Health Kit", "Rusty Sword"
	*/
	std::string getName();
	void setName(std::string name);

	/*
	returns the type EX: "health", "melee"
	*/
	std::string getType();
	void setType(std::string type);

	std::vector<Attack*> getAttackTypes();
	void setAttackType(std::string name, std::string type, int value);
	void printAttackTypes();

	std::vector<std::string> getDescription();
	void printDescription();
	void addToDescription(std::string desc);

	/*
	returns item's int value EX: health kit value
	*/
	int getValue();
	void setValue(int value);
private:
	std::vector<std::string> description;
	std::vector<Attack*> attackTypes;
	std::string name;
	std::string type; //KEY, item, weapon...
	int value; //for health items

};

