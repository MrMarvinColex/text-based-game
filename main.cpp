/*
 *	this is
 *	MAIN.CPP
 */

#include "main.h"

int main(int num, char* argv[]) {
  srand(time(NULL));
  Invoker invoker;
  StartGame* startGame = new StartGame(std::string(argv[1]) == "True");

  invoker.executeCommand(startGame);

  delete startGame;
  return 0;
}
