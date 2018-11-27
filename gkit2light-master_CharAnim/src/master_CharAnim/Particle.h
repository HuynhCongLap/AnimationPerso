/****************************************************************************
Copyright (C) 2010-2020 Alexandre Meyer

This file is part of Simea.

Simea is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Simea is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Simea.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef PARTICLES_H
#define PARTICLES_H

#include <iostream>
#include <vector>
#include <math.h>
#include "vec.h"
using namespace std;
class Particle
{
public:

	Particle()
	{
        m_isTissu = false;
		m_mass = 1.0;      // 1kg
		m_radius = 10 + rand() % 5;
		m_p.x = rand() % 400 - 200;
		m_p.y = m_radius + 5 + rand() % 100;
		m_p.z = rand() % 400 - 200;

	}

	Particle(const Vector& poss, bool isTissu)
	{
	    m_isTissu = isTissu;
        m_mass = 1;
		m_radius = 5;
		m_p.x = poss.x;
		m_p.y = poss.y;
		m_p.z = poss.z;
	}

	void update(const float dt = 0.1f)		// advect
	{
		//TODO
		if (m_mass>0)
		{
			 // mise à jour de la vitesse
			 m_v = m_v + (m_f/m_mass)*dt;
			 // mise à jour de la position
			 m_p = m_p + m_v*dt;
			 // remise à 0 de la force
			 m_f = Vector(0,0,0);
		}
	}

	//! Collision with the ground (y=0)
	void groundCollision()
	{
		if (m_radius < 0) return;
		if (m_p.y < m_radius)
		{
		    if (!m_isTissu)
                m_v = m_v*-0.95;
            else
                m_v = m_v*-0.2;
			m_p.y = m_radius;
		}
	}

	//! Collision with any point p of radius radius (this will be used for kicking with the character's bones)
	bool collision(const Point& p, const float radius)
	{
		if (m_radius < 0) return false;
		if (distance(m_p, p) < m_radius+radius){
            return true;
		}
	}

	//! add force to the particles
	void addForce(const Vector& force)
	{
		m_f = m_f + force;
	}


	//! Apply gravity
	void addEarthGravity()
	{
		addForce(Vector(0,-10*m_mass,0));
	}

	bool isTissu(){
        return m_isTissu;
	}

	float getMass(){
        return m_mass;
	}

	Vector getVelocity(){
        return m_v;
	}

	const Point& position() const { return m_p; }
	float radius() const { return m_radius; }

	friend std::ostream& operator<<(std::ostream& o, const Particle& p)
	{
		o << " p=(" << p.m_p.x << "," << p.m_p.y << ") v=(" << p.m_v.x << "," << p.m_p.y << ") m=" << p.m_mass << std::endl;
		return o;
	}

protected:
    bool m_isTissu;
	Point m_p;				//!< position
	float m_radius;			//!< radius
	Vector m_v;				//!< velocity m/s
	Vector m_f;				//!< force in N
	float m_mass;			//!< mass in kg
};


#endif
