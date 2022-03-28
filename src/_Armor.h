#pragma once

#include <string>

class ArmorUnit {
public:
	ArmorUnit() = default;
	ArmorUnit (int value) : name(), durability(100), protectionFactor(value) {}

public:
	std::string name;
	int durability;
	double protectionFactor;
};

class Armor {
public:
	Armor() = default;
	Armor (int value) : helmet(value), chestplate(value), leggins(value), boots(value) {}

public:
	ArmorUnit helmet;
	ArmorUnit chestplate;
	ArmorUnit leggins;
	ArmorUnit boots;
};

