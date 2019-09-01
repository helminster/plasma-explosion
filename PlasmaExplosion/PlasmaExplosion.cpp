#include <iostream>
#include <SDL.h>
#include <math.h>
#include "Screen.h"
#include <time.h>
#include "Swarm.h"

using namespace std;
using namespace ssk;

int main(int argc, char *args[]) {
	srand(time(NULL));
	
	Screen screen;
	
	if (!screen.init()) {
		return 1;
	}

	Swarm swarm;

	while (true) {
		int elapsed = SDL_GetTicks();
		
		swarm.update(elapsed);
		const Particle* const pParticles = swarm.getParticles();
		
		unsigned char red = (1 + sin(elapsed * 0.0001)) * 128;
		unsigned char green = (1 + sin(elapsed * 0.0002)) * 128;
		unsigned char blue = (1 + sin(elapsed * 0.0003)) * 128;

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();
		screen.update();

		if (!screen.processEvents()) {
			break;
		}
	}
	
	screen.close();

	return 0;
}