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

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (renderer == NULL) {
		cout << "Error initalizing the renderer: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 3;
	}

	if (texture == NULL) {
		cout << "Error initalizing the texture: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 4;
	}

	Uint32* buffer = new Uint32[SCREEN_HEIGHT*SCREEN_WIDTH];

	memset(buffer, 0x00, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));

	SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

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