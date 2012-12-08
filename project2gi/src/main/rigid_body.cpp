#include "simphys/rigid_body.h"
#include <iostream>
// TODO - implement rigid body code here.

namespace simphys {

  RigidBody::RigidBody()
    : pos{0.0f, 0.0f, 0.0f}
    , vel{0.0f, 0.0f, 0.0f}
    , acc{0.0f, 0.0f, 0.0f}
    , accumulatedForces{0.0f, 0.0f, 0.0f}
    , damping{1.0f}
    , invMass{1.0f}
    , IntertiaTensorX {10.0f}
    , IntertiaTensorY {10.0f}
    , IntertiaTensorZ {10.0f}
    , Torque {1.0f, 1, 1}
    , angularOrientation{0,0,0,0}
    , angularVelocity{0,0,0}
    , angularAcceleration{0,0,0} { }

  void RigidBody::setPosition(const vec3& newPos) {
    pos = newPos;
  }

  void RigidBody::setVelocity(const vec3& newVel) {
    vel = newVel;
  }

  void RigidBody::setAcceleration(const vec3& newAcc) {
    acc = newAcc;
  }

  void RigidBody::setDamping(float d) {
    damping = d;
  }

  void RigidBody::setMass(float m) {
    // TODO - decide if this is reasonable. Error handling?
    invMass = 1.0f / m;
  }

  vec3 RigidBody::getPosition() const {
    return pos;
  }

  vec3 RigidBody::getVelocity() const {
    return vel;
  }
  
  vec3 RigidBody::getAcceleration() const {
    return acc;
  }

  float RigidBody::getDamping() const {
    return damping;
  }
  
  float RigidBody::getMass() const {
    return 1.0f / invMass;
  }

  void RigidBody::integrate(fseconds duration) {
    //std::cout << "integrate" << std::endl;
    // don't move objects that have "infinite mass."
    if (invMass <= 0.0f ) {
    
    }
    else
    {
       // update position using Euler integration
       pos = pos + duration.count() * vel;

       vec3 resultantAcc = acc;
       resultantAcc = resultantAcc + (invMass * accumulatedForces);

       // update velocity using Euler integration
       vel = vel + duration.count() * resultantAcc;

       // incorporate damping
       vel = vel * damping;

       clearForces();
   }
   if (0 >= IntertiaTensorX && 0 >= IntertiaTensorY && 0 >= IntertiaTensorZ)
   {
      return;
   }
   
   // Rotate
   angularOrientation.normalize();
   auto W = angularOrientation.getW();
   auto X = angularOrientation.getX();
   auto Y = angularOrientation.getY();
   auto Z = angularOrientation.getZ();
   auto x = angularVelocity.getX();
   auto y = angularVelocity.getY();
   auto z = angularVelocity.getZ();
   std::cout << W << " " << X << " " << Y << " " << Z << std::endl;
   Quaternion temp(-X*x + -Y*y + -Z*z, W*x + Z*y + -Y*z, -Z*x + W*y + X*z,Y*x - X*y + W*z);
   angularOrientation = angularOrientation + duration.count() * .5f * temp;
   //std::cout << "yahtzeee2"<< W << X << Y << Z << std::endl;
   angularVelocity = angularVelocity + duration.count()*angularAcceleration;
   angularAcceleration = vec3(Torque.getX()*1.0f/IntertiaTensorX,Torque.getY()*1.0f/IntertiaTensorY,Torque.getZ()*1.0f/IntertiaTensorZ);
   //Torque = .5f*Torque;
  }

  void RigidBody::clearForces() {
    accumulatedForces = vec3{0.0f, 0.0f, 0.0f};
  }
 
  void RigidBody::applyForce(const vec3& force) {
    accumulatedForces = accumulatedForces + force;
  }

  void RigidBody::setOrientation(Quaternion orient)
  {
     angularOrientation = orient;
  }
  void RigidBody::setAngularVelocity(vec3 velo)
  {
     angularVelocity = velo; 
  }
  
  void RigidBody::setAngularAcceleration(vec3 accel)
  {
     angularAcceleration = accel;
  }
  void RigidBody::setTorque(vec3 torq)
  {
     Torque = torq;
  }
  
  vec3 RigidBody::getAngVel() const
  {
     return angularVelocity;
  }

  vec3 RigidBody::getAngAccel() const
  {
     return angularAcceleration;
  }

  vec3 RigidBody::getTorque() const
  {
     return Torque;
  }

  Quaternion RigidBody::getOrientation() const
  {
     return angularOrientation;
  }
}
