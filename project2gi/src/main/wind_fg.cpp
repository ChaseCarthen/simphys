#include "simphys/wind_fg.h"
#include <iostream>
namespace simphys {
   WindGenerator::WindGenerator(const vec3& windy)
   {
      wind = windy;
   }
   WindGenerator::WindGenerator() : wind{0,0,0}
   {
   }
   void WindGenerator::update(shared_ptr<RigidBody> p, fsecond dt)
   {
      p->applyForce(wind*p->getMass());
   }
}
