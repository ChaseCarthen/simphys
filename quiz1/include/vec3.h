/*
  Skeleton of a 3D vector class, for use in simulation physics.
  
  This isn't everything that will eventually go into this class, but
  it's a decent start. Other things we'll eventually have to think about include:
  
  1. Copy constructor
  2. Move constructor (a C++11 thing)
  3. Assignment operator
  4. Equality operator.

  \author Richard Kelley.

  TODO - add your name as an author
  \author
*/

#ifndef VEC3_H
#define VEC3_H

namespace simphys {
  
  class vec3 {
  private:
    float x;
    float y;
    float z;
  public:
    /*
      Constructor.
      \param x_, y_, z_ the coordinates of the vector.
    */
    vec3(float x_, float y_, float z_);

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
    vec3 normalized() const;

    /*
      Normalize this vector.
    */
    void normalize();

    /*
      Dot product of this vector with the other vector
     */
    float dotProduct(const vec3& other) const;

    /*
      Cross product of this vector with the other vector.
     */
    vec3 crossProduct(const vec3& other) const;

    /*
      Getters and setters for the member variables.
    */
    float getX() const;
    float getY() const;
    float getZ() const;
    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);
  };

  /*
    Operations on vec3 inputs.
  */
  vec3 operator+(const vec3& v1, const vec3& v2);
  vec3 operator-(const vec3& v1, const vec3& v2);
  vec3 operator*(float, const vec3& v1);
  vec3 operator*(const vec3& v1, float);
  
}

#endif // VEC3_H
