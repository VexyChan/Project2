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

ItemGen(std::string name, std::string type, int value)
{
    this->name = nName;
    this->type = tType;
    this->value = vValue;
    
}

std::string genItemName()
{
    std::ifstream inFile_fn {"D:\\name.txt"};
    std::ifstream inFile_ln {"D:\\type.txt"};

    std::vector<std::string> name{std::istream_iterator<std::string>{inFile_fn}, {}};
    std::vector<std::string> type{std::istream_iterator<std::string>{inFile_ln}, {}};

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(name.begin(), name.end(), std::default_random_engine(seed));
    std::shuffle(type.begin(), type.end(), std::default_random_engine(seed+1));

    for (size_t i = 0; i < std::min(name.size(), type.size()); ++i)
    {
        std::cout << name[i] << type[i] << "\n";
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
