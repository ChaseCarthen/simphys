#include "simphys/particle.h"
#include <iostream>

namespace simphys {

  Particle::Particle()
    : pos{0.0f, 0.0f, 0.0f}
    , oldpos { 0.0f, 0.0f, 0.0f}
    , initial{true}
    , vel{0.0f, 0.0f, 0.0f}
    , acc{0.0f, 0.0f, 0.0f}
    , accumulatedForces{0.0f, 0.0f, 0.0f}
    , damping{1.0f}
    , invMass{1.0f} { }

  void Particle::setPosition(const vec3& newPos) {
    pos = newPos;
    oldpos = pos;
  }

  void Particle::setVelocity(const vec3& newVel) {
    vel = newVel;
  }

  void Particle::setAcceleration(const vec3& newAcc) {
    acc = newAcc;
  }

  void Particle::setDamping(float d) {
    damping = d;
  }

  void Particle::setMass(float m) {
    // TODO - decide if this is reasonable. Error handling?
    invMass = 1.0f / m;
  }

  vec3 Particle::getPosition() const {
    return pos;
  }

  vec3 Particle::getVelocity() const {
    return vel;
  }
  
  vec3 Particle::getAcceleration() const {
    return acc;
  }

  float Particle::getDamping() const {
    return damping;
  }
  
  float Particle::getMass() const {
    return 1.0f / invMass;
  }

  void Particle::integrate(fseconds duration) {

    // don't move objects that have "infinite mass."
    if (invMass <= 0.0f) {
      return;
    }

//Regular verlet integration
//error due to dt is huge

    /*vec3 temp = pos;
    vec3 resultantAcc = acc;
    if(initial==true)
    {
      oldpos=pos;
      pos = pos + vel*duration.count() + 0.5*(acc)*(duration.count()*duration.count());
      initial = false;
    }
    else{
      resultantAcc = resultantAcc + (invMass * accumulatedForces);
      pos = 2*pos - oldpos + resultantAcc*duration.count()*duration.count();
      oldpos = temp;
     }*/
    
    // update position using Verlocity Verlet integration
    /*pos = pos + vel*duration.count() + 0.5*(acc)*(duration.count()*duration.count());

    // update velocity using Verlocity verlet integration
    vel = vel + 0.5 * (acc)*duration.count();
    
    // update acceleration
    vec3 resultantAcc = acc;
    acc = resultantAcc + (invMass * accumulatedForces);

    // update velocity again
    vel = vel + .5 * acc * duration.count();*/

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

  void Particle::clearForces() {
    accumulatedForces = vec3{0.0f, 0.0f, 0.0f};
  }

  void Particle::applyForce(const vec3& force) {
    accumulatedForces = accumulatedForces + force;
  }

}
