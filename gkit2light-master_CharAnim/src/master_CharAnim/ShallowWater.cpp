#include "ShallowWater.h"

ShallowWater::ShallowWater(){
    init(0,0);
}

ShallowWater::ShallowWater(const int DIMX, const int DIMY){
    init(DIMX, DIMY);
}

void ShallowWater::init(const int DIMX, const int DIMY){
    m_h.init(DIMX, DIMY);
    m_g.init(DIMX, DIMY);
    m_n.init(DIMX, DIMY);
    m_vX.init(DIMX, DIMY);
    m_vY.init(DIMX, DIMY);
}

Array2D ShallowWater::advect(Array2D src, const Array2D vx, const Array2D vy){
    Array2D dst;
    float x, y;
    float dt = 0.1;
    dst.init(vx.dimX(), vx.dimY());
    for(int j = 0; j < vx.dimY() ; ++j){
        for(int i = 0; i < vx.dimX() ; ++i){
            x = i - dt*vx(i,j);
            y = j - dt*vy(i,j);
            dst(i,j) = src.interpolate(x, y);
        }
    }
    return dst;
}

void ShallowWater::updateHeight(Array2D &n, const Array2D vx, const Array2D vy){
    float dt = 0.1;
    for(int j = 0; j < vx.dimY()-1 ; ++j){
        for(int i = 0; i < vx.dimX()-1 ; ++i){
            n(i, j) -= n(i, j)*dt*((vx(i+1, j) - vx(i, j))/ vx.dimX() + (vy(i, j+1) - vy(i,j))/ vx.dimY());
        }
    }
}

void ShallowWater::updateVelocities(Array2D &vx, Array2D &vy, const Array2D h){
    float dt = 0.1;
    float g = 9.81;
    for(int j = 0; j < vx.dimY() ; ++j){
        for(int i = 1; i < vx.dimX() ; ++i){
            vx(i,j) += g*dt*((h(i-1, j) - h(i,j))/vx.dimX());
            vy(i,j) += g*dt*((h(i-1, j) - h(i,j))/vx.dimY());
        }
    }
}

void ShallowWater::computeOneStep(){
    m_n = advect(m_n, m_vX, m_vY);
    m_vX = advect(m_vX, m_vX, m_vY);
    m_vY = advect(m_vY, m_vX, m_vY);
    updateHeight(m_n, m_vX, m_vY);
    for(int j = 0; j < m_vX.dimY() ; j++){
        for(int i = 0; i < m_vX.dimX() ; i++){
            m_h(i,j) = m_n(i,j) + m_g(i,j);
        }
    }
    updateVelocities(m_vX, m_vY, m_h);
}

void ShallowWater::draw(){

}
