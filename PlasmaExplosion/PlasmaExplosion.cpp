#include <iostream>
#include <SDL.h>
#include "Screen.h"

using namespace std;
using namespace ssk;

int main(int argc, char *args[]) {
	Screen screen;
	
	if (!screen.init()) {
		return 1;
	}

	while (true) {
		for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
			for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
				screen.setPixel(x, y, rand() % 255, rand() % 255, rand() % 255);
			}
		}

		screen.update();

		if (!screen.processEvents()) {
			break;
		}
	}
	
	screen.close();

	return 0;
}