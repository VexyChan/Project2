#include <string>

class ItemGen
{
    
public:
	
    ItemGen();
    ItemGen(std::string name, std::string type, int value);
    ~ItemGen();
    std::string getName();
    void setName(std::string name);
    std::string getType();
    void setType(std::string type);
    void printItem();
    std::string genItemName();
    int genItemValue();
   
    
private:
    
    std::string name;
    std::string type;
    int value;

};
