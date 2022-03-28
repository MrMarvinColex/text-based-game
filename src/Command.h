#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <vector>

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
//		пример: выход из игры нужно сделать только ожин раз
//		commands[hash(commands)] = something;
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

