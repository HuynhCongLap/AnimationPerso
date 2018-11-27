
#include <PhysicalWorld.h>

#include <CharAnimViewer.h>


void PhysicalWorld::update(const float dt)
{
	int i;
	for (i = 0; i<m_part.size(); ++i){
		//TODO
		// i_eme particule update
        m_part[i].update(dt);
		// i_eme particule collision
		m_part[i].groundCollision();
		// i_eme particule add gravirty
		m_part[i].addEarthGravity();
	}
    for (i = 0; i<m_spring.size(); ++i){
        m_spring[i].computeParticleForceSpring(m_part[m_spring[i].getIndex1()],
                                               m_part[m_spring[i].getIndex2()]);
    }
}


void PhysicalWorld::draw()
{
	int i;
	for (i = 0; i<particlesCount(); ++i){
		if (m_part[i].radius()>0)
			CharAnimViewer::singleton().draw_sphere(m_part[i].position(), m_part[i].radius());
	}
	for (i = 0; i<m_spring.size(); ++i){
        CharAnimViewer::singleton().draw_cylinder(m_part[m_spring[i].getIndex1()].position(),
                                                  m_part[m_spring[i].getIndex2()].position(),
                                                  3);
    }
}

int PhysicalWorld::addParticle(const Vector& p, bool isTissu){
    m_part.push_back(Particle(p,isTissu));
    return particlesCount()-1;
}

void PhysicalWorld::addLine(const Vector& p1, const Vector& p2){
     m_spring.push_back(Spring(length(p1 + p2),1,addParticle(p1,false), addParticle(p2,false)));
}

void PhysicalWorld::addCube(const Vector& center, float l){
    float k = 1;
    int id1 = this->addParticle(Vector(center.x-l/2,center.y+l/2,center.z-l/2),false);
    int id2 = this->addParticle(Vector(center.x+l/2,center.y+l/2,center.z-l/2),false);
    int id3 = this->addParticle(Vector(center.x-l/2,center.y+l/2,center.z+l/2),false);
    int id4 = this->addParticle(Vector(center.x+l/2,center.y+l/2,center.z+l/2),false);
    int id5 = this->addParticle(Vector(center.x-l/2,center.y-l/2,center.z-l/2),false);
    int id6 = this->addParticle(Vector(center.x+l/2,center.y-l/2,center.z-l/2),false);
    int id7 = this->addParticle(Vector(center.x-l/2,center.y-l/2,center.z+l/2),false);
    int id8 = this->addParticle(Vector(center.x+l/2,center.y-l/2,center.z+l/2),false);
    m_spring.push_back(Spring(l,k,id1,id2));
    m_spring.push_back(Spring(l,k,id1,id3));
    m_spring.push_back(Spring(l,k,id1,id5));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id1,id4));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id1,id6));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id1,id7));
    m_spring.push_back(Spring(sqrt(l*l+l*l+l*l),k,id1,id8));
    m_spring.push_back(Spring(l,k,id2,id4));
    m_spring.push_back(Spring(l,k,id2,id6));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id2,id3));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id2,id5));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id2,id8));
    m_spring.push_back(Spring(sqrt(l*l+l*l+l*l),k,id2,id7));
    m_spring.push_back(Spring(l,k,id3,id4));
    m_spring.push_back(Spring(l,k,id3,id7));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id3,id5));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id3,id8));
    m_spring.push_back(Spring(sqrt(l*l+l*l+l*l),k,id3,id6));
    m_spring.push_back(Spring(l,k,id4,id8));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id4,id6));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id4,id7));
    m_spring.push_back(Spring(sqrt(l*l+l*l+l*l),k,id4,id5));
    m_spring.push_back(Spring(l,k,id5,id6));
    m_spring.push_back(Spring(l,k,id5,id7));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id5,id8));
    m_spring.push_back(Spring(l,k,id6,id8));
    m_spring.push_back(Spring(sqrt(l*l+l*l),k,id6,id7));
    m_spring.push_back(Spring(l,k,id7,id8));
}

void PhysicalWorld::addTissu(const Vector& center, int lar, int lon){
    int index[lar][lon];
    float k = 1;
    float dis = 10;
    float x, z;
    float y = center.y;
    for (int i = 0; i < lar ; ++i){
        for (int j = 0; j < lon; ++j){
            y -= 1;
            x = center.x + (lar/2 - i) * dis;
            z = center.z + (lon/2 - j) * dis;
            index[i][j] = addParticle(Vector(x,y,z),true);
        }
    }
    for (int i = 0; i < lar ; ++i){
        for (int j = 0; j < lon; ++j){
            if (i < lar-1){
                m_spring.push_back(Spring(dis, k, index[i][j],index[i+1][j]));
            }
            if (j < lon-1){
                m_spring.push_back(Spring(dis, k, index[i][j],index[i][j+1]));
            }
//            if ((i < lar-1) && (j < lon-1)){
//                m_spring.push_back(Spring(dis*sqrt(2), k, index[i][j],index[i+1][j+1]));
//                m_spring.push_back(Spring(dis*sqrt(2), k, index[i][j+1],index[i+1][j]));
//            }
        }
    }
}
