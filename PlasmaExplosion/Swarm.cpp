#include "Swarm.h"

namespace ssk {
	Swarm::Swarm()
	{
		m_pParticles = new Particle[NPARTICLES];
	}

	Swarm::~Swarm()
	{
		delete[] m_pParticles;
	}

	void Swarm::update()
	{
		for (int i = 0; i < NPARTICLES; i++) {
			m_pParticles[i].update();
		}
	}
}