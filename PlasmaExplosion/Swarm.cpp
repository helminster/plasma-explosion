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
}