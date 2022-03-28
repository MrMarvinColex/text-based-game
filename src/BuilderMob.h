#pragma once

#include <vector>

#include "_Armor.h"
#include "_Creature.h"
#include "_Items.h"
#include "_Weapon.h"

class Builder {
public:
	virtual ~Builder() {}
	virtual void reset() const = 0;
	virtual void setHealth() const = 0;
	virtual void setInventory() const = 0;
	virtual void setArmor() const = 0;
	virtual void setWeapon() const = 0;
};

class Beast : public Builder {
private:	
	Mob* mob;

public:
	// constructor
	Beast() {
		reset();
	}
	// destructor
	~Beast() {
		delete mob;
	}
	
	// creating method
	void reset() {
		mob = new Mob();
	}

	// building methods
	void setHealth() const override {
		mob->healthValue = 25;
	}
	void setInventory() const override {
		mob->inventory = 0;
	}
	void setArmor() const override {
		mob->armor = 5;
	}
	void setWeapon() const override {
		mob->weapon = Weapon("claw", 12);
	}

	// ger product
	Mob* getProduct() {
		Mob* result = mob;
		reset();
		return result;
	}
};

class Director {
private:
	Builder* builder;

public:
	void setBuilder(Builder* transferedBuilder) {
		builder = transferedBuilder;
	}
	void buildMob() {
		builder->setHealth();
		builder->setInventory();
		builder->setArmor();
		builder->setWeapon();
	}
};

