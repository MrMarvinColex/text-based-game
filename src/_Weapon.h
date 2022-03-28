#pragma once

#include <string>

class Weapon {
public:
	Weapon() = default;
	Weapon (std::string name, int damage) : name(name), damage(damage) {}

public:
	std::string name;
	int damage;
};
