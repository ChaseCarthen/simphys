#ifndef RIGID_BODY_H
#define RIGID_BODY_H

// TODO - provide appropriate headers
#include "quaternion.h"
#include <chrono>
typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

namespace simphys {

  // TODO - provide necessary forward declarations

  class RigidBody {
 
    // current position
    vec3 pos;

    // current velocity
    vec3 vel;

    // current acceleration
    vec3 acc;

    // accumulated force for the current time step
    vec3 accumulatedForces;

    // Damping parameter 
    float damping;

    // 1.0f / mass
    float invMass;
    vec3 centerOfMass;
    vec3 angularAcceleration;
    vec3 angularVelocity;
    vec3 Torque;
    float IntertiaTensorX,IntertiaTensorY, IntertiaTensorZ;
    Quaternion angularOrientation;

  public:

    RigidBody();
    
    // setters
    void setPosition(const vec3& newPos);
    void setVelocity(const vec3& newVel);
    void setAcceleration(const vec3& newAcc);
    void setDamping(float d);
    void setMass(float m);
    void setOrientation(Quaternion orient);
    void setAngularVelocity(vec3 velo);
    void setAngularAcceleration(vec3 accel);
    void setTorque(vec3 Torque);
    // getters
    vec3 getPosition() const;
    vec3 getVelocity() const;
    vec3 getAcceleration() const;
    float getDamping() const;
    float getMass() const;    
    vec3 getAngVel() const;
    vec3 getAngAccel() const;
    vec3 getTorque() const;
    Quaternion getOrientation() const;
 
    // Update the position and velocity of this particle.
    void integrate(fseconds duration);
    
    // clear the force accumulation vector
    void clearForces();

   // Apply a force to this rigid body
   void applyForce(const vec3& force);
    
   void applyTorque(const vec3& torq);
  };

  // TODO - provide necessary non-member functions.

}


#endif // RIGID_BODY_H
