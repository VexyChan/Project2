#include "ItemGen.h"
#include <string>
#include <stdlib> 
#include <time>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>


ItemGen::ItemGen()
{
    
}

ItemGen::ItemGen(std::string name, std::string type, int value)
	
	this->name = name;
	this->type = type;
	this->value = value;

}


void ItemGen::printItem()
{
	std::cout << "Item: " << name << type << value << std::endl;
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
