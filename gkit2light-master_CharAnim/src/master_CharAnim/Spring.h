#ifndef SPRING_H
#define SPRING_H

#include <iostream>
#include <vector>
#include <Particle.h>
#include "vec.h"
using namespace std;

class Spring
{
public:
    Spring(float l, float k, int id1, int id2);
    int getIndex1();
    int getIndex2();
    void computeParticleForceSpring(Particle& p1, Particle& p2);
protected:
    float m_l;
    float m_k;
    int m_id1, m_id2;
};

#endif // SPRING_H
