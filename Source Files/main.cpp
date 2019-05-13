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
/* enemy attack add for knight
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
	*/
/*
Creates and populates the rooms that will be traveled through.
*/
std::vector<Room*> createRooms() {
	std::vector<Room*> room;
	for (int i = 0; i < 20; i++) {
		room.push_back(new Room("Room " + std::to_string(i)));
	}

	/*
	Room[0] Starting Room | Outside starting Town
	forest path is the only option for the next room
	Items:
	3x hp pots heal for 150
	1x armor adds 250 // the only thing the guild could spare due to the waves spread across the land and supplies for battaling them are so low
	2x Fireball  dmg 75-100
	3x throwing knife 25-50 dmg
	3x water
	2x rations
	No enemies in this room	
	*/
	room[0]->setRooms(room[1],nullptr,nullptr,nullptr);
	room[0]->addToDescription("After leaving the adventures guild & gathering your things, you leave the town...");
	room[0]->addToDescription("You stand outside the town ready to fight the Lord Of Chaos...);
	room[0]->addToDescription("But first you must find the old kingdom's necropolis...");
	room[0]->addToDescription("For now you may only go north towards the Forest...");
	room[0]->addToDescription("In the distance you see an ominous black miasma overcast in the direction you need to go...");
	/* Items*/
	Item*  sMageStaff= new Item("MageStaff", "magic");
	sMageStaff->addToDescription("Your trusty magic staff you have fought may enemies with while adventuring")
	sMageStaff->setAttackType("Fireball", "attack", 45);
	sMageStaff->setAttackType("Lightning", "attack", 20);
	sMageStaff->setAttackType("Purification", "attack", 55);
	Item* sHolySword = new Item("HolySword", "melee");
	sHolySword->addToDescription("Your trusty sword  you have had since you first became an adventure, it has been passed down in your family for generations");
	sHolySword->setAttackType("Slash", "attack", 40);
	sHolySword->setAttackType("cleave", "attack", 50);
	sHolySword->setAttackType("Impale", "attack", 55);
	Item* sBow = new Item("Bow&Arrow", "ranged");
	sBow->addToDescription("eww it is just a normal bow you just kinda found");
	sBow->setAttackType("VortexArrow", "attack", 35);
	sBow->setAttackType("FireArrow", "attack", 45);
	sBow->setAttackType("Snipe", "attack", 30);
	room[0]->setItem(sBow);
	room[0]->setItem(sHolySword);
	room[0]->setItem(sMageStaff);
	item* WaterRation1 = new Item("WaterRation", "health");
	WaterRation1->setValue(30);
	WaterRation1->addToDescription("Gain some health back for hydrating");
	room[0]->setItem(WaterRation1);
	item* FoodRation1 = new Item("FoodRation", "health");
	FoodRation1->setValue(20);
	FoodRation1->addToDescription("You can't fight on an empty stomach");
	room[0]->setItem(FoodRation1);
	item* HealthPotion1 =new Item("HealthPotion", "health";
	HealthPotion1->setValue(50);
	HealthPotion1->addToDescription("An avarge quality Health Potion")
	room[0]->setItem(HealthPotion1);
	item* HealthPotion2 =new Item("HealthPotion", "health";
	HealthPotion2->setValue(50);
	HealthPotion2->addToDescription("An avarge quality Health Potion")
	room[0]->setItem(HealthPotion2);
	item* HealthPotion3 =new Item("HealthPotion", "health";
	HealthPotion3->setValue(50);
	HealthPotion3->addToDescription("An avarge quality Health Potion")
	room[0]->setItem(HealthPotion3);
	item* LeatherArmor =new Item("LeatherArmor", "health");
	LeatherArmor->setValue(250);
	LeatherArmor->addToDescription("Well crafted armor which helps with taking some hit from enemies"));
	room[0]->setItem(LeatherArmor);
	/*
	ROOM 1 Starting path in the naba forest
	shield adds 32 hp // its a wood plank
	*/
	room[1]->setRooms(nullptr, room[0], room[2], room[3]);
	room[1]->addToDescription("You enter the path into the Nabaran Forest..."");
	room[1]->addToDescription("The path is over cast by trees and darkness.....");
	room[1]->addToDescription("This however is the only way to the necropolis of the old kingdom....");
	room[1]->addToDescription("Infomation from the guild tells you ...");
	room[1]->addToDescription("In the east is the direct route while in the west in a village you may stop and get supplies... ");
	/* Items */
	item* HealthPotion4 =new Item("HealthPotion", "health";
	HealthPotion4->setValue(50);
	HealthPotion4->addToDescription("An avarge quality Health Potion")
	room[1]->setItem(HealthPotion4);
	/* Enemeis*/
	Enemy* CHumman1 = new Enemy("Alex", 60);
	CHumman1->setAttack("Inpact", "attack", 10); 
	CHumman1->setAttack("AxeSlash", "attack", 40);
	CHumman1->setWarning("During the first waves when the chaos lord returned he had corrupted the spirts of  humans  make them mindless servents to chaos. . ..");
	CHumman1->setWarning("As you enter the forest you come upon 2 people Jace and Alex who you have known since childhood, as you get closser you see their eyes are glossed over. . .");
	CHumman1->setWarning("It is like they can't even see the world around them any more. . .");
	Enemy* CHumman2 = new Enemy("Jace", 45);
	CHumman2->setAttack("Inpact", "attack", 25); 
	CHumman2->setAttack("Punch", "attack", 20);
	room[1]->setEnemy(CHumman1);
	room[1]->setEnemy(CHumman2);
	/*
	ROOM 2  Western path of the Nahouran forest
	*/
	room[2]->setRooms(room[5], nullptr,nullptr, room[1]);
	room[2]->addToDescription("You have decided to go to the next village to find some supplies to fight the lord. . . .");
	room[2]->addToDescription("You still have a ways to go before you get there, you still can turn back. . .");
	room[2]->addToDescription("You have no idea what this path has in store for you . . .");
	room[2]->addToDescription("As you enter deeper into the forest the pressure of the miasma grows. . .");
	room[2]->addToDescription("you see several abandoned carts as you journey along the path may of them have been destroyed. . . but by what? . . .");
	/* Items */
	item* HealthPotion5 =new Item("HealthPotion", "health";
	HealthPotion5->setValue(50);
	HealthPotion5->addToDescription("An avarge quality Health Potion")
	room[2]->setItem(HealthPotion3);
	item* HealthPotion6 =new Item("HealthPotion", "health";
	HealthPotion6->setValue(50);
	HealthPotion6->addToDescription("An avarge quality Health Potion")
	room[2]->setItem(HealthPotion6);
	/*Enemies */ 
	Enemy* Bear= new Enemy("Bear", 100);
	Bear->setAttack("Charge", "attack", 35); 
	Bear->setAttack("Bite", "attack", 50);
	Bear->setAttack("Claw", "attack", 30);
	room[2]->setEnemy(Bear);
	/*
	ROOM 3 Eastern path of the Nahouran forest
	*/
	room[3]->addToDescription("You have decided to take the shorter path . . .");
	room[3]->addToDescription("As you reach the end it seems like the bridge is out. . .");
	room[3]->addToDescription("you find a path to the east which will take you around to the exit of the forest....");	
	room[3]->setRooms(room[4], nullptr, room[1], nullptr);
	/* Items */
	item* HealthPotion7 =new Item("HealthPotion", "health";
	HealthPotion7->setValue(50);
	HealthPotion7->addToDescription("An avarge quality Health Potion")
	room[3]->setItem(HealthPotion7);
	item* WaterRation2 =new Item("WaterRation", "health";
	WaterRation2->setValue(20);
	WaterRation2->addToDescription("Gain some health back for hydrating")
	room[2]->setItem(WaterRation2);
	item* WoodSheild =new Item("WoodPlank", "health";
	WoodSheild ->setValue(70);
	WoodSheild->addToDescription("Gain some more protection from damage")
	room[2]->setItem(WoodSheild);
	/*Enemies */ 
	Enemy* Wolf1= new Enemy("Wolf", 30);
	Wolf1->setAttack("Charge", "attack",15); 
	Wolf1->setAttack("Bite", "attack", 30);
	Wolf1->setAttack("Claw", "attack", 20);
	room[3]->setEnemy(Wolf1);
	Enemy* Wolf2= new Enemy("Wolf", 50);
	Wolf2->setAttack("Charge", "attack",25); 
	Wolf2->setAttack("Bite", "attack", 40);
	Wolf2->setAttack("Claw", "attack", 25);
	room[3]->setEnemy(Wolf2);
	Enemy* Wolf3= new Enemy("Wolf", 20);
	Wolf3->setAttack("Charge", "attack",15); 
	Wolf3->setAttack("Bite", "attack", 25);
	Wolf3->setAttack("Claw", "attack", 10);
	room[3]->setEnemy(Wolf3);
	Enemy* Wolf4= new Enemy("Wolf", 10);
	Wolf4->setAttack("Charge", "attack",5); 
	Wolf4->setAttack("Bite", "attack", 15);
	Wolf4->setAttack("Claw", "attack", 5);
	room[3]->setEnemy(Wolf4);
	/*
	ROOM 4 Off the eastern trail exit to the outskirts of the onld kingdom the plains
	*/
	room[4]->addToDescription("You have ended up closer to  the old  kingdom . . .");
	room[4]->addToDescription("As you reach the end of the forest you can see a field with a path . .");
	room[4]->addToDescription("you are still a good distance away from the old kingdom. . ..");
	room[4]->addToDescription("you need to go East to arrive at the old kingdom. . .");	
	room[4]->setRooms(nullptr, room[3], room[6],nullptr);
	Enemy* Wolf5= new Enemy("Wolf", 60);
	Wolf5->setAttack("Charge", "attack",25); 
	Wolf5->setAttack("Bite", "attack", 35);
	Wolf5->setAttack("Claw", "attack",40);
	room[4]->setEnemy(Wolf3);
	Enemy* Wolf6= new Enemy("Wolf", 50);
	Wolf6->setAttack("Charge", "attack",25); 
	Wolf6->setAttack("Bite", "attack", 45);
	Wolf6->setAttack("Claw", "attack", 15);
	room[4]->setEnemy(Wolf4);

	/*
	ROOM 5 the exit of the forest, next to the destroyed town of tohya
	*/
	room[5]->setRooms(room[6], room[2],nullptr,nullptr);
	room[5]->addToDescription("You are almost to the village of Toyha however you find the path has been blocked. . .");
	room[5]->addToDescription("There is a hole in the blockade and you  decide to get up on the blockade. . .");
	room[5]->addToDescription("When you are on the blockade you see the village of Toyha  burned to the ground. . .");
	room[5]->addToDescription("It is infested with zombies and what you belive crazzed humans killing each other. . .");
	room[5]->addToDescription("You have two choices either move north to the old kingdom which you see in the distance  and exit the forest or go back and try to go east to look for more supplies . . .");
	item* FoodRation2 = new Item("Food Ration", "health");
    FoodRation2->setValue(25);
    FoodRation2->addToDescription("Gain some health back for Eating");
    room[5]->setItem(FoodRation2);
	item* FoodRation3 = new Item("Food Ration", "health");
    FoodRation3->setValue(20);
    FoodRation3->addToDescription("Gain some health back for Eating");
    room[5]->setItem(FoodRation3);
	Enemy* ZHumman1 = new Enemy("Zombie", 60);
	ZHumman1->setAttack("Grab", "attack", 5); 
	ZHumman1->setAttack("Bite", "attack", 20);
	ZHumman1->setWarning("When the chaos lord returned he had corrupted the spirts of and trapped them inside dead humans bringing their bodies back to life. . .");
	ZHumman1->setWarning("As are about to leave blockade you find two zombies have wandered over to you. . .");
	Enemy* ZHumman2 = new Enemy("Zombie", 45);
	ZHumman2->setAttack("Bite", "attack", 25); 
	ZHumman2->setAttack("Claw", "attack", 20);
	room[5]->setEnemy(ZHumman1);
	room[5]->setEnemy(ZHumman2);
	/*
	ROOM 6  Old KIngdom City outskirt ruins 2 sekeltons
	*/
	room[6]->setRooms(room[7], room[5], nullptr, room[4]);
	room[6]->addToDescription("You arrive at the walls of the old kingdom. . .");
	room[6]->addToDescription("There is a giant hole piercing the wall at the bottom of one of the watch towers. . .");
	room[6]->addToDescription("It appears to be the only way in to the old kingdom. . .");
	room[6]->addToDescription("The Front Gates are closed and appear not to have moved in centuries. . .");
	Enemy* Skeleton1 = new Enemy("Skeleton", 50);
	Skeleton1->setAttack("Arrow Shot", "attack", 5); 
	Skeleton1->setAttack("BoneThrow", "attack", 20);
	Skeleton1->setWarning("When the chaos lord returned he returned some of the bones of the crypt located in the necropolis to motion traping slayed humans soul within their marrow. . .");
	Skeleton1->setWarning("You see two skeletons with bows standing perched on platforms higher up on the inside of the tower. . .");
	Skeleton1->setWarning("You must defeat them to make it into the city. . .");
	Enemy* Skeleton2 = new Enemy("skeleton", 55);
	Skeleton2->setAttack("Bite", "attack", 25);  
	Skeleton2->setAttack("Claw", "attack", 20);
	room[6]->setEnemy(Skeleton1);
	room[6]->setEnemy(Skeleton2);
	/*
	ROOM 7  Old kingdom main square
	*/
	room[7]->setRooms(nullptr, room[6], nullptr, room[8]);
	room[7]->addToDescription("After making it through the tower you have now arrived at the main plaza of the kingdom. . .");
	room[7]->addToDescription("You notice there are many bodies on the ground they look like the have been dropped from a significant high. . .");
	room[7]->addToDescription("You also notice some of them look to have been preyed on by vultures and other animals. . .");
	room[7]->addToDescription("ou see intestines strewn from these bodies as if what ever did this savagely ripped them apart after they fell from a high. . .");
	Enemy* Wayvern1 = new Enemy("Wayvern",150);
	Wayvern1->setAttack("Bite", "attack", 50); 
	Wayvern1->setAttack("TailWhip", "attack", 120);
	Wayvern1->setWarning("you hear a loud screeching noise then out of no where come two undead wayverns. . .");
	Wayvern1->setWarning("you have heard legends that the kingdoms of old use to have the power to train and control wayverns and dragons. . .");
	Wayvern1->setWarning("You never believed that they existed, but now you know they must have! ! ! . . .");
	Enemy* Wayvern2 = new Enemy("Wayvern", 155);
	Wayvern2->setAttack("Bite", "attack", 25);  
	Wayvern2->setAttack("Claw", "attack", 20);
	room[7]->setEnemy(Wayvern1);
	room[7]->setEnemy(Wayvern2);
	/*
	ROOM 8 Estize Kingdom Necropolis
	*/
	room[8]->setRooms(nullptr, room[9], room[7], nullptr);
	room[8]->addToDescription("You gotten to what seems  like the old kingdom's necropolis. . .");
	room[8]->addToDescription("There is a hole in the door and you slip your way in. . .");
	room[8]->addToDescription("You light a torch and see a map on the ground you pick it up and you notice it has the name Estize. . .");
	room[8]->addToDescription("The map looks similar to maps you have seen of the area now, the only diffrence was that insdead of the old kingdom it has the name Estize. . .");
	room[8]->addToDescription("Does that mean the kingdom was erased from the records for some reason? ? ? . . .");
	room[8]->addToDescription("You must decided to continue further south into the necropolis or to fail the world and it's people. . .");
	/*
	ROOM 9 Ritual Chamber
	*/
	room[9]->setRooms(room[8], nullptr,room[10],room[11]);
	room[9]->addToDescription("You arrive  in a cold room, surrounded on all four sides by walls with an alter in the middle with doors on the east and west sides.");
	room[9]->addToDescription("It seems like the temple where you see off the dead in the crypt of Estnophor");
	room[9]->addToDescription("If you remeber correctly the layout of the Estnophor crypt had a priests quarters to the  west and a path to the crypts in the east");
	Enemy* ChaosKnight1 = new Enemy("ChaosKnight", 255);
    ChaosKnight1->setAttack("Inpact", "attack", 25); 
    ChaosKnight1->setAttack("Punch", "attack", 20);
    room[9]->setEnemy(ChaosKnight1);
	Enemy* UndeadKnight1 = new Enemy("UndeadKnight", 115);
    UndeadKnight1->setAttack("MaceBludgeon", "attack", 35); 
    UndeadKnight1->setAttack("cleave", "attack", 40);
    room[9]->setEnemy(UndeadKnight1);
	Enemy* UndeadKnight2 = new Enemy("UndeadKnight", 125);
    UndeadKnight1->setAttack("SwordInpact", "attack", 25); 
    UndeadKnight1->setAttack("Punch", "attack", 20);
    room[9]->setEnemy(ChaosKnight1);
	room[9]->setEnemy(UndeadKnight1);
	room[9]->setEnemy(UndeadKnight2);
	/*
	ROOM 10 corridor to the crypts
	*/
	room[10]->setRooms(room[13], room[12], room[11], room[9]);
	room[10]->addToDescription("You descend deeper into the crypt to find the lord of chaos.");
	room[10]->addToDescription("There is many bones lined up on the walls of the crypt as you descent level after level");
	Enemy* ZHumman3 = new Enemy("Zombie", 60);
	ZHumman3->setAttack("Grab", "attack", 5); 
	ZHumman3->setAttack("Bite", "attack", 20);
	ZHumman3->setWarning("As you descend deeper into the crypts  you find  a large a hall that branches off into two diffrent directions. . .");
	ZHumman3->setWarning("You find three zombies wandering around the hall that has doors to the south and the north . .");
	Enemy* ZHumman4 = new Enemy("Zombie", 45);
	ZHumman4->setAttack("Bite", "attack", 25); 
	ZHumman4->setAttack("Claw", "attack", 20);
	Enemy* ZHumman5 = new Enemy("Zombie", 60);
	ZHumman5->setAttack("Grab", "attack", 5); 
	ZHumman5->setAttack("Bite", "attack", 20);
	room[10]->setEnemy(ZHumman3);
	room[10]->setEnemy(ZHumman4);
	room[10]->setEnemy(ZHumman5);
		/*
	ROOM 11  priests quarters
	*/
	room[11]->setRooms(nullptr, nullptr, room[9], room[10]);
	room[11]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[11]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[11]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[11]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[11]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 12 southern wing of the crypt
	*/
	room[12]->setRooms(room[10], room[20], room[14], nullptr]);
	room[12]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[12]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[12]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[12]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[12]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 13 norther wing of the crypt 
	*/
	room[13]->setRooms(room[15], room[10], nullptr,nullptr);
	room[13]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[13]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[13]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[13]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[13]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 14 1st generation tomb of royalty
	*/
	room[14]->setRooms(nullptr,nullptr,nullptr, room[12]);
	room[14]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[14]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[14]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[14]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[14]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 15 corrador of the dammed
	*/
	room[15]->setRooms(room[16], room[13], room[17],nullptr);
	room[15]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[15]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[15]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[15]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[15]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 16  north wing of the second lvl of the crypt
	*/
	room[16]->setRooms(nullptr, room[15], room[19], nullptr);
	room[16]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[16]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[16]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[16]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[16]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 17 Eastern wing of the second lvl of the crypt
	*/
	room[17]->setRooms(room[18], nullptr, nullptr, room[15]);
	room[17]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[17]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[17]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[17]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[17]->addToDescription("This door can't be broken, you must find a key.");
		/*
	ROOM 18  2nd generation tomb of royalty 3 undead knight  2 chaos knights Dead End room dont enter
	*/
	room[18]->setRooms(nullptr, room[17], nullptr,nullptr);
	room[18]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[18]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[18]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[18]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[18]->addToDescription("This door can't be broken, you must find a key.");
	Enemy* ChaosKnight2 = new Enemy("ChaosKnight", 125);
    ChaosKnight2->setAttack("Inpact", "attack", 25); 
    ChaosKnight2->setAttack("Punch", "attack", 20);
    room[18]->setEnemy(ChaosKnight1);
	Enemy* ChaosKnight3 = new Enemy("ChaosKnight", 125);
    ChaosKnight3->setAttack("Inpact", "attack", 25); 
    ChaosKnight3->setAttack("Punch", "attack", 20);
    room[18]->setEnemy(ChaosKnight3);
		/*
	ROOM 19 Undead Dragon  tomb of royal the gardian 1 undead dragon key room
	*/
	room[19]->setRooms(nullptr,nullptr,nullptr,room[19]);
	room[19]->addToDescription("You are in a cold room, surrounded on all four sides by walls, each with a door.");
	room[19]->addToDescription("There is a hole in the ceiling above you, but it is too high to reach, and there is nothing to climb on.");
	room[19]->addToDescription("In the corner there is a locked metal door with a small window.");
	room[19]->addToDescription("Upon looking through the window a staircase can be seen.");
	room[19]->addToDescription("This door can't be broken, you must find a key.");
	Item* key = new Item("key", "item");
	key->addToDescription("You see a key on the ground next to the sleeping bags.");
	room[19]->setItem(key);
	/*
	ROOM 20 Boss Room [Chaos Lord] Crypt of the elders 1 lord of destruction and chaos
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
						std::cout <<"The World and kingdom has fallen into ruins. . ."<<std::endl;
						Sleep(10);
						std::cout <<"You have failed however you do have another chance. . ."<<std::endl;
						Sleep(10);
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