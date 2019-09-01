#pragma once

#include "Particle.h"

namespace ssk {
	class Swarm
	{
	public:
		const static int NPARTICLES = 7000;
	private:
		Particle* m_pParticles;
		int lastElapsed;
	public:
		Swarm();
		~Swarm();
		Particle* getParticles() { return m_pParticles; }
		void update(int elapsed);
	};
}
