#pragma once

#include <string>

#include "_Armor.h"
#include "_Items.h"
#include "_Weapon.h"

class Creature {
public:
	Creature() = default;
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
        Wallet inventory;
        Armor armor;
        Weapon weapon;
};

class Player : Creature {
public:
        Player() : xCoordinate(), yCoordinate(), Inventory(), armor(), weapon() {}
public:
        int xCoordinate;
        int yCoordinate;
	std::string playerName;
        Wallet Inventory;
        Armor armor;
        Weapon weapon;

	void move(int xMove, int yMove) {
		xCoordinate += xMove;
		yCoordinate += yMove;
	}
};
	
