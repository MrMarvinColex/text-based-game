/*
 *	this is
 *	MAIN.CPP
 */

#include "main.h"

int main() {
	Invoker invoker;
	StartGame* startGame = new StartGame();

	invoker.executeCommand(startGame);
	return 0;
}
