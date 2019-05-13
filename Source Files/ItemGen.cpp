#include "ItemGen.h"
#include <string>
#include <cstdlib> 
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <random>
#include <chrono>
#include <algorithm>


ItemGen::ItemGen()
{
    
}

ItemGen::ItemGen(std::string nName, std::string type, bool isOpe, bool isU, bool isE, std::string open, int h, int arm, int blc, int atck, std::string whIsItem)
{
	name = nName;
	type = tType;
	isOpenable = isOpe;
	mOpen = open;
	isUsable = isU;
	isEquipable = isE;
	healthAdd = h;
	armorAdd = arm;
	blockAdd = blc;
	attackAdd = atck;
	whereIsItem = whIsItem;

}

//Getters Setters functions 
bool ItemGen::getisOpenable()
{
	return isOpenable;
}
bool ItemGen::getIsUsable()
{
	return isUsable;
}
bool ItemGen::getIsEquipable()
{
	return isEquipable;
}

int ItemGen::getHealthAdd()
{
	return healthAdd;
}

int ItemGen::getArmorAdd()
{
	return armorAdd;
}

int ItemGen::getBlockAdd()
{
	return blockAdd;
}

int ItemGen::getAttackAdd()
{
	return attackAdd;
}

std::string ItemGen::getName()
{
	return name;
}

void ItemGen::setName(std::string nName)
{
	name = nName;
}

std::string ItemGen::getType()
{
	return type;
}

void ItemGen::setType(std::string tType)
{
	type = tType;
}

std::string ItemGen::examine()
{
	return type;
}

std::string ItemGen::open()
{
	return mOpen;
}

void ItemGen::setOpenable(bool openable)
{
	isOpenable = openable;
}
void ItemGen::setOpenDesc(string openD)
{
	mOpen = openD;
}

std::string ItemGen::getWhereIsItem()
{
	return whereIsItem;
}


void ItemGen::printItem()
{
	std::cout << "Item name: " << name << std::endl;
	std::cout << "Item type: " << type << std::endl;
	std::cout << "Item isOpenable: " << isOpenable << std::endl;
	cout << "Item whereitis: " << whereIsItem << endl;

}

void ItemGen::loadItem(std::ifstream& inFile)
{

	string garbage;

	inFile >> garbage >> name;//read the object name
	//read all of the objects member variables
	inFile >> garbage ;
	getline(inFile, description);
	inFile >> garbage >> mOpen;
	inFile >> garbage >> isOpenable;
	inFile >> garbage >> isUsable;
	inFile >> garbage >> isEquipable;
	inFile >> garbage >> healthAdd;
	inFile >> garbage >> armorAdd;
	inFile >> garbage >> blockAdd;
	inFile >> garbage >> attackAdd;
	inFile >> garbage >> whereIsItem;

}

void ItemGen::saveItem(std::ofstream& oFile)
{
	oFile << "ItemName " << name << std::endl;
	oFile << "type " << type << std::endl;
	oFile << "Open " << mOpen << std::endl;
	oFile << "isOpenable " << isOpenable << std::endl;
	oFile << "isUsable " << isUsable << std::endl;
	oFile << "isEquipable " << isEquipable << std::endl;
	oFile << "healthAdd " << healthAdd << std::endl;
	oFile << "armorAdd " << armorAdd << std::endl;
	oFile << "blockAdd " << blockAdd << std::endl;
	oFile << "attackAdd " << attackAdd << std::endl;
	oFile << "RoomWhereItIs " << whereIsItem << std::endl;
	oFile << std::endl;

}

void ItemGen::loadStaticItemParts(std::ifstream& inFile)
{

	std::string garbage;

	inFile >> garbage >> name;//read the object name
	//read all of the objects member variables
	inFile >> garbage;
	getline(inFile, type);
	inFile >> garbage >> healthAdd;
	inFile >> garbage >> armorAdd;
	inFile >> garbage >> blockAdd;
	inFile >> garbage >> attackAdd;

}

void ItemGen::loadChangingItemParts(std::ifstream& inFile)
{

	std::string garbage;

	inFile >> garbage >> mOpen;
	inFile >> garbage >> isOpenable;
	inFile >> garbage >> isUsable;
	inFile >> garbage >> isEquipable;
	inFile >> garbage >> whereIsItem;
}

std::string genItemName()
{
    std::ifstream inFile_fn {"D:\\nameitem.txt"};
    std::ifstream inFile_ln {"D:\\typeofitem.txt"};

    std::vector<std::string> nameItem{std::istream_iterator<std::string>{inFile_fn}, {}};
    std::vector<std::string> typeOfItem{std::istream_iterator<std::string>{inFile_ln}, {}};

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(nameItem.begin(), nameItem.end(), std::default_random_engine(seed));
    std::shuffle(typeOfItem.begin(), typeOfItem.end(), std::default_random_engine(seed+1));

    for (size_t i = 0; i < std::min(name.size(), type.size()); ++i)
    {
        std::cout << nameItem[i] << typeOfItem[i] << "\n";
    }

}

int genItemValue()
{
    srand((unsigned)time(0)); 
    int value; 
    for(int index=0; index<1; index++)
    { 
        value = (rand()%10)+1; 
        std::cout << value << std::endl;
    }
}
    
ItemGen::~ItemGen()
{

}
