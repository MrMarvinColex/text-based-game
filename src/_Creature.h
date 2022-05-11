/*
 * 	this is
 * 	_CREATURE.H
 */

#pragma once

#include <string>

#include "_Armor.h"
#include "_Items.h"
#include "_Weapon.h"

class Creature {
public:
	Creature() = default;
	Creature(int health) : healthValue(health) {}
public:
	int healthValue;

	void decreaseHealth(int decreaseValue) {
		healthValue -= decreaseValue;
		if (healthValue <= 0) {
			death();
		}
	}
	void death() {}
};

class Mob : public Creature {
public:
        Mob() : inventory(), armor(), weapon() {}
public:
	std::string mobName;
        Wallet inventory;
        Armor armor;
        Weapon weapon;

	int getHealth() {
                return healthValue;
        }
        std::string getName() {
                return mobName;
        }
        std::pair<std::string, int> getWeapon() {
                return {weapon.getName(), weapon.getDamage()};
        }
	std::pair<std::string, int> getInventory() {
                return inventory.getMoney();
        }
};

class Player : public Creature {
public:
        Player() : xCoordinate(), yCoordinate(), playerName(), inventory(), armor(), weapon() {}
	Player(int health, int x, int y, std::string name, int inv, int arm, std::string weapName, int dam) :
	       Creature(health), xCoordinate(x), yCoordinate(y), playerName(name), inventory(inv), armor(arm), weapon(weapName, dam) {}
public:
        int xCoordinate;
        int yCoordinate;
	int killCounter = 0;
	std::string playerName;
        Wallet inventory;
        Armor armor;
        Weapon weapon;

	void move(int xMove, int yMove) {
		xCoordinate += xMove;
		yCoordinate += yMove;
	}


	int getKillCounter() {
		return killCounter;
	}
	int getHealth() {
		return healthValue;
	}
	std::string getName() {
		return playerName;
	}
	std::pair<std::string, int> getWeapon() {
		return {weapon.getName(), weapon.getDamage()};
	}
	std::pair<std::string, int> getInventory() {
		return inventory.getMoney();
	}

	void decreaseMoney(int cost) {
		inventory.decreaseMoney(cost);
	}
	void increaseKills(int kills) {
		killCounter += kills;
	}

};
	
