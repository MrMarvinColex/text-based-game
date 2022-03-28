#include "main.h"

int main() {
	Invoker invoker;
	Greeting* greetingCommand = new Greeting("First launch! Hi, I'm alive!\n");
	invoker.setCommand(greetingCommand);

	invoker.executeRemainings();
}
