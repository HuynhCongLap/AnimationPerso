#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H
#include "BVH.h"
#include "mat.h"

class CharacterController
	{
	public:
		CharacterController();

		void update(const float dt);

		//void turn(const Transform& transf_v);  // pas forcement n�cessaire
		void turnXZ(const float& rot_angle_v);
		void accelerate(const float& speed_inc);
		void setVelocityMax(const float vmax);

		void setPosition(const Vector& p);
		void setVelocityNorm(const float v);

		const Vector position() const;
		const Vector direction() const;
		float velocity() const;

	//protected:
                Transform m_ch2w;   // matrice du character vers le monde
                                    // le personnage se d�place vers X
                                    // il tourne autour de Y
                                    // Z est sa direction droite

		float m_v;          // le vecteur vitesse est m_v * m_ch2w * Vector(1,0,0)
		float m_vMax;       // ne peut pas acc�l�rer plus que m_vMax
	};

#endif // CHARACTERCONTROLLER_H
