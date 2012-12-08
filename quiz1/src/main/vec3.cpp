/*
  Implementation of the vec3 class.

  Wherever you see TODO, you should fill in code to perform the
  required function.

  I decided not to use a namespace declaration or directive, so this
  file is more verbose than you would normally see in the real
  world. The only reason for this is to show you how a custom
  namespace gets used.

  \author Richard Kelley

  TODO - fill in your name as an author
  \author 
*/

#include "vec3.h"
#include <cmath>
#include <iostream>
simphys::vec3::vec3(float x_, float y_, float z_) 
  : x{x_}, y{y_}, z{z_} {
  // TODO - make sure you understand what this notation for a
  // constructor is doing. If you haven't seen this before, bring it
  // up on Piazza and we can talk about initializer lists.
}

float simphys::vec3::norm() const {
  // TODO - fill in implementation for quiz 1.
  return sqrtf(x*x + y*y + z*z);
}

float simphys::vec3::norm_sq() const {
  // TODO - fill in implementation for quiz 1.
  return x*x + y*y + z*z;
}

simphys::vec3 simphys::vec3::normalized() const {
  // TODO - fill in implementation for quiz 1.
  float no = norm();
  return vec3(x/no, y/no, z/no);
}

void simphys::vec3::normalize() { 
  // TODO - fill in implementation for quiz 1.
  float no = norm();
  x /= no;
  y /= no;
  z /= no;
}

float simphys::vec3::dotProduct(const simphys::vec3& other) const {
  // TODO - fill in implementation for quiz 1.
  return x*other.getX() + y*other.getY() + z*other.getZ();
}

simphys::vec3 simphys::vec3::crossProduct(const simphys::vec3& other) const {
  // TODO - fill in implementation for quiz 1.
  return vec3(y*other.getZ()-z*other.getY(), z*other.getX() - x*other.getZ(), x*other.getY() - y * other.getX());
}

float simphys::vec3::getX() const {
  // TODO - fill in implementation for quiz 1.
  return x;
}

float simphys::vec3::getY() const {
  // TODO - fill in implementation for quiz 1.
  return y;
}

float simphys::vec3::getZ() const {
  // TODO - fill in implementation for quiz 1.
  return z;
}


void simphys::vec3::setX(float newX) {  
   // TODO - fill in implementation for quiz 1.
   x=newX;
}
void simphys::vec3::setY(float newY) {  
   // TODO - fill in implementation for quiz 1.
   y=newY;
}
void simphys::vec3::setZ(float newZ) {  
   // TODO - fill in implementation for quiz 1.
   z=newZ;
}

simphys::vec3 simphys::operator+(const simphys::vec3& v1, const simphys::vec3& v2) {
  // TODO - fill in implementation for quiz 1.
  return vec3(v1.getX()+v2.getX(), v1.getY()+v2.getY(), v1.getZ()+v2.getZ());
}

simphys::vec3 simphys::operator-(const simphys::vec3& v1, const simphys::vec3& v2) {
  // TODO - fill in implementation for quiz 1.
  return vec3(v1.getX()-v2.getX(), v1.getY()-v2.getY(), v1.getZ()-v2.getZ());
}

simphys::vec3 simphys::operator*(float c, const simphys::vec3& v1) {
  // TODO - fill in implementation for quiz 1.
  return vec3(v1.getX() * c, v1.getY() * c, v1.getZ() * c);
}

simphys::vec3 simphys::operator*(const simphys::vec3& v1, float c) {
  // TODO - fill in implementation for quiz 1.
  return vec3(v1.getX() * c, v1.getY() * c, v1.getZ() * c);
}
