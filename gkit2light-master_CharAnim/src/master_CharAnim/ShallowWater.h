#ifndef SHALLOWWATER_H
#define SHALLOWWATER_H
#include <vector>
#include <assert.h>
using namespace std;

class Array2D
{
public:
   Array2D() { m_dimX=m_dimY=0; }
   void init(const int DIMX, const int DIMY) { m_dimX=DIMX; m_dimY=DIMY; m_data.resize(m_dimX*m_dimY); }
   void setAll(const float v) { m_data.assign(m_dimX*m_dimY, v); }
   const int dimX() const { return m_dimX; }
   const int dimY() const { return m_dimY; }

   float& operator()(const int x, const int y)
   {
      assert( x>=0 && x<m_dimX && y>=0 && y<m_dimY);
      return m_data[ y*m_dimX+x ];
   }

   float operator()(const int x, const int y) const
   {
      assert( x>=0 && x<m_dimX && y>=0 && y<m_dimY);
      return m_data[ y*m_dimX+x ];
   }

   float interpolate(const float x, const float y)
   {
      if ((x<0) || (x>m_dimX) || (y<0) || (y>m_dimY)) return 0.f;
      int X = int(x);
      int Y = int(y);
      if ((X+1>=m_dimX) || (Y+1>=m_dimY)) return operator()(X,Y);
      float IX_b = (x-X)*operator()(X+1,Y) + (X+1-x)*operator()(X,Y);
      float IX_h = (x-X)*operator()(X+1,Y+1) + (X+1-x)*operator()(X,Y+1);
      return (y-Y)*IX_h + (Y+1-y)*IX_b;
   }


protected:
   vector<float> m_data; // OU float* m_data
   int m_dimX, m_dimY;
};


class ShallowWater
{
public:
   ShallowWater();
   ShallowWater(const int DIMX, const int DIMY);
   Array2D advect(Array2D src, const Array2D vx, const Array2D vy);
   void init(const int DIMX, const int DIMY);
   void updateHeight(Array2D &n, const Array2D vx, const Array2D vy);
   void updateVelocities(Array2D &vx, Array2D &vy, const Array2D h);
   void computeOneStep();
   void draw();
//protected:
   Array2D m_g;     // height of the ground (0 if flat)
   Array2D m_h;     // height of the water : the thing to compute and to draw
   Array2D m_n;     // m_n = m_h - m_g : amount of water above the ground
   Array2D m_vX;    // velocity along X
   Array2D m_vY;    // velocity along Y
};

#endif // SHALLOWWATER_H
