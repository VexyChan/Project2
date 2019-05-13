#include <string>

class ItemGen
{
    
public:
	
    ItemGen();
    ItemGen(std::string name, std::string type, int value);
    ~ItemGen();
    ItemGen(std::string name, std::string description, bool isOpenable, bool isU, bool isE,bool std::string open, int h, int def, int blc, int atck);
    std::string getName();
    void setName(std::string nName);
    std::string getDescription();
    void setDescription(std::string desc);
    void setOpenable(bool openable);
    void printItem();
    bool getisOpenable();
    bool getIsUsable();

    bool getIsEquipable();
    int getHealthAdd();
    int getArmorAdd();
    int getBlockAdd();
    int getAttackAdd();

    void loadItem(std::ifstream& inFile);
    void saveItem(std::ofstream& oFile);
    void loadStaticItemParts(std::ifstream& inFile);
    void loadChangingItemParts(std::ifstream& inFile);
    std::string genItemName();
    int genItemValue();
   
    
private:
    
    std::string name;
    std::string type;
    int value;
    std::string description;
    std::string mOpen;
    bool isOpenable; 
    bool isUsable;
    bool isEquipable;
    int healthAdd;
    int defenseAdd;
    int blockAdd;
    int attackAdd;

};
