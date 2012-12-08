/*
  A 3D Vector.

  \author Richard Kelley.
*/

#ifndef vec2_H
#define vec2_H

#include <string>
#include <cmath>

namespace simphys {
  
  class vec2 {
  private:
    float x;
    float y;
  public:
    /*
      Constructor.
      \param x_, y_, _ the coordinates of the vector.
    */
    vec2(float x_ = 0.0f, float y_ = 0.0f);

    /*
      Copy constructor.
    */
    vec2(const vec2& other);

    /*
      Copy assignment operator.
    */
    vec2& operator=(const vec2& other);

    /*
      Move operator
    */
    // TODO

    /*
      Return the norm of the vector.
    */
    float norm() const;

    /*
      Return the square of the norm, for efficiency.
    */
    float norm_sq() const;

    /*
      Return the unit vector pointing in the same direction as this
      vector.
     */
    vec2 normalized() const;

    /*
      Normalize this vector.
    */
    void normalize();

    /*
      Dot product of this vector with the other vector
     */
    float dotProduct(const vec2& other) const;

    /*
      Getters and setters for the member variables.
    */
    float getX() const;
    float getY() const;
    void setX(float newX);
    void setY(float newY);

    /*
      return a string representation of this vector.
    */
    std::string toString();    

    /*
      Compare for equality using a precision appropriate for numerical
      simulation.
    */
    bool operator==(const vec2& other) {
      float precision = 0.0001f;
      return (std::fabs(x - other.x) < precision && 
	      std::fabs(y - other.y) < precision);
    }

  };

  /*
    Operations on vec2 inputs.
  */
  vec2 operator+(const vec2& v1, const vec2& v2);
  vec2 operator-(const vec2& v1, const vec2& v2);
  vec2 operator*(float, const vec2& v1);
  vec2 operator*(const vec2& v1, float);
  
}

#endif // vec2_H
