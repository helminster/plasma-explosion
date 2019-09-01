#pragma once

#include "Particle.h"

namespace ssk {
	class Swarm
	{
	public:
		const static int NPARTICLES = 5000;
	private:
		Particle* m_pParticles;
	public:
		Swarm();
		~Swarm();
		Particle* getParticles() { return m_pParticles; }
	};
}
