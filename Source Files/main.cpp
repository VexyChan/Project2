#include "Player.h"
#include "Room.h"
#include "Enemy.h"
#include "Item.h"
#include "Attack.h"
#include "Knight.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <map>
#include <exception>
#include <stdlib.h>
#include <time.h>

std::pair<Player*, Enemy*> doCombat(Player* player, Enemy* enemy) {
	system("CLS");

	std::vector<Attack*> enemyAttacks = enemy->getAttacks();
	Attack* enemyAttack = nullptr;
	Attack* userAttack = nullptr;
	std::vector<Item*> playerWeapons = player->getWeapons();
	std::vector<Item*> playerItems = player->getItems();
	Item* userWeapon = nullptr;
	std::string userIn;
	

	/*
	These are used for loop conditionals/input/iteration
	*/
	bool run = false;
	bool moveSelect = true;

	player->resetStatus();
	enemy->resetStatus();
	

	while (player->isAlive() && enemy->isAlive()) {
		
		bool goBack = false;//used to restart turn in a fight


		/*
		Shows choices to the player
		*/
		std::cout << player->getName() << "'s Health: " << player->getHealth() << std::endl;
		std::cout << enemy->getName() << "'s Health: " << enemy->getHealth() << std::endl;
		std::cout << "Fight!" << std::endl;
		std::cout << "1) Attacks" << std::endl;
		std::cout << "2) Items" << std::endl;
		std::cout << "3) Run" << std::endl;
		std::getline(std::cin, userIn);
		system("CLS");

		std::transform(userIn.begin(), userIn.end(), userIn.begin(), ::tolower); //sets input to lowercase, wont matter for numbers. EX: User can enter "1" OR "ATTACKS" for the first option

		/*
		ATTACK OPTION - SHOWS ALL OPTIONS FOR ATTACKS
		*/
		if (userIn == "1" || userIn == "attacks") {
			if (playerWeapons.size() > 0) {
				run = false;

				/*
				Selects an Attack for the enemy to use
				*/
				if (moveSelect) {
					enemyAttack = enemyAttacks[0];
					moveSelect = !moveSelect;
				}
				else {
					enemyAttack = enemyAttacks[1];
					moveSelect = !moveSelect;
				}

				/*
				This ensures the user is entering a number and that the number is in range
				*/
				while (!run) {
					system("CLS");
					/*
					Shows what move the enemy is about to use.
					*/
					std::string type;
					if (enemyAttack->getType() == "attack") {
						type = "do";
					}
					else if (enemyAttack->getType() == "block") {
						type = "block";
					}
					std::cout << "The " << enemy->getName() << " is about to use " << enemyAttack->getName() << "!" << std::endl;
					std::cout << "It will " << type << " " << enemyAttack->getValue() << " damage." << std::endl;
					std::cout << std::endl;

					/*
					Prints all of the player's "weapons" (includes melee, ranged, and magic)
					*/
					player->printWeapons();

					std::cout << std::endl;
					std::cout << "Select a weapon! You must enter a number." << std::endl;
					std::cout << "All weapons have multiple attack types." << std::endl;
					std::cout << "Enter 0 or any letter to go back!" << std::endl;
					int userIn;
					std::cin >> userIn;
					while (!std::cin) {
						std::cin.clear();
						std::cin.ignore();
						continue;
					}
					if (userIn == 0) {
						system("CLS");
						goBack = true;
						break;
					}
					if (userIn <= playerWeapons.size() && userIn > 0) {
						run = true;
						/*
						creates an Item* for the user's choice of weapon
						The -1 is so player can see list of weapons, when they pick first(1) weapon,
						they are actually picking the first(0) index of the weapons vector
						*/
						userWeapon = playerWeapons[userIn - 1];
						system("CLS");
					}
				}//End of while loop for weapon input

				/*
				This ensures the user is entering a number and that the number is in range
				*/
				run = false;
				while (!run && !goBack) {
					system("CLS");
					/*
					Shows what move the enemy is about to use.
					*/
					std::string type;
					if (enemyAttack->getType() == "attack") {
						type = "do";
					}
					else if (enemyAttack->getType() == "block") {
						type = "block";
					}
					std::cout << "The " << enemy->getName() << " is about to use " << enemyAttack->getName() << "!" << std::endl;
					std::cout << "It will " << type << " " << enemyAttack->getValue() << " damage." << std::endl;
					std::cout << std::endl;
					/*
					Displays the types of moves available for that weapon ("Stab", "Block", etc)
					*/
					userWeapon->printAttackTypes();

					std::cout << std::endl;
					std::cout << "Choose what to do with this attack! You must enter a number: " << std::endl;
					std::cout << "Enter 0 or any letter to go back!" << std::endl;
					int userIn;
					std::cin >> userIn;
					while (!std::cin) {
						std::cin.clear();
						std::cin.ignore();
						continue;
					}
					if (userIn == 0) {
						system("CLS");
						goBack = true;
						break;
					} 
					else if (userIn <= userWeapon->getAttackTypes().size() && userIn > 0) {
						run = true;
						userAttack = userWeapon->getAttackTypes()[userIn - 1];
						system("CLS");
					}
				}//end of while loop for attack input

				if (!goBack) {
					if (enemyAttack->getType() == "block") {
						enemy->setBlockValue(enemyAttack->getValue());
					}
					if (userAttack->getType() == "block") {
						player->setBlockValue(userAttack->getValue());
					}
					if (enemyAttack->getType() == "attack") {
						player->subHealth(enemyAttack->getValue());
					}
					if (userAttack->getType() == "attack") {
						enemy->attacked(userWeapon, userAttack);
					}
					if (enemyAttack->getType() == "status") {
						player->setStatus(enemyAttack->getName(), enemyAttack->getValue());
					}
					if (userAttack->getType() == "status") {
						enemy->setStatus(userAttack->getName(), userAttack->getValue());
					}
				}

				/*
				Checks if the player or enemy have any status damages that need to be subtracted
				*/
				player->checkStatus();
				enemy->checkStatus();
			} //End of IF statement for (player has more than 0 weapons)

			else { //IF YOU HAVE NO ATTACKS, IT GOES TO THIS ELSE STATEMENT
				std::cout << "You have no attacks." << std::endl;
			}
		} //end of IF statement for (user entered 1 OR attack)
		
		/*
		ITEMS OPTIONS - SHOWS ALL OPTIONS FOR ATTACKS
		*/
		else if (userIn == "2" || userIn == "items") {
			if (player->getItems().size() <= 0) {
				std::cout << "You don't have any items." << std::endl;
			}
			else {
				player->printItems();
				std::cout << std::endl;
				std::cout << "Choose an item!" << std::endl;
				std::cout << "Enter 0 or any letter to go back!" << std::endl;
				int userIn;
				std::cin >> userIn;
				while (!std::cin) {
					std::cin.clear();
					std::cin.ignore();
					continue;
				}
				if (userIn == 0) {
					system("CLS");
					goBack = true;
					break;
				}
				else if (userIn <= player->getItems().size() && userIn > 0) {
					Item* playerItem = player->getItems()[userIn - 1];
					if (playerItem->getType() == "health") {
						player->addHealth(playerItem->getValue());
					}
					else {
						std::cout << "THIS ITEM DOES NOT HAVE A USE RIGHT NOW." << std::endl;
					}
				}
			}


		}
		else if (userIn == "3" || userIn == "run") {
			system("CLS");
			break;
		}

	}
	return std::make_pair(player, enemy);
}

/*
Creates and populates the rooms that will be traveled through.
*/
std::vector<Room*> createRooms() {
	std::vector<Room*> room;
	for (int i = 0; i < 10; i++) {
		room.push_back(new Room("Room " + std::to_string(i)));
	}

	/*
	ROOM 0 - STARTING ROOM + STAIRCASE TO BOSS
	*/
	room[0]->setRooms(room[4], room[1], room[6], room[2]);
	room[0]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[0]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[0]->addToDescription("In the corner there is a staircase with a locked metal gate in front of it.");
	room[0]->addToDescription("This gate can't be broken, you must find a key.");
	room[0]->setLockStatus("locked");

	/*
	ROOM 1 - FIRST WEAPON ROOM
	*/
	room[1]->setRooms(room[0], nullptr, nullptr, nullptr);
	room[1]->addToDescription("You are in a well-lit room, with torches covering each wall.");
	room[1]->addToDescription("In the center of the room lay the remains of a long-dead knight.");
	Item* rustySword = new Item("Rusty Sword", "melee");
	rustySword->setAttackType("Stab", "attack", 20);
	rustySword->setAttackType("Block", "block", 20);
	rustySword->addToDescription("There is an ancient sword sticking out of its chest.");
	room[1]->setItem(rustySword);

	/*
	ROOM 2 - FIRST ENEMY
	*/
	room[2]->setRooms(nullptr, nullptr, room[0], room[3]);
	room[2]->addToDescription("There is an overwhelming smell of ass in this room.");
	room[2]->addToDescription("Try not to touch anything, you'll probably get some sort of disease.");
	Enemy* troll = new Enemy("Troll", 100);
	troll->setAttack("Club", "attack", 5);
	troll->setAttack("Shield", "block", 5);
	troll->setItem(new Item("Health Kit","health"));
	troll->getItem()->setValue(10);
	troll->setWarning("You see an angry looking troll with a giant club and a broken-down shield, and he sees you.");
	room[2]->setEnemy(troll);
	

	/*
	ROOM 3 - GET NEXT WEAPON TYPE
	*/
	room[3]->setRooms(nullptr, nullptr, room[2], room[7]);
	room[3]->addToDescription("This rooms seems to be the remnants of a library.");
	room[3]->addToDescription("There is hardened wax that has melted down the sides of bookshelves.");
	Item* bookOfFlames = new Item("Book of Flames", "magic");
	bookOfFlames->setAttackType("Blast", "attack", 20);
	bookOfFlames->setAttackType("Burn","status",15); //does 5 damage at the end of each turn
	bookOfFlames->addToDescription("At the edge of the room there is a pedestal with a book opened on it.");
	bookOfFlames->addToDescription("There seems to be a flickering light coming from it.");
	room[3]->setItem(bookOfFlames);
	/*
	ROOM 4
	*/
	room[4]->setRooms(room[5], room[0], nullptr, nullptr);
	room[4]->addToDescription("You see the remains of a campfire in what look like an old dining room.");
	room[4]->addToDescription("The embers are still hot.");
	Enemy* goblin = new Enemy("Goblin", 100);
	goblin->setAttack("Bleed", "status", 2); //bleeds 2 damage
	goblin->setAttack("Side-Step", "block", 10);
	goblin->setItem(new Item("Health Kit", "health"));
	goblin->setWarning("You hear something moving quickly among the dining tables. A goblin jumps at you.");
	room[4]->setEnemy(goblin);

	/*
	ROOM 5
	*/
	room[5]->setRooms(room[8], room[4], nullptr, nullptr);
	room[5]->addToDescription("This room clearly used to be an armory.");
	room[5]->addToDescription("There are sword hilts literring the ground.");
	room[5]->addToDescription("There are not many usable materials in this room.");
	Item* bowAndArrow = new Item("Bow and Arrow", "ranged");
	bowAndArrow->setAttackType("Snipe", "attack", 25);
	bowAndArrow->setAttackType("Hail", "status", 7); //hails 4 damage
	bowAndArrow->addToDescription("Hanging on one of the walls is a bow and there are arrows below it.");
	room[5]->setItem(bowAndArrow);

	/*
	ROOM 6
	*/
	room[6]->setRooms(nullptr, nullptr, nullptr, room[0]);
	room[6]->addToDescription("You are in a courtyard, with a large bonfire lit in the center.");
	room[6]->addToDescription("There are several sleeping bags, and some sort of animal is being cooked.");
	Knight* bronzeKnight = new Knight("Bronze Knight", 150);
	bronzeKnight->setAttack("Slam", "attack", 15); 
	bronzeKnight->setAttack("Barricade", "block", 10);
	bronzeKnight->setWarning("A tall knight clad in bronze-colored armor steps out from behind the fire.");
	bronzeKnight->setWarning("He carries a gleaming Steel Sword.");
	Item* steelSword = new Item("Steel Sword", "melee");
	steelSword->setAttackType("Stab", "attack", 30);
	steelSword->setAttackType("Block", "block", 25);
	steelSword->setAttackType("Fury", "status", 15);
	bronzeKnight->setItem(steelSword);
	bronzeKnight->setImmunity("melee");
	room[6]->setEnemy(bronzeKnight);
	Item* key1 = new Item("key", "item");
	key1->addToDescription("You see a key on the ground next to the sleeping bags.");
	room[6]->setItem(key1);

	/*
	ROOM 7
	*/
	room[7]->setRooms(nullptr, nullptr, room[3], nullptr);
	room[7]->addToDescription("You are in a backroom attached to the Library.");
	room[7]->addToDescription("There are scrolls spread all over the floor.");
	Knight* silverKnight = new Knight("Silver Knight", 150);
	silverKnight->setAttack("Whirlwind", "attack", 10);
	silverKnight->setAttack("Tornado","status",2);
	silverKnight->setWarning("There is a silver-clad knight sitting among the scrolls.");
	silverKnight->setWarning("A light seems to be pulsing from him.");
	Item* bookOfFlamesPlus = new Item("Advanced Book of Flames", "magic");
	bookOfFlamesPlus->setAttackType("Blast", "attack", 30);
	bookOfFlamesPlus->setAttackType("Burn", "status", 20);
	bookOfFlamesPlus->setAttackType("Flame Wall", "block", 30);
	silverKnight->setItem(bookOfFlamesPlus);
	silverKnight->setImmunity("magic");
	room[7]->setEnemy(silverKnight);
	Item* key2 = new Item("key", "item");
	key2->addToDescription("Among the scrolls you see a key.");
	room[7]->setItem(key2);

	/*
	ROOM 8
	*/
	room[8]->setRooms(nullptr, room[5], nullptr, nullptr);
	room[8]->addToDescription("You enter a courtyard which looks to be a firing range.");
	room[8]->addToDescription("There are dummy targets down-range which are full of arrows.");
	Knight* goldKnight = new Knight("Gold Knight", 150);
	goldKnight->setAttack("Triple Shot", "attack", 15);
	goldKnight->setAttack("Defensive Rain", "block", 15);
	goldKnight->setWarning("A knight is practicing his shooting with a giant recurve bow.");
	goldKnight->setWarning("He turns and sees you.");
	Item* bowAndArrowPlus = new Item("Recurve Bow", "ranged");
	bowAndArrowPlus->setAttackType("Snipe", "attack", 35);
	bowAndArrowPlus->setAttackType("Hail", "status", 20);
	goldKnight->setItem(bowAndArrowPlus);
	goldKnight->setImmunity("ranged");
	room[8]->setEnemy(goldKnight);
	Item* key3 = new Item("key", "item");
	key3->addToDescription("Hanging from one of the arrows is a key.");
	room[8]->setItem(key3);

	/*
	ROOM 9
	*/
	room[9]->setRooms(nullptr, nullptr, nullptr, nullptr);
	room[9]->addToDescription("You enter a well-lit room.");
	room[9]->addToDescription("Throughout the room there is golden treasure everywhere.");
	room[9]->setGate(true);
	Knight* bossKnight = new Knight("Betrayer", 150);
	bossKnight->setAttack("Sledge", "attack", 20);
	bossKnight->setAttack("Protect", "block", 30);
	bossKnight->setWarning("Your 'friend' is sitting among the treasures.");
	bossKnight->setWarning("You need to finish this.");
	bossKnight->setImmunity("melee");
	room[9]->setEnemy(bossKnight);

	return room;
}

/*
Returns a vector of user input tokens
*/
std::string tokenize(std::string userIn, char seperator) {
	std::vector<std::string> tokens;
	std::stringstream ss(userIn);
	std::string tok;
	bool stop = false;

	while(getline(ss, tok, seperator)) {
		if (tok == "quit" || tok == "help" || tok == "north" ||
			tok == "south" || tok == "east" || tok == "west" ||
			tok == "inventory" || tok == "gate" || tok == "take" ||
			tok == "grab" || tok == "look") 
		{
			return tok;
		}
	}
	return "blank";
}

/*
prints all options for help
*/
void printHelp() {

	/*
	creates 'help' list of available commands
	*/
	std::vector<std::string> help;
	help.push_back("north/south/east/west : travel in indicated direction. Can also enter 'go south', 'travel south', etc..");
	help.push_back("inventory : shows the player's inventory");
	help.push_back("look : describes the room to the player");
	help.push_back("take/grab : if there is an item in the room, lets you pick it up");
	help.push_back("");
	help.push_back("ENCOUNTER COMMANDS: ");
	help.push_back("run : if you encounter an enemy, allows you to return to previous room without engaging in combat");
	help.push_back("fight : if you encounter an enemy, starts a combat encounter");

	for (std::string msg : help) {
		std::cout << msg << std::endl;
	}
}



int main() {
	

	/*
	Creates rooms, run conditional
	*/
	std::vector<Room*> room = createRooms();
	Room* currentRoom = room[0];
	bool runGame = true;
	std::string userIn;

	/*
	Get character name here:
	*/
	std::cout << "You suddenly wake up, your head is pounding." << std::endl;
	std::cout << "You have a hard time remembering exactly what happened." << std::endl;
	std::cout << "There is one thing you do remember: " << std::endl;
	std::cout << "Your friend has betrayed you and left you for dead in this dungeon." << std::endl;
	std::cout << "Find them." << std::endl;
	std::cout << std::endl << std::endl;
	std::string name;
	std::cout << "Enter your character's name: " << std::endl;
	std::getline(std::cin, name);
	while(name.length() <= 0) {
		system("CLS");
		std::cout << "Enter your character's name: " << std::endl;
		std::getline(std::cin, name);
	}
	system("CLS");
	Player *player = new Player(name);
	bool printRoom = true;
	Item* steelSword = new Item("Steel Sword", "melee");
	steelSword->setAttackType("Stab", "attack", 50);
	steelSword->setAttackType("Block", "block", 50);
	steelSword->setAttackType("Fury", "status", 50);
	player->addToInv(steelSword);
	
	while (runGame) {
		Room* previousRoom = currentRoom; //This is used if the user wants to run from a fight, returns them to "previous room"

		if (printRoom) {
			std::cout << player->getName() << "'s health is: " << player->getHealth() << std::endl << std::endl;
			currentRoom->printDescription();
			if (currentRoom->hasItem()) {
				currentRoom->getItem()->printDescription();
			}
		}
		printRoom = true;
		/*
		takes user input and tokenizes it
		*/
		std::cout << "What do you want to do?" << std::endl;
		std::getline(std::cin, userIn);
		std::string tok = tokenize(userIn, ' ');
		system("CLS");

		std::transform(tok.begin(), tok.end(), tok.begin(), ::tolower);

		if (tok == "quit") {
			runGame = false;
			break;
		}//"QUIT" IF STATEMENT
		else if (tok == "help") {
			printRoom = false;
			printHelp();
			std::cout << std::endl;
		}//"HELP IF STATEMENT
		else if (tok == "north" || tok == "south" || tok == "east" || tok == "west") {
			currentRoom = currentRoom->getRoom(tok); //SETS CURRENT ROOM TO NEW ROOM, OR SAME ROOM IF DIRECTION WAS NULLPTR
			std::cout << player->getName() << "'s health is: " << player->getHealth() << std::endl << std::endl;
			currentRoom->printDescription();
			printRoom = false;
			if (currentRoom->hasItem()) {
				currentRoom->getItem()->printDescription();
			}

			if (currentRoom->hasEnemy()) { //CHECKS IF THERE IS AN ENEMY IN THE ROOM
				currentRoom->getEnemy()->printWarning();
				std::cout << "Do you want to fight the " << currentRoom->getEnemy()->getName() << " or run?" << std::endl;
				std::getline(std::cin, userIn);
				std::transform(userIn.begin(), userIn.end(), userIn.begin(), ::tolower);
				while (userIn != "fight" && userIn != "run") {
					system("CLS");
					std::cout << "Incorrect choice! Do you want to fight the " << currentRoom->getEnemy()->getName() << " or run?" << std::endl;
					std::cin >> userIn;
				}
				if (userIn == "run") {
					currentRoom = previousRoom;
					std::cout << player->getName() << "'s health is: " << player->getHealth() << std::endl << std::endl;
					currentRoom->printDescription();
					system("CLS");
					printRoom = true;
				}
				else {
					std::pair<Player*, Enemy*> combatants = doCombat(player, currentRoom->getEnemy());
					player = combatants.first;
					currentRoom->setEnemy(combatants.second);
					if (!currentRoom->getEnemy()->isAlive()) { //IF THE ENEMY IS DEAD
						std::cout << "You killed the " << currentRoom->getEnemy()->getName() << "!" << std::endl;
						if (currentRoom->getEnemy()->hasItem()) { //IF THE ENEMY HAD AN ITEM, IT GETS ADDED TO YOUR INVENTORY
							player->addToInv(currentRoom->getEnemy()->getItem());
							std::cout << "The " << currentRoom->getEnemy()->getName() << " dropped a " << currentRoom->getEnemy()->getItem()->getName() << "!" << std::endl;
							std::cout << "It has been added to your inventory!" << std::endl;
							int pause;
							std::cout << "Enter any number to continue.";
							std::cin >> pause;
							while (!std::cin) {
								std::cin.clear();
								std::cin.ignore();
								std::cout << "You must enter a number.";
								std::cin >> pause;
							}
						}
						currentRoom->removeEnemy();
					}
					else if (!player->isAlive()) { //IF THE PLAYER IS DEAD
						std::cout << "You were killed by the " << currentRoom->getEnemy()->getName() << "!" << std::endl;
						runGame = false;
						int pause;
						std::cout << "Enter any number to continue.";
						std::cin >> pause;
						while (!std::cin) {
							std::cin.clear();
							std::cin.ignore();
							std::cout << "You must enter a number.";
							std::cin >> pause;
						}
					}
				}
			}//if currentRoom.hasEnemy()
		}//ROOM TRAVEL DIRECTION IF STATEMENT
		else if (tok == "inventory") {
			std::cout << player->getName() << "'s health is: " << player->getHealth() << std::endl << std::endl;
			if (player->getItems().size() != 0) {
				std::cout << "Items: " << std::endl;
				player->printItems();
			}
			else {
				std::cout << "You have no items." << std::endl;
			}
			if (player->getWeapons().size() != 0) {
				std::cout << "Weapons: " << std::endl;
				player->printWeapons();
			}
			else {
				std::cout << "You have no weapons." << std::endl;
			}
			std::cout << std::endl;
			std::cout << "Select an item!" << std::endl;
			std::cout << "Enter 0 or any letter to go back!" << std::endl;
			int userIn;
			std::cin >> userIn;
			while (!std::cin) {
				std::cin.clear();
				std::cin.ignore();
				std::cout << "You must enter a number." << std::endl;
				std::cin >> userIn;
			}
			if (userIn <= player->getItems().size() && userIn > 0) {
				Item* playerItem = player->getItems()[userIn - 1];
				if (playerItem->getType() == "health") {
					player->addHealth(playerItem->getValue());
					player->removeFromInv(playerItem);
					system("CLS");
					std::cout << "You used a " << playerItem->getName() << "! It has been removed from your inventory." << std::endl;
					int pause;
					std::cout << "Enter any number to continue.";
					std::cin >> pause;
					while (!std::cin) {
						std::cin.clear();
						std::cin.ignore();
						std::cout << "You must enter a number.";
						std::cin >> pause;
					}
				}
				else {
					std::cout << "THIS ITEM DOES NOT HAVE A USE RIGHT NOW." << std::endl;
				}
			}
		}//INVENTORY IF STATMENT
		else if (tok == "gate") {
			if (currentRoom->hasGate()) {
				if (player->numOfKeys() > 0) {
					currentRoom->setLockStatus("unlocked");
				}
				if (currentRoom->isLocked()) {
					std::cout << "That is locked, find the key" << std::endl;
				}
				else {
					currentRoom = room[9];
				}
			}
			else {
				std::cout << "There is no gate to open in here." << std::endl;
			}
			
		}//GATE IF STATEMENT
		else if (tok == "take" || tok == "grab") {
			if (currentRoom->hasItem()) {
				player->addToInv(currentRoom->getItem());
				std::cout << "You received: " << currentRoom->getItem()->getName() << "!" << std::endl << std::endl;
				currentRoom->removeItem();
			}
			else {
				std::cout << "There are no items you can take." << std::endl;
			}
		}//CHEST IF STATEMENT
		else if (tok == "look") {
			std::cout << player->getName() << "'s health is: " << player->getHealth() << std::endl << std::endl;
			currentRoom->printDescription();
			printRoom = false;
			if (currentRoom->hasItem()) {
				currentRoom->getItem()->printDescription();
			}
			if (currentRoom->hasEnemy()) { //CHECKS IF THERE IS AN ENEMY IN THE ROOM
				currentRoom->getEnemy()->printWarning();
				std::cout << "Do you want to fight or run?";
				std::getline(std::cin, userIn);
				std::transform(userIn.begin(), userIn.end(), userIn.begin(), ::tolower);
				while (userIn != "fight" && userIn != "run") {
					system("CLS");
					std::cout << "Incorrect choice! Do you want to fight or run?";
					std::cin >> userIn;
				}
				if (userIn == "run") {
					printRoom = true;
					currentRoom = previousRoom;
					system("CLS");
				}
				else {
					std::pair<Player*, Enemy*> combatants = doCombat(player, currentRoom->getEnemy());
					player = combatants.first;
					currentRoom->setEnemy(combatants.second);
					if (!currentRoom->getEnemy()->isAlive()) { //IF THE ENEMY IS DEAD
						std::cout << "You killed the " << currentRoom->getEnemy()->getName() << "!" << std::endl;
						currentRoom->removeEnemy();
					}
					else if (!player->isAlive()) { //IF THE PLAYER IS DEAD
						std::cout << "You were killed by the " << currentRoom->getEnemy()->getName() << "!" << std::endl;
						runGame = false;
					}
				}
			}//IF CURRENT ROOM HAS ENEMY
		}//LOOK ELSE IF STATEMENT
	} //WHILE (RUN)
} //BOTTOM OF MAIN