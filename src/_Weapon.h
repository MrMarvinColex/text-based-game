/*
 * 	this is 
 * 	_WEAPONS.H
 */

#pragma once

#include <string>

class Weapon {
 public:
  Weapon() = default;
  Weapon (std::string name, int damage) : name(name), damage(damage) {}

 public:
  std::string name;
  int damage;

  int getDamage() {
    return damage;
  }
  std::string getName() {
    return name;
  }
};
