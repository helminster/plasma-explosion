#pragma once

namespace ssk {
	struct Particle
	{
		double m_x;
		double m_y;
		double m_xspeed;
		double m_yspeed;
	public:
		Particle();
		~Particle();
		void update();
	};
}
