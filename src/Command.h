/*
 * 	this is
 * 	COMMAND.H
 */

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>

#include "BuilderMob.h"
#include "_Creature.h"
#include "_Stream.h"

class Command {
 public:
  virtual ~Command() {}
  virtual void execute() const = 0;
};

class Greeting : public Command {
 public:
  Greeting(Stream* stream, const std::string& speech) : stream(stream), greeting(speech) {}
  void execute() const override {
    stream->sendMessage(greeting);
  }
 private:
  Stream* stream;
  std::string greeting;
};


class PrintInventory : public Command {
 private:
  Player* player;
  Stream* stream;
 public:
  PrintInventory(Player* player, Stream* stream) : player(player), stream(stream) {}
  void execute() const override {
    std::stringstream buffer;
    buffer  << "\n\n" << player->getName() << ",\n"
            << "Your health now: " << player->getHealth() << '\n'
            << "You have  " << player->getInventory().second << ' ' << player->getInventory().first << '\n'
            << "Your weapon is " << player->getWeapon().first << " with " << player->getWeapon().second << " damage\n";
    stream->sendMessage(buffer.str());
    // очищаем буффер, сейчас я им здесь больше по пользуюсь, но вдруг в будущем ...
    // столкнуться с такой проблемой будет неприятно.
    buffer.str("");
  }
};


class HealPlayer : public Command {
 private:
  Player* player;
  Stream* stream;
  int debuff;
 public:
  HealPlayer(Player* player, Stream* stream, int debuff) : player(player), stream(stream), debuff(debuff) {}
  void execute() const override {
    int cost = 4 + rand() % 4 + debuff * (rand() % 2);
    int healPoints = 3 + rand() % 4 - debuff;

    std::stringstream buffer;
    buffer << "\n\nDo you wanna change your " << cost << ' ' <<  player->getInventory().first << " to heal " << healPoints << " hp?\n"
           << "(y / n): ";
    stream->sendMessage(buffer.str());
    buffer.clear();
    // очищаем буффер
    buffer.str("");

    std::string answer = stream->receiveMessage();
    if (answer == "y" || answer == "Y" || answer == "1" || answer == "Yes" || answer == "Yeap" || answer == "yes" || answer == "yeap") {
      if (player->getInventory().second < cost) {
        buffer << "Sorry, you haven't enough mana... ooops, sorry, money. \n";
        stream->sendMessage(buffer.str());
	buffer.str("");
	return ;
      }

      player->decreaseMoney(cost);
      player->decreaseHealth(-healPoints);
      buffer << "Your HP now " << player->getHealth() << '\n';
      stream->sendMessage(buffer.str());
      buffer.str("");
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
 private:
  bool isTelegramm = false;
  Stream* stream;
 public:
  StartGame() : StartGame(false) {}
  StartGame(bool isTelegramm) : isTelegramm(isTelegramm), stream() {
    if(!isTelegramm) {
      stream = static_cast<Stream*>(new ConsoleStream());
    }
    else {
      stream = static_cast<Stream*>(new TelegrammStream());
    }
  }
  void execute() const override {

    TgBot::Bot bot("5333812218:AAH7vY6iKTXQms8uu7Ony_SYI0j3Hv66H2I");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
      bot.getApi().sendMessage(797384873, "Your message is: " + message->text);
      std::ofstream out("./info.txt");
      out << message->text;
      out.close();
    });

    Invoker invoker;
    Greeting* greetingCommand = new Greeting(stream, "I found yourself in this cold and wet cave. \nSo, do you remember your name? ... \nenter the name: ");
    invoker.executeCommand(greetingCommand);

    std::string name = stream->receiveMessage();
    Player player(100, 0, 0, name, 20 + rand() % 20, 0, "Common Knife", 5 + rand() % 3);
    int winNumber = 5 + rand() % 11;

    PrintInventory* printInventory = new PrintInventory(&player, stream);

    while (true) {
      std::stringstream buffer;
      if (isTelegramm) {
	TgBot::TgLongPoll longPoll(bot);
	longPoll.start();
      }
      if (player.getHealth() <= 0) {
        buffer << "Ohhh, your adventure is ended ...\n";
	stream->sendMessage(buffer.str());
        buffer.str("");
        break;
      }
      if (player.getKillCounter() >= winNumber) {
        buffer << "\n\nOh, you see the light in the end og tunnel!\nYou are saved!\n";
        stream->sendMessage(buffer.str());
        buffer.str("");
	break;
      }

      buffer << "\n\nWhat you wanna do?\n i: Print inventory\n h: Heal\n f: Go to fight\n e: Exit (not recommended)\n";
      stream->sendMessage(buffer.str());
      buffer.str("");
      std::string answer = stream->receiveMessage();

      if (answer == "e") {
        buffer << "\n\nAre you sure?\n(y / n): ";
	stream->sendMessage(buffer.str());
        buffer.str("");
        std::string sure = stream->receiveMessage();
        if (sure == "y")
          break;
      } else if (answer == "i") {
        invoker.executeCommand(printInventory);
      } else if (answer == "h") {
        HealPlayer* healPlayer = new HealPlayer(&player, stream, 0);
        invoker.executeCommand(healPlayer);
        delete healPlayer;
      } else if (answer == "f") {
        Director director;
        Beast* beastBuilder = new Beast();
        director.setBuilder(beastBuilder);

        director.buildMob();
        Mob* mob = beastBuilder->getProduct();

        buffer << "\n\n" << mob->getName() << " block your way. He has " << mob->getHealth() << " HP and " << mob->getWeapon().second
               << " damage with his " << mob->getWeapon().first << ".\n";
	stream->sendMessage(buffer.str());
        buffer.str("");

        while (player.getHealth() > 0) {
          if (mob->getHealth() <= 0) {
            buffer << "\n\nCongratulation, " << mob->getName() << " was killed, you get " << mob->getInventory().second << " gold.\n";
            stream->sendMessage(buffer.str());
            buffer.str("");
	    player.decreaseMoney(-mob->getInventory().second);
            player.increaseKills(1);
            break;
          }

          buffer << "\n\nWhat you wanna do?\n a: Attack monster\n h: Heal\n e: Exit from fight\n";
          stream->sendMessage(buffer.str());
          buffer.str("");
	  std::string answer = stream->receiveMessage();

          if (answer == "a") {
            mob->decreaseHealth(player.getWeapon().second);
            player.decreaseHealth(mob->getWeapon().second);

            buffer << "\n\nYou damage " << mob->getName() << " with your " << player.getWeapon().first << " on "
                   << player.getWeapon().second << " damage.\n"
                   << mob->getName() << " have " << std::max(0, mob->getHealth()) << " HP\n"
                   << "You were damaged on " << mob->getWeapon().second << " with " << mob->getWeapon().first << ".\n"
                   << "Your health now: " << std::max(0, player.getHealth()) << '\n';
	    stream->sendMessage(buffer.str());
            buffer.str("");
          } else if (answer == "h") {
            HealPlayer* healPlayer = new HealPlayer(&player, stream, 1 + rand() % 2);
            invoker.executeCommand(healPlayer);
	    delete healPlayer;
	  } else if (answer == "e") {
            break;
          }
        }
        delete beastBuilder;
        delete mob;
      } else {
        buffer << "\n\nSorry, I can't understand you, try again.\n";
	stream->sendMessage(buffer.str());
        buffer.str("");
      }
    }
    delete stream;
    delete greetingCommand;
    delete printInventory;
  }
};
