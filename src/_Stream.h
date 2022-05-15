/*
 *	this is
 *	_STREAM.H
 */

#pragma once

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <tgbot/tgbot.h>

class Stream {
 public:
  virtual ~Stream() {}
  virtual void sendMessage(const std::string&) const = 0;
  virtual std::string receiveMessage() const = 0;
};

class ConsoleStream : public Stream {
 public:
  ConsoleStream() = default;

  void sendMessage(const std::string& message) const override {
    std::cout << message;
  }
  std::string receiveMessage() const override {
    std::string message;
    std::cin >> message;
    return message;
  }
};


/*	
 *	it was taken from:
 *	https://github.com/reo7sp/tgbot-cpp
 *
 *	It's library to make TG bot with C++,
 *	but for me it was unsuccessfully, very sad.
 */

TgBot::Bot bot("5333812218:AAH7vY6iKTXQms8uu7Ony_*************");
class TelegrammStream : public Stream {
 private:
  //TgBot::Bot bot("5333812218:AAH7vY6iKTXQms8uu7Ony_*************"); 
  //static int chatID = 797384873;
 public:
  TelegrammStream() = default;

  void sendMessage(const std::string& stringMessage) const override {
    bot.getApi().sendMessage(797384873, stringMessage);
  }
  std::string receiveMessage() const override {
    /*bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
      bot.getApi().sendMessage(797384873, "Your message is: " + message->text);
      std::ofstream out("./info.txt");
      out << message->text;
      out.close();
    });
    */
    std::ifstream in("./info.txt");
    std::string message;
    in >> message;
    in.close();
    return message;
  }
};
