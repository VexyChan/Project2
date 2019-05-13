#include <string>

class ItemGen
{
    
public:
	
    ItemGen();
    ItemGen(std::string name, std::string type, int value);
    ~ItemGen();
    std::string genItemName();
    int genItemValue();
    
private:
    
    std::string name;
    std::string type;
    int value;


};
