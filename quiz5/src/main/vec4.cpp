#include "vec4.h"

simphys::vec4::vec4(float _x, float _y, float _z, float _w) : x(_x),y(_y),z(_z),w(_w){}

float simphys::vec4::getX() const
{
   return x;
}
float simphys::vec4::getY() const
{
   return y;
}
float simphys::vec4::getZ() const
{
   return z;
}
float simphys::vec4::getW() const
{
   return w;
}
void simphys::vec4::setX(float val)
{
   x = val;
}
void simphys::vec4::setY(float val)
{
   y = val;
}
void simphys::vec4::setZ(float val)
{
   z = val;
}
void simphys::vec4::setW(float val)
{
   w = val;
}
