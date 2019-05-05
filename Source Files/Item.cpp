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
Returns either "melee", "ranged", "magic", "item"
*/
std::string Item::getType()
{
	return this->type;
}

/*
Returns the type of the item "melee", "ranged", "magic", "item"
*/
void Item::setType(std::string type)
{
	this->type = type;
}

int Item::getValue()
{
	return this->value;
}

void Item::setValue(int value)
{
	this->value = value;
}

std::vector<struct Attack> Item::getAttacks() 
{
	return attacks;
}

/*
takes an attack struct and adds it to attacks vector
*/
void Item::addToAttacks(struct Attack *attack)
{
	attacksVector.push_back(attack);
}

void Item::printAttackTypes()
{
	//THIS WILL HAVE TO BE RE-DONE
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





