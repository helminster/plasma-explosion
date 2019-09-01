#include "Swarm.h"

namespace ssk {
	Swarm::Swarm(): lastElapsed(0)
	{
		m_pParticles = new Particle[NPARTICLES];
	}

	Swarm::~Swarm()
	{
		delete[] m_pParticles;
	}

	void Swarm::update(int elapsed)
	{
		int interval = elapsed - lastElapsed;

		for (int i = 0; i < NPARTICLES; i++) {
			m_pParticles[i].update(interval);
		}

		lastElapsed = elapsed;
	}
}