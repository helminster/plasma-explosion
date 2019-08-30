#include <iostream>
#include <SDL.h>

using namespace std;

int main(int argc, char *args[]) {
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL init failed" << endl;
		return 1;
	}

	cout << "SDL init succeeded" << endl;

	SDL_Window* window = SDL_CreateWindow(
		"Plasma Explosion",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		cout << "Error initalizing the window: " << SDL_GetError() << endl;
		SDL_Quit();
		return 2;
	}

	bool quit = false;

	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}