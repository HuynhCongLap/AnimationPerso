#include "CharacterController.h"

CharacterController::CharacterController()
{
    setPosition(Vector(0,0,0));
    m_v = 0;
    m_vMax = 30;
}

void CharacterController::update(const float dt=0.1){
    setPosition(m_ch2w[3] + m_ch2w(Vector(m_v*dt,0,0)));
}

void CharacterController::turnXZ(const float& rot_angle_v){
    m_ch2w = m_ch2w*RotationY(rot_angle_v);
}

void CharacterController::accelerate(const float& speed_inc){
    m_v+=speed_inc;
    if (m_v > m_vMax)
        m_v = m_vMax;
    if (m_v < 0)
        m_v = 0;
}

void CharacterController::setPosition(const Vector& p){
    m_ch2w.m[0][3] = p.x;
    m_ch2w.m[1][3] = p.y;
    m_ch2w.m[2][3] = p.z;
}

void CharacterController::setVelocityMax(const float vmax){
    m_vMax = vmax;
}

void CharacterController::setVelocityNorm(const float v){
    m_v = v;
}
