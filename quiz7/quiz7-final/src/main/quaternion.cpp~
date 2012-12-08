#include "quaternion.h"
#include <iostream>

// Constructoers
simphys::Quaternion::Quaternion(const vec3 other)
{
   w = 0;
   x = other.getX();
   y = other.getY();
   z = other.getZ();  
}

simphys::Quaternion::Quaternion(const float _w, const float _x, const float _y, const float _z)
{
   w = _w;
   y = _y;
   z = _z;
   x = _x;
}

// Getters and Setters
float simphys::Quaternion::getX() const
{
   return x;
}

float simphys::Quaternion::getY() const
{
   return y;
}

float simphys::Quaternion::getZ() const
{
   return z;
}

float simphys::Quaternion::getW() const
{
   return w;
}

void simphys::Quaternion::setY(float val)
{
   y = val;
}

void simphys::Quaternion::setX(float val)
{
   x = val;
}

void simphys::Quaternion::setZ(float val)
{
   z = val;
}
void simphys::Quaternion::setW(float val)
{
   w = val;
}

// Norm functions
float simphys::Quaternion::norm() const
{
   return sqrt(x*x+y*y+z*z+w*w);
}
void simphys::Quaternion::normalize()
{
   float normval = norm();
   //std:: cout << normval;
   if( normval != 0.0f )
   {
      x /= normval;
      y /= normval;
      z /= normval;
      w /= normval;
   }
}

simphys::mat33 simphys::Quaternion::getMatrix() const
{
   auto temp2 = (*this);
   if ( norm() != 1.0f)
   {
      temp2.normalize(); 
   }
   auto X = temp2.getX();
   auto Y = temp2.getY();
   auto Z = temp2.getZ();
   auto W = temp2.getW();
   //std::cout << W << ' '<< X << ' ' << Y << ' ' << Z << std::endl;
   simphys::mat33 temp{1.0f-2.0f*Y*Y - 2.0f*Z*Z, 2.0f*X*Y - 2.0f*Z*W, 2.0f*X*Z + 2.0f * Y * W,
                       2.0f*X*Y + 2.0f*Z*W, 1.0f-2.0f*X*X - 2.0f*Z*Z, 2.0f*Y*Z - 2.0f * X * W,
                       2.0f*X*Z - 2.0f * Y * W, 2.0f * Y * Z + 2.0f * X * W, 1.0f - 2.0f *X *X- 2.0f*Y*Y };
   return temp;
}

// operators
simphys::Quaternion simphys::Quaternion::operator+(const Quaternion& other)
{
   return simphys::Quaternion(w+other.getW(),x+other.getX(),y+other.getY(),z+other.getZ());
}

simphys::Quaternion simphys::Quaternion::operator*(const Quaternion& other)
{
   return simphys::Quaternion(w*other.getW()-x*other.getX()-y*other.getY()-z*other.getZ(),w*other.getX()+x*other.getW()+y*other.getZ()-z*other.getY(),w*other.getY()-x*other.getZ()+y*other.getW()+z*other.getX(),w*other.getZ()+x*other.getY() - y*other.getX()+z*other.getW());
}

simphys::Quaternion simphys::operator*(const float val, const Quaternion& me)
{
   return simphys::Quaternion( val*me.getW(),val*me.getX(),val*me.getY(), val*me.getZ() );
}
