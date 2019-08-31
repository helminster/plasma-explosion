#include <iostream>
#include <SDL.h>
#include "Screen.h"

using namespace std;
using namespace ssk;

int main(int argc, char *args[]) {
	Screen screen;
	screen.init();

	while (true) {
		if (!screen.processEvents()) {
			break;
		}
	}

	screen.close();

	return 0;
}