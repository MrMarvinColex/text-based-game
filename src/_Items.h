#pragma once

#include <string>
#include <vector>

class monetaryUnit {
public:
	monetaryUnit() = default;
	monetaryUnit (std::string name, int nominal) : nameOfCurrency(name), nominal(nominal) {}

public:
        std::string nameOfCurrency;
        int nominal;
};

class Wallet {
public:
	Wallet() = default;
	Wallet (int num) : money() {
		if (!num)
			money = {};
		else {
			money = {monetaryUnit("gold", num)};
		}
	}

public:
        std::vector<monetaryUnit> money;
};

