#include <string>

class ItemGen
{
    
public:
	
	ItemGen();
	ItemGen(std::string name, std::string type, int value);
	~ItemGen();
    std::string genItemName();
    std::string genItemType();
    int genItemValue();
    void print();
    
private:
    
    std::string name;
    std::string type;
    int value;


};
