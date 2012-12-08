#ifndef QUATERNION_H
#define QUATERNION_H

/*
  TODO - insert the necessary includes for your own code. You'll need
  to figure out what to include.
*/
#include "mat33.h"
#include "vec3.h"
#include <cmath>
/*
  Basic quaternion class. The interface provided is not complete; we
  are only giving you the parts of the class that we will test for
  correctness. In the "real world," you'd want to implement other
  methods as well.						
*/

namespace simphys {

  class Quaternion {
  private:
    // TODO - fill in necessary data members.
    float x,y,z,w;
  public:
    // construct a quaternion from a vector.
    Quaternion(const vec3);
    
    // construct a quaternion from a collection of floats.
    Quaternion(const float w, const float x, const float y, const float z);
    
    //blank constructor
    Quaternion();

    // TODO - you'll probably want getters and setters for something.
    float getX() const;
    float getY() const;
    float getZ() const;
    float getW() const;
    void setY(float val);
    void setX(float val);
    void setZ(float val);
    void setW(float val);

    // get the norm of this quaternion.
    float norm() const;
    
    // destructively update this quaternion so that its norm is 1.
    void normalize();
    
    // return the rotation matrix represented by this quaternion.  if
    // the quaternion is not a unit quaternion, normalize the
    // quaternion.
    mat33 getMatrix() const;

    /*
      Quaternion arithmetic.

      A reasonable question to ask here is, "Why are these member
      functions?" Another valid approach would be to make these
      operators regular functions and force them to access quaternion
      data via the class's public interface. Either choice could be
      made to work (without efficiency losses), but in this case there
      really isn't a big win by putting the operators outside the
      class. One of the main reasons we wrote vec3 the way we did was
      to represent the fact that scalar-vector multiplication is
      commutative. Since quaternion multiplication is not commutative,
      we don't get that benefit here.
    */
    Quaternion operator+(const Quaternion& other);
    Quaternion operator*(const Quaternion& other);
  };

  /*
    When we multiply a scalar by a quaternion, we typically write the
    scalar on the right. To do something similar in our code, we need
    a function that is not a member.
   */
  Quaternion operator*(const float, const Quaternion&);

}

#endif // QUATERNION_H
