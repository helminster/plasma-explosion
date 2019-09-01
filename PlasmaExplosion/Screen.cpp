#include "Screen.h"
#include <iostream>

using namespace std;

namespace ssk {
	Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_secondBuffer(NULL)
	{
	}

	bool Screen::init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			cout << "ssk::Screen: SDL init failed" << endl;
			return false;
		}

		cout << "ssk::Screen: SDL init succeeded" << endl;

		m_window = SDL_CreateWindow(
			"Plasma Explosion",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		if (m_window == NULL) {
			cout << "ssk::Screen: Error initalizing the window: " << SDL_GetError() << endl;
			SDL_Quit();
			return false;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (m_renderer == NULL) {
			cout << "ssk::Screen: Error initalizing the renderer: " << SDL_GetError() << endl;
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		if (m_texture == NULL) {
			cout << "ssk::Screen: Error initalizing the texture: " << SDL_GetError() << endl;
			SDL_DestroyWindow(m_window);
			SDL_DestroyRenderer(m_renderer);
			SDL_Quit();
			return false;
		}

		m_buffer = new Uint32[SCREEN_HEIGHT * SCREEN_WIDTH];
		m_secondBuffer = new Uint32[SCREEN_HEIGHT * SCREEN_WIDTH];

		memset(m_buffer, 0x00, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));
		memset(m_secondBuffer, 0x00, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));

		return true;
	}

	bool Screen::processEvents()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return false;
			}
		}
		return true;
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
	{
		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
			return;
		}

		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		m_buffer[(y * SCREEN_WIDTH) + x] = color;
	}

	void Screen::boxBlur()
	{
		Uint32* temp = m_buffer;
		m_buffer = m_secondBuffer;
		m_secondBuffer = temp;

		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {

				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;

				for (int row = -1; row < 1; row++) {
					for (int col = -1; col < 1; col++) {
						int currentX = x + col;
						int currentY = y + row;

						if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
							Uint32 color = m_secondBuffer[currentY * SCREEN_WIDTH + currentX];

							redTotal += (Uint8) ((color & 0xFF000000) >> 24);
							greenTotal += (Uint8) ((color & 0x00FF0000) >> 16);
							blueTotal += (Uint8) ((color & 0x0000FF00) >> 8);
						}
					}
				}

				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;

				setPixel(x, y, red, green, blue);
			}
		}
	}

	void Screen::update()
	{
		SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	void Screen::close()
	{
		delete[] m_buffer;
		delete[] m_secondBuffer;

		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);

		SDL_Quit();
	}
}