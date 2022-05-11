/*
 * 	this is
 * 	_ITEM.H
 */

#pragma once

#include <string>
#include <vector>

class monetaryUnit {
 public:
  monetaryUnit() = default;
  monetaryUnit (std::string name, int nominal) : nameOfCurrency(name), nominal(nominal) {}

  std::string getName() {
    return nameOfCurrency;
  }
  int getNominal() {
    return nominal;
  }

 private:
  std::string nameOfCurrency;
  int nominal;
};

class Wallet {
 public:
  Wallet (int num = 0) : money() {
    if (!num)
      money = {};
    else {
      money = {{monetaryUnit("gold", 1), num}};
    }
  }

  std::pair<std::string, int> getMoney() {
    return {money[0].first.getName(), money[0].first.getNominal() * money[0].second};
  }
  void decreaseMoney(int cost) {
    money[0].second -= cost;
  }

 private:
  std::vector<std::pair<monetaryUnit, int>> money;
};

