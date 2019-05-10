#include "Player.h"
#include "Room.h"
#include "Enemy.h"
#include "Item.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <map>
#include <exception>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

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
	for (int i = 0; i < 20; i++) {
		room.push_back(new Room("Room " + std::to_string(i)));
	}

	/*
	Room[0] Starting Room Outside starting Town
	forest path is the only option for the next room
	*/
	room[0]->setRooms(room[1],nullptr,nullptr,nullptr);
	room[0]->addToDescription("After leaving the adventures guild & gathering your things, you leave the town...");
	room[0]->addToDescription("You stand outside the town ready to fight the Lord Of Chaos...);
	room[0]->addToDescription("But first you must find the old kingdom's necropolis...");
	room[0]->addToDescription("For now you may only go north towards the Forest...");
	room[0]->addToDescription("In the distance you see an ominous black miasma overcast in the direction you need to go...");

	
	/*
	ROOM 1 - FIRST WEAPON ROOM
	*/
	room[1]->setRooms(nullptr, room[0], room[2], room[3]);
	room[1]->addToDescription("You enter the path into the Nabaran Forest..."");
	room[1]->addToDescription("The path is over cast by trees and darkness.....");
	room[1]->addToDescription("This however is the only way to the necropolis of the old kingdom....");
	room[1]->addToDescription("Infomation from the guild tells you ...");
	room[1]->addToDescription("In the east is the direct route while in the west in a village you may stop and get supplies... ");
	room[1]->addToDescription(".");

	/*
	ROOM 2 - FIRST ENEMY
	*/
	room[2]->setRooms(room[5], nullptr,nullptr, room[1]);
	room[2]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[2]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[2]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[2]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[2]->addToDescription("This door can't be broken, you must find a key.");
	

	/*
	ROOM 3 - GET NEXT WEAPON TYPE
	*/
	room[3]->setRooms(room[4], nullptr, room[1], nullptr);
	room[3]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[3]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[3]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[3]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[3]->addToDescription("This door can't be broken, you must find a key.");
	/*
	ROOM 4
	*/
	room[4]->setRooms(nullptr, room[3], room[5],nullptr);
	room[4]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[4]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[4]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[4]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[4]->addToDescription("This door can't be broken, you must find a key.");
	/*
	ROOM 5
	*/
	room[5]->setRooms(room[6], room[2],nullptr,nullptr);
	room[5]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[5]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[5]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[5]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[5]->addToDescription("This door can't be broken, you must find a key.");

	/*
	ROOM 6
	*/
	room[6]->setRooms(room[7], room[5], nullptr, nullptr);
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
	room[7]->setRooms(nullptr, room[6], nullptr, room[8]);
	room[7]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[7]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[7]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[7]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[7]->addToDescription("This door can't be broken, you must find a key.");
	/*
	ROOM 8
	*/
	room[8]->setRooms(nullptr, room[9], room[7], nullptr);
	room[8]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[8]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[8]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[8]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[8]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 9
	*/
	room[9]->setRooms(room[8], nullptr,room[10],room[11]);
	room[9]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[9]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[9]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[9]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[9]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 10
	*/
	room[10]->setRooms(room[13], room[12], room[11], room[9]);
	room[10]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[10]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[10]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[10]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[10]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 11
	*/
	room[11]->setRooms(nullptr, nullptr, room[9], room[10]);
	room[11]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[11]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[11]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[11]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[11]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 12
	*/
	room[12]->setRooms(room[10], room[20], room[14], nullptr]);
	room[12]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[12]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[12]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[12]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[12]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 13
	*/
	room[13]->setRooms(room[15], room[10], nullptr,nullptr);
	room[13]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[13]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[13]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[13]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[13]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 14
	*/
	room[14]->setRooms(nullptr,nullptr,nullptr, room[12]);
	room[14]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[14]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[14]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[14]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[14]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 15
	*/
	room[15]->setRooms(room[16], room[13], room[17],nullptr);
	room[15]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[15]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[15]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[15]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[15]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 16
	*/
	room[16]->setRooms(nullptr, room[15], room[19], nullptr);
	room[16]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[16]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[16]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[16]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[16]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 17
	*/
	room[17]->setRooms(room[18], nullptr, nullptr, room[15]);
	room[17]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[17]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[17]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[17]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[17]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 18
	*/
	room[18]->setRooms(nullptr, room[12], nullptr,nullptr);
	room[18]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[18]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[18]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[18]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[18]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 19 Undead Dragon
	*/
	room[19]->setRooms(nullptr,nullptr,nullptr,room[19]);
	room[19]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[19]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[19]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[19]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[19]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 20 Boss Room [Chaos Lord]
	*/
	room[20]->setRooms(room[12],nullptr,nullptr,nullptr);
	room[20]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[20]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[20]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[20]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[20]->addToDescription("This door can't be broken, you must find a key.");
	room[20]->setLockStatus(true);
	room[20]->hasDoor(true);
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
			tok == "grab" || tok == "look" || tok == "search") 
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
    help.push_back("Interaction Commands:");
    help.push_back("[ {north} | {south} | {east} | {west} ] Will move you into the next room");
    help.push_back("{Inventory} Displays Your Inventory");
    help.push_back("{look} tells the player infomation about the room  & what items it has");
    help.push_back("[ {take} | {grab} ] Will allow you to take an item");
	help.push_back("[ {search} ]tells what items a room has");
    help.push_back("");
    help.push_back("Encounter Commands: ");
    help.push_back("{run} Allows you to return to the previous room before combat");
    help.push_back("{fight} Starts a combat encounter with an enemy");


	for (std::string msg : help) {
		std::cout << msg << std::endl;
	}
}



int main() {
std::cout << "########################" << std::endl;
std::cout << "# Welcome To                           #" << std::endl;
std::cout << "#                   Adventure Quest!#" << std::endl;
std::cout << "######################## " << std::endl;                                                                                                                   
system("CLS");                                                                                        
                                                                                                                            
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
	std::cout << "The lord of destruction & chaos has awakened. . . ." << std::endl;
	Sleep(10); 
	std::cout << "The land and its people are in dire peril! . . ." << std::endl;
	Sleep(10);
	std::cout << "You must become the hero that save the kingdom & the world from ruin. . ." << std::endl;
	Sleep(10);
	std::cout << "Will you stand against the chaos and save the world . . ." << std::endl;
	Sleep(10);
		std::cout << ". . ." << std::endl;
	Sleep(25);
	system("CLS");
	std::cout << std::endl << std::endl;
	std::string name;
	std::cout << "What is Your Name Hero. . . " << std::endl;
	std::getline(std::cin, name);
	while(name.length() <= 0) {
		system("CLS");
		std::cout << "What is Your Name Hero. . . " << std::endl;
		std::getline(std::cin, name);
	}
	system("CLS");
	std::cout << ". . . ???" << std::endl;
	Sleep(10);
	std::cout << "The Lord Of Chaos Wages War & Destruction upon the land attacking it's people in waves... "<<std::endl;
	Sleep(10);
	std::cout <<user.getName()<< " you have been tasked with defeating the chaos lord and his corrupted minions and stopping the spread of his  malevolence..."<<std::endl; 
	Sleep(10);
	std::cout <<"You must raid the Chaos Lord's  stronghold which was the necropolis of old, which belonged to a  long forgotten kingdom amongst the passing of time..."<<std::endl;
	Sleep(10);
	std::cout <<"The adventures guild of the kingdom of Estnophor has tasked you with finding and stop the spread of chaos..."<<std::endl;
	Sleep(10);
	std::cout <<"As well as defeating the Chaos Lord ..."<<std::endl;
	Sleep(10);
	std::cout <<"Will You Save the Kingdom & The World..."<<std::endl;
	Sleep(35);
	system("CLS");
	Player *player = new Player(name);
	bool printRoom = true;
	
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
		}//END OF INVENTORY IF STATMENT
		else if (tok == "search") {
			if (!currentRoom.hasItems()) {
				std::cout << "This room has no usable items." << std::endl;
			}
			else {
				tempItems = currentRoom.getItems();
				std::cout << "This room contains: " << std::endl;
				for (Item* it : tempItems) {
					std::cout << it.getName() << std::endl;
				}
			}
		}//END OF SEARCH IF STATEMENT
		else if (tok == "door") {
			if (currentRoom->hasDoor()) {
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
				std::cout << "There is no door to open in here." << std::endl;
			}
			
		}//END OF DOOR IF STATEMENT
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