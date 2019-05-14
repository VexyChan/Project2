#include <string>

class ItemGen
{
    
public:
	
    ItemGen();
    ItemGen(std::string name, std::string type, int value);
    ~ItemGen();

    void printItem();
    std::string genItemName();
    int genItemValue();
   
    
private:
    
    std::string name;
    std::string type;
    int value;

};
