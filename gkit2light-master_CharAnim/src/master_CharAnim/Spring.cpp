#include <Spring.h>
#include <PhysicalWorld.h>

Spring::Spring(float l, float k, int id1, int id2){
    m_l = l;
    m_k = k;
    m_id1 = id1;
    m_id2 = id2;
}

int Spring::getIndex1(){
    return m_id1;
}

int Spring::getIndex2(){
    return m_id2;
}

void Spring::computeParticleForceSpring(Particle& p1, Particle& p2)
{
    p1.addForce(-m_k * (distance(p1.position(), p2.position()) - m_l) * normalize(p1.position() - p2.position()));
    p2.addForce(-m_k * (distance(p1.position(), p2.position()) - m_l) * normalize(p2.position() - p1.position()));
}
