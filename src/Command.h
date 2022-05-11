/*
 * 	this is
 * 	COMMAND.H
 */

#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <vector>

#include "BuilderMob.h"
#include "_Creature.h"


class Command {
public:
	virtual ~Command() {}
	virtual void execute() const = 0;
};

class Greeting : public Command {
public:
	Greeting(const std::string& speech) : greeting(speech) {}
	void execute() const override {
		std::cout << greeting;
	}
private:
	std::string greeting = "Welcome in AmazingCave, stranger!\n";
};


class PrintInventory : public Command {
private:
	Player* player;
public:
	PrintInventory(Player* player) : player(player) {}
	~PrintInventory() {
		delete player;
	}
	void execute() const override {
		std::cout << "\n\n" << player->getName() << ",\n";
		std::cout << "Your health now: " << player->getHealth() << '\n';
		std::cout << "You have  " << player->getInventory().second << ' ' << player->getInventory().first << '\n';
		std::cout << "Your weapon is " << player->getWeapon().first << " with " << player->getWeapon().second << " damage\n";
	}
};


class HealPlayer : public Command {
private:
	Player* player;
	int debuff;
public:
	HealPlayer(Player* player, int debuff) : player(player), debuff(debuff) {}
	~HealPlayer() {
		delete player;
	}
	void execute() const override {
		int cost = 4 + rand() % 4 + debuff * (rand() % 2);
		int healPoints = 3 + rand() % 4 - debuff;
		
		std::cout << "\n\nDo you wanna change your " << cost << ' ' <<  player->getInventory().first << " to heal " << healPoints << " hp?\n";
		std::cout << "(y / n): ";
		std::string answer;
		std::cin >> answer;
		if (answer == "y" || answer == "Y" || answer == "1" || answer == "Yes" || answer == "Yeap" || answer == "yes" || answer == "yeap") {
			if (player->getInventory().second < cost) {
				std::cout << "Sorry, you haven't enough mana... ooops, sorry, money. \n";
				return ;
			}
			
			player->decreaseMoney(cost);
			player->decreaseHealth(-healPoints);
			std::cout << "Your HP now " << player->getHealth() << '\n';
		}
	}
};


class Attack : public Command {
private:
	Creature* target;
	int damage;
public:
	Attack(Creature* target, int damage) : target(target), damage(damage) {}
	void execute() const override {
		target->decreaseHealth(damage);
	}
};


class Invoker {
private:
//	вектор в разработке, смысл его существования написан чуть ниже
//	std::vector<bool> commands;
	std::queue<Command*> queueOfCommands;
public:
	Invoker() = default;
	void setCommand(Command* command) {
		queueOfCommands.push(command);
//		здесь может быть проверка для команд, исполняющихся только один раз
//		пример: выход из игры нужно сделать только один раз
//		commands[hash(commands)] = something;
	}
	void executeCommand(Command* command) {
		command->execute();
	}
	void makeFitings() {
//		for (auto fittingCommand : queue)
//			fitingCommand.execute();
	}
	void executeRemainings() {
		while(!queueOfCommands.empty()) {
			queueOfCommands.front()->execute();
			queueOfCommands.pop();
		}
	}
};


class StartGame : public Command {
public:
        StartGame() = default;
	void execute() const override {
		Invoker invoker;
                Greeting* greetingCommand = new Greeting("I found yourself in this cold and wet cave. \nSo, do you remember your name? ... \nenter the name: ");
                invoker.executeCommand(greetingCommand);

                std::string name;
                std::cin >> name;
                Player player(100, 0, 0, name, 20 + rand() % 20, 0, "Common Knife", 5 + rand() % 3);
		int winNumber = 5 + rand() % 11;

                PrintInventory* printInventory = new PrintInventory(&player);

                while (true) {
			if (player.getHealth() <= 0) {
				std::cout << "Ohhh, your adventure is ended ...\n";
				break;
			}
			if (player.getKillCounter() >= winNumber) {
				std::cout << "\n\nOh, you see the light in the end og tunnel!\nYou are saved!\n";
				break;
			}

                        std::cout << "\n\nWhat you wanna do?\n i: Print inventory\n h: Heal\n f: Go to fight\n e: Exit (not recommended)\n";
                        std::string answer;
                        std::cin >> answer;

                        if (answer == "e") {
                                std::cout << "\n\nAre you sure?\n(y / n): ";
                                std::string sure;
                                std::cin >> sure;
                                if (sure == "y")
                                        break;
                        } else if (answer == "i") {
                                invoker.executeCommand(printInventory);
                        } else if (answer == "h") {
                                HealPlayer* healPlayer = new HealPlayer(&player, 0);
                                invoker.executeCommand(healPlayer);
                        } else if (answer == "f") {
				Director director;
				Beast* beastBuilder = new Beast();
				director.setBuilder(beastBuilder);

				director.buildMob();
				Mob* mob = beastBuilder->getProduct();

				std::cout << "\n\n" << mob->getName() << " block your way. He has " << mob->getHealth() << " HP and " << mob->getWeapon().second
					  << " damage with his " << mob->getWeapon().first << ".\n";

				while (player.getHealth() > 0) {
					if (mob->getHealth() <= 0) {
						std::cout << "\n\nCongratulation, " << mob->getName() << " was killed, you get " << mob->getInventory().second << " gold.\n";
						player.decreaseMoney(-mob->getInventory().second);
						player.increaseKills(1);
						break;
					}
					
					std::cout << "\n\nWhat you wanna do?\n a: Attack monster\n h: Heal\n e: Exit from fight\n";
					std::string answer;
					std::cin >> answer;

					if (answer == "a") {
						/*
						std::cout << "\n\nYou damage " << mob->getName() << " with your " << player.getWeapon().first << " on " 
							  << player.getWeapon().second << " damage.\n";
						std::cout << mob->getName() << " have " << mob->getHealth() << " HP\n"; 
						std::cout << "You were damaged on " << mob->getWeapon().second << " with " << mob->getWeapon().first << ".\n";
						std::cout << "Your health now: " << player.getHealth();
						*/

						mob->decreaseHealth(player.getWeapon().second);
						player.decreaseHealth(mob->getWeapon().second);

						std::cout << "\n\nYou damage " << mob->getName() << " with your " << player.getWeapon().first << " on "
                                                          << player.getWeapon().second << " damage.\n";
                                                std::cout << mob->getName() << " have " << std::max(0, mob->getHealth()) << " HP\n";
                                                std::cout << "You were damaged on " << mob->getWeapon().second << " with " << mob->getWeapon().first << ".\n";
                                                std::cout << "Your health now: " << std::max(0, player.getHealth());
					} else if (answer == "h") {
						HealPlayer* healPlayer = new HealPlayer(&player, 1 + rand() % 2);
                                		invoker.executeCommand(healPlayer);
						std::cout << "Your health now: " << player.getHealth();
					} else if (answer == "e") {
						break;
					}
				}
                        } else {
                                std::cout << "\n\nSorry, I can't understand you, try again.\n";
                        }
                }
        }
};
