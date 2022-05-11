/*
 *	this is
 *	MAIN.CPP
 */

#include "main.h"

int main() {
  srand(time(NULL));
  Invoker invoker;
  StartGame* startGame = new StartGame();

  invoker.executeCommand(startGame);

  delete startGame;
  return 0;
}
