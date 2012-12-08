#include "simphys/grav_fg.h"
#include <iostream>
namespace simphys {


GravGenerator::GravGenerator(const vec3& grav)
{
   gravity = grav;
}

GravGenerator::GravGenerator() : gravity{0,-15.0f,0}
{
}

void GravGenerator::update(shared_ptr<Particle> p, fsecond dt)
{
   p->applyForce(gravity*p->getMass());
}
}
