/*
  Implementation of the vec2 class.

  \author Richard Kelley
*/

#include <cmath>
#include <string>

#include "vec2.h"

simphys::vec2::vec2(float x_, float y_) 
  : x(x_), y(y_) {
}

simphys::vec2::vec2(const vec2& other) {
  this->x = other.x;
  this->y = other.y;
}

simphys::vec2& simphys::vec2::operator=(const vec2& other) {
  
  if (this == &other) {
    return *this;
  }

  this->x = other.x;
  this->y = other.y;

  return *this;
}

float simphys::vec2::norm() const {
  return std::sqrt(x*x + y*y );
}

float simphys::vec2::norm_sq() const {
  return (x*x + y*y);
}

simphys::vec2 simphys::vec2::normalized() const {
  float n = norm();
  return vec2(x / n, y / n);
}

void simphys::vec2::normalize() { 
  float n = norm();
  x /= n;
  y /= n;
}

float simphys::vec2::dotProduct(const simphys::vec2& other) const {
  return x * other.x + y * other.y;
}

float simphys::vec2::getX() const {
  return x;
}

float simphys::vec2::getY() const {
  return y;
}

void simphys::vec2::setX(float newX) {
  x = newX;
}

void simphys::vec2::setY(float newY) {
  y = newY;
}

std::string simphys::vec2::toString() {
      return "(" + std::to_string(x) + 
	"," + std::to_string(y) + 
	")";
}

simphys::vec2 simphys::operator+(const simphys::vec2& v1, const simphys::vec2& v2) {
  return vec2(v1.getX() + v2.getX(), 
	      v1.getY() + v2.getY());
}

simphys::vec2 simphys::operator-(const simphys::vec2& v1, const simphys::vec2& v2) {
  return vec2(v1.getX() - v2.getX(), 
	      v1.getY() - v2.getY());
}

simphys::vec2 simphys::operator*(float c, const simphys::vec2& v1) {
  return vec2(c * v1.getX(), 
	      c * v1.getY());
}

simphys::vec2 simphys::operator*(const simphys::vec2& v1, float c) {
  return vec2(v1.getX() * c, 
	      v1.getY() * c);
}
