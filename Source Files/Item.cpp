#include "Item.h"



Item::Item(std::string name, std::string type)
{
	this->name= name;
	this->type = type;
}


Item::~Item()
{
}

std::string Item::getName()
{
	return this->name;
}

void Item::setName(std::string name)
{
	this->name = name;
}

/*
Returns either "melee", "ranged", "magic", or "item"
*/
std::string Item::getType()
{
	return this->type;
}

void Item::setType(std::string type)
{
	this->type = type;
}

std::vector<Attack*> Item::getAttackTypes()
{
	return this->attackTypes;
}

/*
takes a name and damage value (ex: "stab", 25), and adds them to a vector of attacks
*/
void Item::setAttackType(std::string name, std::string type, int value)
{
	this->attackTypes.push_back(new Attack(name, type, value));
}

void Item::printAttackTypes()
{
	int i = 1;
	for (Attack* at : this->attackTypes) {
		if (at->getType() == "attack" || at->getType() == "status") {
			std::cout << i << ".) " << at->getName() << " | Type: " << at->getType() << " | Damage: " << at->getValue() << std::endl;
		}
		else { //if attack type is "block", displays the value as 'Blocks: '
			std::cout << i << ".) " << at->getName() << " | Type: " << at->getType() << " | Blocks: " << at->getValue() << std::endl;
		}
		++i;
	}
}

std::vector<std::string> Item::getDescription()
{
	return this->description;
}

void Item::printDescription()
{
	for (std::string desc : this->description) {
		std::cout << desc << std::endl;
	}
}

void Item::addToDescription(std::string desc)
{
	this->description.push_back(desc);
}

int Item::getValue()
{
	return this->value;
}

void Item::setValue(int value)
{
	this->value = value;
}



